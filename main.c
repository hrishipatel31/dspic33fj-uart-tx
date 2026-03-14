/* 
 * File:   main.c
 * Author: hpatel
 *
 * Created on February 25, 2026, 9:18 PM
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

/*
 * UART Echo using Interrupt Mode
 *
 * NOTE / LIMITATION:
 * This implementation works reliably at lower baud rates (e.g., 9600).
 * At higher baud rates, characters may be lost or corrupted.
 *
 * Possible reasons:
 * - ISR latency
 * - UART FIFO overflow
 * - TX register not ready before next RX interrupt
 *
 * This code is currently intended for learning and testing interrupt-based UART communication.
 */

#include<stdio.h>
#include <stdint.h>
#include "my_defines.h"
#define FOSC 7372800UL // define XTAL FREQ
#define Fcy FOSC/2     // Peripheral clock freq
#define BAUDRATE 115200  // Baud rate
#define STD_SPEED 16
#define HIGH_SPEED 4
#define BRGV ((Fcy/BAUDRATE)/HIGH_SPEED)-1 // caluculate Baud rate prescalar

// UART message
const char tx_msg[] = "UART1 TX INTERRUPT MODE \r\n";
volatile const char *uart_tx_ptr = NULL;
volatile unsigned int txIndex = 0;
volatile char rx_data[2];

void delay(uint16_t i)
{
    for(uint16_t j=0; j < i; j++ )
    {
        ;
    }
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

    myIEC0->bits.U1TXIE = 0;       // Disable UART1 TX interrupt initially
    myIEC0->bits.U1RXIE = 1;       // Enable UART1 RX interrupt initially
}

void start_uart1_tx(const char *msg)
{
    // Only start TX if hardware TX is idle (previous transmission done)
    if(myU1STA->bits.TRMT)
    {
        uart_tx_ptr = msg;             // Point to the string to transmit
        txIndex = 0;                   // Transmission in progress
        myU1TXREG->value = uart_tx_ptr[txIndex++]; // send first character
        myIEC0->bits.U1TXIE = 1;       // Enable UART1 TX interrupt
    }
}

// UART1 TX Interrupt Service Routine
void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    myIFS0->bits.U1TXIF = 0; // clear interrupt flag
    
    if (uart_tx_ptr[txIndex] != '\0') 
    {
        myU1TXREG->value = uart_tx_ptr[txIndex++];   // Send current character, advance pointer
    } 
    else 
    {
        myIEC0->bits.U1TXIE = 0;            // Disable TX interrupt when done
    }
}

// UART1 RX Interrupt Service Routine
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    myIFS0->bits.U1RXIF = 0; // clear interrupt flag
    if(myU1STA->bits.OERR)
    {
        myU1STA->bits.OERR = 0;
    }
    if(myU1STA->bits.URXDA)
    {
        rx_data[0] = myU1RXREG->value;
        rx_data[1] = '\0';
        start_uart1_tx(rx_data);         // Send the string to UART1
    }
    
}

int main(void)
{
    UART1_init();
    delay(100);                             // Allow time for UART setup, define delay()
    start_uart1_tx(tx_msg);
    while (1)
    {

    }
}
