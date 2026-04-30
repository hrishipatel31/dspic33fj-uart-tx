/* 
 * File:   modbus_data.c
 * Author: hpatel
 *
 * Created on April 19, 2026, 9:43 PM
 */

#include "modbus_data.h"

// --- User application holding registers ---
static uint16_t holding_regs[HOLDING_REG_COUNT] = {
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 
    0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xAAAA, 0xABCD, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF
};

uint16_t modbus_get_holding_register(uint16_t reg_addr)
{
    switch (reg_addr) {
        case 0:  return holding_regs[0];
        case 1:  return holding_regs[1];
        case 2:  return holding_regs[2];
        case 3:  return holding_regs[3];
        case 4:  return holding_regs[4];
        case 5:  return holding_regs[5];
        case 6:  return holding_regs[6];
        case 7:  return holding_regs[7];
        case 8:  return holding_regs[8];
        case 9:  return holding_regs[9];
        case 10: return holding_regs[10];
        case 11: return holding_regs[11];
        case 12: return holding_regs[12];
        case 13: return holding_regs[13];
        case 14: return holding_regs[14];
        case 15: return holding_regs[15];
        case 16: return holding_regs[16];
        case 17: return holding_regs[17];
        case 18: return holding_regs[18];
        case 19: return holding_regs[19];
        case 20: return holding_regs[20];
        case 21: return holding_regs[21];
        case 22: return holding_regs[22];
        case 23: return holding_regs[23];
        case 24: return holding_regs[24];
        case 25: return holding_regs[25];
        case 26: return holding_regs[26];
        case 27: return holding_regs[27];
        case 28: return holding_regs[28];
        case 29: return holding_regs[29];
        case 30: return holding_regs[30];
        case 31: return holding_regs[31];
        case 32: return holding_regs[32];
        case 33: return holding_regs[33];
        case 34: return holding_regs[34];
        case 35: return holding_regs[35];
        case 36: return holding_regs[36];
        case 37: return holding_regs[37];
        case 38: return holding_regs[38];
        case 39: return holding_regs[39];
        case 40: return holding_regs[40];
        case 41: return holding_regs[41];
        case 42: return holding_regs[42];
        case 43: return holding_regs[43];
        case 44: return holding_regs[44];
        case 45: return holding_regs[45];
        case 46: return holding_regs[46];
        case 47: return holding_regs[47];
        case 48: return holding_regs[48];
        case 49: return holding_regs[49];
        case 50: return holding_regs[50];
        case 51: return holding_regs[51];
        case 52: return holding_regs[52];
        case 53: return holding_regs[53];
        case 54: return holding_regs[54];
        case 55: return holding_regs[55];
        case 56: return holding_regs[56];
        case 57: return holding_regs[57];
        case 58: return holding_regs[58];
        case 59: return holding_regs[59];
        case 60: return holding_regs[60];
        case 61: return holding_regs[61];
        case 62: return holding_regs[62];
        case 63: return holding_regs[63];
        default: return 0;
    }
}