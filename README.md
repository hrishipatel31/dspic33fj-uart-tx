# Modbus RTU Slave (dsPIC33FJ256GP710A)

## Overview

This project implements a **Modbus RTU Slave** on the **dsPIC33FJ256GP710A** using **UART1**.

The slave responds to **Function Code 0x03 (Read Holding Registers)** and allows a Modbus master (e.g., Modbus Poll, QModMaster) to read holding register values.

---

## Features

* Modbus RTU protocol implementation
* UART1 communication (9600 baud, 8N1)
* Supports **Function Code 0x03 (Read Holding Registers)**
* Slave address configurable (default: `0x01`)
* Supports reading **64 holding registers**
* CRC16 (Modbus) calculation and validation
* Simple and lightweight implementation (no RTOS)

---

## Hardware

* Microcontroller: **dsPIC33FJ256GP710A**
* UART: **UART1**
* Communication: RS232 / RS485 (depending on external hardware)

---

## UART Configuration

* Baud Rate: **9600**
* Data Bits: **8**
* Parity: **None**
* Stop Bits: **1**

---

## Modbus Configuration

* Slave ID: `0x01` (decimal 10)
* Supported Function Code:

  * `0x03` → Read Holding Registers
* Register Range:

  * Address: **1 to 64**

---

## Supported Request Format

### Master Request

| Byte | Description          |
| ---- | -------------------- |
| 1    | Slave Address        |
| 2    | Function Code (0x03) |
| 3-4  | Starting Address     |
| 5-6  | Number of Registers  |
| 7-8  | CRC                  |

---

### Slave Response

| Byte | Description   |
| ---- | ------------- |
| 1    | Slave Address |
| 2    | Function Code |
| 3    | Byte Count    |
| 4-N  | Register Data |
| Last | CRC           |

---

## How It Works

1. UART receives Modbus frame
2. Frame is validated using **CRC**
3. Slave checks:

   * Address match
   * Function code
4. If valid:

   * Reads requested registers
   * Sends response with updated CRC

---

## Example

Master sends:

* Read 2 registers starting at address 1

Slave responds:

* Returns corresponding register values with CRC

---

## How to Test

You can test using:

* **Modbus Poll (Windows)**

### Steps:

1. Connect MCU via UART/RS485
2. Configure tool:

   * Baud: 9600
   * Slave ID: 1
3. Send request:

   * Function: 03
   * Address: 1
   * Quantity: up to 64
4. Verify response

---

## Future Improvements

* Interrupt-based UART handling
* Support for more function codes (0x06, 0x10)
* DMA-based reception
* Error handling (exception responses)
* Configurable register map

---

## Author

**hpatel**

---

## Notes

* Designed for learning and embedded firmware development
* Suitable for interview demonstration of:

  * UART communication
  * Protocol implementation
  * Embedded C design

---

