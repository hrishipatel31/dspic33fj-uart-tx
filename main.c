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

// ... existing code ...

#include <stdint.h>
#include "my_defines.h"

#define FOSC 7372800UL
#define Fcy FOSC/2
#define BAUDRATE 9600
#define STD_SPEED 16
#define HIGH_SPEED 4
#define BRGVAL ((Fcy/BAUDRATE)/HIGH_SPEED)-1


void UART1_init()
{
    myU1MODE->bits.ABAUD     = 0;
    myU1MODE->bits.BRGH      = 1;    //HIGH SPEED UART
    myU1MODE->bits.PDSEL     = 0b00; // 8-BIT NO PARITY
    myU1MODE->bits.STSEL     = 0;    // ONE STOP BIT
    myU1MODE->bits.UARTEN    = 1;    // ENABLE UART
    
    myU1BRG->value = BRGVAL ;          // BAUDRATE PRESCALAR
    
    myU1STA->bits.UTXEN = 0b01;        // UART TX ENABLE
}

void UART_TX(char *ch)
{
    
    while(*ch != '\0')
    {
        while(myU1STA->bits.UTXBF); // wait if TX buffer is full
        myU1TXREG->value = *ch;
        ch++;
    }
    
}

uint8_t UART_RX()
{
    while(!(myU1STA->bits.URXDA)); // wait until data arrives
    if(myU1STA->bits.OERR == 1)     // Receive buffer has overflown
    {
        myU1STA->bits.OERR = 0;  // reset the receive buffer 
    }
    return myU1RXREG->value;
}

int main(void)
{
    char tx_buff[2];
    
    
    UART1_init();
    UART_TX("UART1 INITIALIZE: \n\r");
    
    while(1)
    {
        tx_buff[0] = UART_RX();
        tx_buff[1] = '\0';  // Adding NULL so that 'uart_TX' can handle it as a string
        UART_TX(&tx_buff);  // Echo: Transmit this byte directly
    }
}