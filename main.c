/* 
 * Modbus RTU Slave for dsPIC33FJ256GP710A
 * Responds to function code 0x03 (Read Holding Registers) for addresses 1–64.
 * Slave address: 0x01 (decimal 10)
 * Connects via UART1 at 9600 baud, 8N1.
 * Polling tools can read up to 64 holding registers.
 * Author: hpatel
 * Created: Feb 25, 2026
 */
// DSPIC33FJ256GP710A Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure Segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = PRI              // Oscillator Mode (Primary Oscillator (XT, HS, EC))
#pragma config IESO = OFF               // Two-speed Oscillator Start-Up Enable (Start up with user-selected oscillator)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Source (XT Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include<stdio.h>
#include <stdint.h>
#include "my_defines.h"
#define FOSC 7372800UL // define XTAL FREQ
#define Fcy FOSC/2     // Peripheral clock freq
#define BAUDRATE 9600  // Baud rate
#define STD_SPEED 16
#define HIGH_SPEED 4
#define BRGV ((Fcy/BAUDRATE)/HIGH_SPEED)-1 // caluculate Baud rate prescalar

#define MODBUS_SLAVE_ADDR   0x01
#define HOLDING_REG_COUNT   64
#define UART_RX_BUF_SIZE    64

uint16_t holding_regs[HOLDING_REG_COUNT] = 
{
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF
};

volatile uint8_t uart_rx_buf[UART_RX_BUF_SIZE];
volatile uint8_t uart_rx_idx = 0;

// --- CRC16 Modbus ---
uint16_t modbus_crc16(uint8_t *data, uint16_t length) {
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < length; pos++) {
        crc ^= data[pos];
        for (uint8_t i = 0; i < 8; i++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

void delay(uint16_t i)
{
    for(uint16_t j=0; j < i; j++ ) { ; }
}

void UART1_init(void)
{
    myU1MODE->bits.STSEL = 0;      // 1 Stop bit
    myU1MODE->bits.PDSEL = 0b00;   // No Parity, 8 Data bits
    myU1MODE->bits.ABAUD = 0;      // Auto-Baud disabled
    myU1MODE->bits.BRGH  = 1;      // High speed
    myU1MODE->bits.UARTEN = 1;     // Enable UART
    myU1MODE->bits.UEN    = 0b00;  // TX & RX only
    myU1STA->bits.UTXEN = 1;       // Enable TX
    myU1BRG->value = BRGV;         // Set baud rate (define BRGV appropriately)
    myIEC0->bits.U1RXIE = 1;
}

// --- UART RX Interrupt (called when RX byte arrives) ---
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    myIFS0->bits.U1RXIF = 0;
    if(myU1STA->bits.OERR) {
        myU1STA->bits.OERR = 0;
    }
    uart_rx_buf[uart_rx_idx++] = myU1RXREG->value;
    if(uart_rx_idx >= UART_RX_BUF_SIZE) {
        uart_rx_idx = 0; // wrap
    }
}

// --- Parse Modbus request and reply ---
void process_modbus_requests(void) 
{
    if (uart_rx_idx < 8) return;

    uint8_t *req = (uint8_t *)uart_rx_buf;
    uint16_t start_addr = (req[2] << 8) | req[3];   // Start address (Modbus)
    uint16_t num_regs   = (req[4] << 8) | req[5];   // Quantity

    // Address check: Allow 0 or 1 as start address (most pollers use 1)
    if ((start_addr != 0 && start_addr != 1)) return;
    // Length check: up to HOLDING_REG_COUNT only
    if (num_regs == 0 || num_regs > HOLDING_REG_COUNT) return;

    // CRC check (low byte first)
    uint16_t req_crc = (req[7] << 8) | req[6];
    if (modbus_crc16(req, 6) != req_crc) return;

    // Build response dynamically: 3 header + (num_regs*2) data + 2 CRC
    uint8_t resp[3 + HOLDING_REG_COUNT*2 + 2]; // Max buffer size
    resp[0] = MODBUS_SLAVE_ADDR;
    resp[1] = 0x03;
    resp[2] = num_regs * 2; // byte count (2 bytes per register)

    uint16_t idx = 3;
    uint16_t reg_offset = (start_addr == 0) ? 0 : 1; // Modbus addressing
    for (uint16_t i = 0; i < num_regs; i++) {
        resp[idx++] = (holding_regs[i + reg_offset] >> 8) & 0xFF;
        resp[idx++] = holding_regs[i + reg_offset] & 0xFF;
    }

    uint16_t resp_crc = modbus_crc16(resp, idx);
    resp[idx++] = resp_crc & 0xFF;          // CRC low
    resp[idx++] = (resp_crc >> 8) & 0xFF;   // CRC high

    // Send response
    for (uint16_t i = 0; i < idx; i++) {
        while (myU1STA->bits.UTXBF); // Wait until ready
        myU1TXREG->value = resp[i];
    }

    uart_rx_idx = 0; // Reset buffer
}

// --- Main ---
int main(void)
{
    UART1_init();
    delay(100);

    while(1) {
        process_modbus_requests();
    }
}

