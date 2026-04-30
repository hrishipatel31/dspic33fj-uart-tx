#include "modbus.h"
#include "modbus_port.h"
#include "modbus_data.h"

static uint8_t *rx_buf;
static uint16_t rx_size;
static volatile uint8_t rx_idx;

static uint8_t *tx_buf;
static uint16_t tx_size;
static volatile uint16_t tx_idx;
static volatile uint16_t tx_len;
static volatile uint8_t tx_busy;

static uint16_t modbus_crc16(uint8_t *data, uint16_t length)
{
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

void modbus_init(uint8_t *rx_b, uint16_t rx_s,
                 uint8_t *tx_b, uint16_t tx_s)
{
    rx_buf = rx_b;
    rx_size = rx_s;
    rx_idx = 0;
    tx_buf = tx_b;
    tx_size = tx_s;
    tx_idx = 0;
    tx_len = 0;
    tx_busy = 0;
}

void modbus_rx_isr(uint8_t byte)
{
    if (rx_idx < rx_size) 
    {
        rx_buf[rx_idx++] = byte;
    } 
    else 
    {
        rx_idx = 0; // wrap or discard old
    }
}

void modbus_tx_isr(void)
{
    if (tx_idx < tx_len) 
    {
        modbus_uart_send(tx_buf[tx_idx++]);
    } 
    else 
    {
        modbus_uart_disable_txint();
        tx_busy = 0;
        tx_idx = 0;
        tx_len = 0;
    }
}

void modbus_task(void)
{
    // Minimum Modbus RTU frame: 8 bytes for function 0x03
    if(rx_idx < 8)
        return;

    uint8_t *req = rx_buf;
    uint16_t slave_addr = req[0];
    uint8_t func_code = req[1];
    uint16_t start_addr = (req[2] << 8) | req[3];
    uint16_t length = (req[4] << 8) | req[5];
    uint16_t req_crc = (req[7] << 8) | req[6];

    // Check slave address & function code
    if(slave_addr != MODBUS_SLAVE_ADDR || func_code != READ_HOLDING_REGISTER)
        goto clear_rx;

    // Address/length validity
    if((start_addr != 1 && start_addr > HOLDING_REG_COUNT) || (start_addr != 1 && length >(HOLDING_REG_COUNT - start_addr)) )
        goto clear_rx;

    // CRC
    if(modbus_crc16(req, 6) != req_crc)
        goto clear_rx;

    // Build Modbus reply frame
    tx_buf[0] = MODBUS_SLAVE_ADDR;
    tx_buf[1] = READ_HOLDING_REGISTER;
    tx_buf[2] = length * 2;
    uint16_t i = 0, idx = 3;
    for(i = start_addr; i < (start_addr + length); i++) {
        tx_buf[idx++] = (modbus_get_holding_register(i) >> 8) & 0xFF;
        tx_buf[idx++] = modbus_get_holding_register(i) & 0xFF;
    }
    uint16_t crc = modbus_crc16(tx_buf, idx);
    tx_buf[idx++] = crc & 0xFF;
    tx_buf[idx++] = (crc >> 8) & 0xFF;

    // Start TX (interrupt driven)
    if(!tx_busy) {
        tx_idx = 1;
        tx_len = idx;
        tx_busy = 1;
        modbus_uart_send(tx_buf[0]); // first byte
        modbus_uart_enable_txint();
    }

clear_rx:
    rx_idx = 0; // ready for next request
}
