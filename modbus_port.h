/* 
 * File:   modbus_port.h
 * Author: hpatel
 *
 * Created on April 13, 2026, 10:30 PM
 */

#ifndef MODBUS_PORT_H
#define	MODBUS_PORT_H

#include <stdint.h>

// --- User edits below for hardware compatibility ---

#define FOSC 7372800UL
#define Fcy (FOSC/2)
#define BAUDRATE 115200
#define STD_SPEED 16
#define HIGH_SPEED 4
#define BRGV ((Fcy/BAUDRATE)/HIGH_SPEED)-1

void modbus_uart_init(void);
void modbus_uart_send(uint8_t byte);
void modbus_uart_enable_txint(void);
void modbus_uart_disable_txint(void);

#endif	/* MODBUS_PORT_H */

