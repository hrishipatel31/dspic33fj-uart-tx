/* 
 * File:   modbus.h
 * Author: hpatel
 *
 * Created on April 13, 2026, 10:29 PM
 */

#ifndef MODBUS_H
#define	MODBUS_H

#include <stdint.h>

#define MODBUS_SLAVE_ADDR 0x0A
#define READ_HOLDING_REGISTER 0x03
#define HOLDING_REG_COUNT   64

void modbus_init(uint8_t *rx_buf, uint16_t rx_size,
                 uint8_t *tx_buf, uint16_t tx_size,
                 uint16_t *holding_regs, uint16_t reg_count);

void modbus_task(void);

void modbus_rx_isr(uint8_t byte); // Called from UART RX ISR
void modbus_tx_isr(void);         // Called from UART TX ISR


#endif	/* MODBUS_H */

