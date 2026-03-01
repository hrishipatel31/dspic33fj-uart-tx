# dsPIC33 UART Transmit – Interrupt Mode

## Description
This branch implements UART transmission using interrupt-driven communication on the dsPIC33 microcontroller.

Unlike the polling version, this implementation uses the UART TX interrupt to transmit data asynchronously. The CPU is free to execute other tasks while transmission occurs in the background.

## Key Features
- UART initialization (8N1 configuration)
- Baud rate configuration using UxBRG
- TX interrupt enabled
- Interrupt Service Routine (ISR) for transmission
- Non-blocking communication

## Why Interrupt Mode?
Polling continuously checks TX status and wastes CPU cycles.
Interrupt mode improves:
- CPU efficiency
- System responsiveness
- Scalability for multitasking systems

## Registers Used
- UxMODE
- UxSTA
- UxBRG
- IECx (Interrupt Enable Control)
- IFSx (Interrupt Flag Status)

## Future Improvements
- Add UART RX interrupt
- Implement circular buffer
- Add DMA-based UART transfer
