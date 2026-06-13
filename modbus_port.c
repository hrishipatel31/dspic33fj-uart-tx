#include "modbus_port.h"
#include "modbus.h"
#include "my_defines.h"

#define MODBUS_DMA_RX_FRAME_SIZE 8u
#define MODBUS_DMA_TX_MAX_SIZE (3u + HOLDING_REG_COUNT * 2u + 2u)
#define DMA_IRQ_UART1_RX 0x000Bu 
#define DMA_IRQ_UART1_TX 0x000Cu

#if MODBUS_UART_RX_DMA
static uint8_t dma_rx_buf[MODBUS_DMA_RX_FRAME_SIZE] __attribute__((space(dma), aligned(16)));

static void modbus_uart_rx_dma_init(void)
{
    myIFS0->bits.DMA0IF    = 0;   // DMA0 flag disable
    myDMA0CON->bits.CHEN   = 0;  // DMA0  channel Disable
    myDMA0CON->bits.SIZE   = 1;  // (1 - byte , 0 - Word ) transfer
    myDMA0CON->bits.DIR    = 0; // 0 - Read from peripheral(UART1RX) to RAM //  1 - Read from RAM, write to peripheral 
    myDMA0CON->bits.AMODE  = 0;
    myDMA0CON->bits.MODE   = 0b00; // 00 - continuous, Ping-pong disabled

    myDMA0REQ->bits.IRQSEL = DMA_IRQ_UART1_RX;
    myDMA0PAD->bits.PAD    = (volatile uint16_t)&(myU1RXREG->value);
    myDMA0CNT->bits.CNT    = MODBUS_DMA_RX_FRAME_SIZE - 1u; // Number of DMA transfers = CNT + 1;

    myDMA0STA->bits.STA    = __builtin_dmaoffset(dma_rx_buf);

    myIEC0->bits.DMA0IE    = 1; // DMA0 Interrupt Enable
    myDMA0CON->bits.CHEN   = 1;  // DMA0  channel Enable
}
#endif

#if MODBUS_UART_TX_DMA
static uint8_t dma_tx_buf[MODBUS_DMA_TX_MAX_SIZE] __attribute__((space(dma), aligned(16)));

static void modbus_uart_tx_dma_init(void)
{
    myIFS0->bits.DMA1IF    = 0;   // DMA1 flag disable
    myDMA1CON->bits.CHEN   = 0;   // DMA1  channel Disable
    myDMA1CON->bits.SIZE   = 1;   // (1 - byte , 0 - Word ) transfer
    myDMA1CON->bits.DIR    = 1;   // 0 - Read from peripheral to RAM //  1 - Read from RAM, write to peripheral(UART1TX))
    myDMA1CON->bits.AMODE  = 0;
    myDMA1CON->bits.MODE   = 0b01; // one shot, Ping-pong disabled
    
    myDMA1REQ->bits.IRQSEL = DMA_IRQ_UART1_TX;
    myDMA1PAD->bits.PAD    = (volatile uint16_t)&(myU1TXREG->value);
    myDMA1STA->bits.STA    = __builtin_dmaoffset(dma_tx_buf);
    
    myIEC0->bits.DMA1IE    = 1;
}
#endif

void modbus_uart_init(void)
{
    myU1MODE->bits.STSEL = 0;      // 1 Stop bit
    myU1MODE->bits.PDSEL = 0b00;   // No Parity, 8 Data bits
    myU1MODE->bits.ABAUD = 0;      // Auto-Baud disabled
    myU1MODE->bits.BRGH  = 1;      // High speed
    myU1MODE->bits.UARTEN = 1;     // Enable UART
    myU1MODE->bits.UEN    = 0b00;  // TX & RX only
    myU1STA->bits.UTXEN = 1;       // Enable TX
    myU1BRG->value = BRGV;
#if MODBUS_UART_RX_DMA
    myIEC0->bits.U1RXIE = 0;
    modbus_uart_rx_dma_init();
#else
    myIEC0->bits.U1RXIE = 1;
#endif
#if MODBUS_UART_TX_DMA
    myIEC0->bits.U1TXIE = 0;
    modbus_uart_tx_dma_init();
#endif
}

// --- Send single byte to UART hardware ---
void modbus_uart_send(uint8_t byte)
{
    while(!myU1STA->bits.TRMT);
    myU1TXREG->value = byte;
}

void modbus_uart_send_frame(const uint8_t *data, uint16_t length)
{
#if MODBUS_UART_TX_DMA
    if(length == 0 || length > MODBUS_DMA_TX_MAX_SIZE)
    {
        modbus_tx_done_isr();
        return;
    }
    myDMA1CON->bits.CHEN = 0;

    for(uint16_t i = 0; i < length; i++)
    {
        dma_tx_buf[i] = data[i];
    }
    myDMA1CNT->bits.CNT = length - 1u;
    myDMA1STA->bits.STA = __builtin_dmaoffset(dma_tx_buf);

    myIFS0->bits.DMA1IF = 0;

    myDMA1CON->bits.CHEN = 1;
    myDMA1REQ->bits.FORCE = 1;
#else
    if(length == 0)
    {
        modbus_tx_done_isr();
        return;
    }

    modbus_uart_send(data[0]);
    modbus_uart_enable_txint();
#endif
}

// --- Enable/disable TX interrupt ---
void modbus_uart_enable_txint(void)  
{ 
    myIEC0->bits.U1TXIE = 1; 
}

void modbus_uart_disable_txint(void) 
{ 
    myIEC0->bits.U1TXIE = 0; 
}

#if !MODBUS_UART_RX_DMA
// --- UART RX interrupt handler ---
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    myIFS0->bits.U1RXIF = 0;
    if(myU1STA->bits.OERR)
    {
        myU1STA->bits.OERR = 0;
    }
    modbus_rx_isr(myU1RXREG->value); // Pass byte to Modbus driver
}
#endif

#if MODBUS_UART_RX_DMA
// --- DMA0 interrupt handler for UART1 RX frames ---
void __attribute__ ((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    myIFS0->bits.DMA0IF = 0;
    if(myU1STA->bits.OERR)
    {
        myU1STA->bits.OERR = 0;
    }
    modbus_rx_frame_isr(dma_rx_buf, MODBUS_DMA_RX_FRAME_SIZE);
}
#endif

#if MODBUS_UART_TX_DMA
// --- DMA1 interrupt handler for UART1 TX frames ---
void __attribute__ ((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
    myIFS0->bits.DMA1IF = 0;
    myDMA1CON->bits.CHEN = 0;
    while(!myU1STA->bits.TRMT);
    modbus_tx_done_isr();
}
#endif

#if !MODBUS_UART_TX_DMA
// --- UART TX interrupt handler ---
void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    myIFS0->bits.U1TXIF = 0;
    modbus_tx_isr();
}
#endif
