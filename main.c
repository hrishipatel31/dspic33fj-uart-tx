/* 
 * Modbus RTU Slave for dsPIC33FJ256GP710A
 * Responds to function code 0x03 (Read Holding Registers) for addresses 1–64.
 * Slave address: 0x01 (decimal 10)
 * Connects via UART1 at 9600 baud, 8N1.
 * Tested Baud Rates from 9600 to 115200 at standard UART speed and at High speed UART, and it works!!!
 * Polling tools can read up to 64 holding registers.
 * Author: hpatel
 * Created: April 12, 2026
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


#include <stdint.h>
#include "modbus.h"
#include "modbus_port.h"
#include "modbus_data.h"

#define UART_RX_BUF_SIZE    64
#define UART_TX_BUF_SIZE    (3 + HOLDING_REG_COUNT*2 + 2)

// --- Modbus RX/TX Buffers ---
uint8_t modbus_rx_buf[UART_RX_BUF_SIZE];
uint8_t modbus_tx_buf[UART_TX_BUF_SIZE];

int main(void)
{
    modbus_uart_init(); // UART HW setup
    modbus_init(modbus_rx_buf, UART_RX_BUF_SIZE,
                modbus_tx_buf, UART_TX_BUF_SIZE);

    while(1) {
        modbus_task(); // driver handles incoming/outgoing frames
    }
}

