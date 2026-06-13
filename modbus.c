#include "modbus.h"
#include "modbus_port.h"
#include "modbus_data.h"

#define WRITE_SINGLE_REGISTER 06

static uint8_t *rx_buf;
static uint16_t rx_size;
static volatile uint8_t rx_idx;

static uint8_t *tx_buf;
static uint16_t tx_size;
static volatile uint16_t tx_idx;
static volatile uint16_t tx_len;
static volatile uint8_t tx_busy;

static void modbus_start_tx(uint16_t length)
{
    if(!tx_busy && length <= tx_size)
    {
#if MODBUS_UART_TX_DMA
        tx_idx = 0;
#else
        tx_idx = 1;
#endif
        tx_len = length;
        tx_busy = 1;
        modbus_uart_send_frame(tx_buf, tx_len);
    }
}

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

#if !MODBUS_UART_RX_DMA
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
#endif

void modbus_rx_frame_isr(const uint8_t *frame, uint16_t length)
{
    if (length > rx_size)
    {
        rx_idx = 0;
        return;
    }

    for (uint16_t i = 0; i < length; i++)
    {
        rx_buf[i] = frame[i];
    }
    rx_idx = length;
}

#if !MODBUS_UART_TX_DMA
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
#endif

void modbus_tx_done_isr(void)
{
    modbus_uart_disable_txint();
    tx_busy = 0;
    tx_idx = 0;
    tx_len = 0;
}

void modbus_task(void)
{
    if(rx_idx < 8) return;

    uint8_t *req = rx_buf;
    uint16_t slave_addr = req[0];
    uint8_t func_code = req[1];

    // Handle function codes
    switch (func_code) 
    {
        case READ_HOLDING_REGISTER: 
        {
            // --- Standard Read as before ---
            uint16_t start_addr = (req[2] << 8) | req[3];
            uint16_t length = (req[4] << 8) | req[5];
            uint16_t req_crc = (req[7] << 8) | req[6];

            if(slave_addr != MODBUS_SLAVE_ADDR || func_code != READ_HOLDING_REGISTER)
                break;

            // Address/length validity
            if((start_addr != 1 && start_addr > HOLDING_REG_COUNT) || (start_addr != 1 && length >(HOLDING_REG_COUNT - start_addr)) )
                break;

            // CRC
            if(modbus_crc16(req, 6) != req_crc)
                break;
            tx_buf[0] = MODBUS_SLAVE_ADDR;
            tx_buf[1] = READ_HOLDING_REGISTER;
            tx_buf[2] = length * 2;
            uint16_t idx = 3;
            for(uint16_t i = start_addr; i < (start_addr + length); i++) {
                uint16_t reg_val = modbus_get_holding_register(i);
                tx_buf[idx++] = (reg_val >> 8) & 0xFF;
                tx_buf[idx++] = reg_val & 0xFF;
            }
            uint16_t crc = modbus_crc16(tx_buf, idx);
            tx_buf[idx++] = crc & 0xFF;
            tx_buf[idx++] = (crc >> 8) & 0xFF;

            modbus_start_tx(idx);
            break;
        }

        case WRITE_SINGLE_REGISTER: 
        {
            // --- Handle write to address 65 ---
            // Modbus 0x06 frame: slave_addr, func_code, reg_hi, reg_lo, val_hi, val_lo, crc_lo, crc_hi
            uint16_t reg_addr = (req[2] << 8) | req[3];
            uint16_t reg_value = (req[4] << 8) | req[5];
            uint16_t req_crc = (req[7] << 8) | req[6];

            if(slave_addr != MODBUS_SLAVE_ADDR || modbus_crc16(req, 6) != req_crc)
                break;

            modbus_set_holding_register(reg_addr, reg_value); // Set via HAL

            // Per Modbus spec, echo back original request as confirmation
            for(uint16_t i = 0; i < 6; i++)
                tx_buf[i] = req[i];
            uint16_t crc = modbus_crc16(tx_buf, 6);
            tx_buf[6] = crc & 0xFF;
            tx_buf[7] = (crc >> 8) & 0xFF;

            modbus_start_tx(8);
            break;
        }

        default:
            // Unsupported function code—ignore request or implement exception reply
            break;
    }

    rx_idx = 0;
}
