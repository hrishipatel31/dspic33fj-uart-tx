/* 
 * File:   modbus_data.c
 * Author: hpatel
 *
 * Created on April 19, 2026, 9:43 PM
 */

#include "modbus_data.h"
#include "my_defines.h"

//RD7, RD6, RD13 represents SW2, SW3, SW4 respectively on MCP3903 board

// --- User application holding registers ---
static uint16_t holding_regs[HOLDING_REG_COUNT];

uint16_t modbus_get_holding_register(uint16_t reg_addr)
{
    switch(reg_addr) {
        case 0:
            //RD7 is SW2 on MCP3903 board 
            if (myPORTD->bits.RD7)
                return 0x0000;
            else
                return 0xFFFF;

        case 1:
            //RD6 is SW3 on MCP3903 board 
            if (myPORTD->bits.RD6)
                return 0x0000;
            else
                return 0xFFFF;
        case 2:
            //RD13 is SW4 on MCP3903 board 
            if (myPORTD->bits.RD13)
                return 0x0000;
            else
                return 0xFFFF;
        case 3:
            // Return button status: 0xFFFF if button ON, 0x0000 if button OFF
            return holding_regs[0];
        case 4:
            return holding_regs[1];
        case 5:
            return holding_regs[2];
        case 6:
            return holding_regs[3];
        case 7:
            return holding_regs[4];
        case 8:
            // Return button status: 0xFFFF if button ON, 0x0000 if button OFF
            return holding_regs[5];
        case 9:
            return holding_regs[6];
        case 10:
            return holding_regs[7];
        case 11:
            return holding_regs[8];
        case 12:
            return holding_regs[9];
        default: return 0;
    }
}

// --- Modbus write support ---
void modbus_set_holding_register(uint16_t reg_addr, uint16_t value)
{
    switch(reg_addr) {
        case 64:
            // Set button output state via HMI
            holding_regs[0] = value;
            break;
        case 65:
            // Set button output state via HMI
            holding_regs[1] = value;
            break;
        case 66:
            // Set button output state via HMI
            holding_regs[2] = value;
            break;
        case 67:
            // Set button output state via HMI
            holding_regs[3] = value;
            break;
        case 68:
            // Set button output state via HMI
            holding_regs[4] = value;
            break;
        case 69:
            // Set button output state via HMI
            holding_regs[5] = value;
            break;
        case 70:
            // Set button output state via HMI
            holding_regs[6] = value;
            break;
        case 71:
            // Set button output state via HMI
            holding_regs[7] = value;
            break;
        case 72:
            // Set button output state via HMI
            holding_regs[8] = value;
            break;
        case 73:
            // Set button output state via HMI
            holding_regs[9] = value;
            break;
        // Optional: implement writes for other registers if needed
        default:
            // No action for other addresses
            break;
    }
}