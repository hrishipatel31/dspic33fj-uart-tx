#include "modbus_port.h"
#include "modbus.h"
#include "my_defines.h"

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
    myIEC0->bits.U1RXIE = 1;
}

// --- Send single byte to UART hardware ---
void modbus_uart_send(uint8_t byte)
{
    while(!myU1STA->bits.TRMT);
    myU1TXREG->value = byte;
}

// --- Enable/disable TX interrupt ---
void modbus_uart_enable_txint(void)  { myIEC0->bits.U1TXIE = 1; }
void modbus_uart_disable_txint(void) { myIEC0->bits.U1TXIE = 0; }

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

// --- UART TX interrupt handler ---
void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    myIFS0->bits.U1TXIF = 0;
    modbus_tx_isr();
}
