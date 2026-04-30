/* 
 * File:   modbus_data.h
 * Author: hpatel
 *
 * Created on April 19, 2026, 9:43 PM
 */

#ifndef MODBUS_DATA_H
#define	MODBUS_DATA_H

#include <stdint.h>
#include "modbus.h"

//extern uint16_t holding_regs[];
// Returns value for requested holding register address (1-based index)
uint16_t modbus_get_holding_register(uint16_t reg_addr);

#endif	/* MODBUS_DATA_H */

