# I2C Communication between PIC18F4580 and ATMEGA32

This repository demonstrates the I2C communication between a **PIC18F4580** (master) and **ATMEGA32** (slave) microcontroller. The project includes various programs for both master and slave devices to show different functionalities, such as transmitting and receiving data via I2C, as well as UART communication for monitoring purposes.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Master PIC Programs](#master-pic-programs)
    - [MASTER_PIC.c](#master_picc)
    - [MASTER_PIC_EASY.c](#master_pic_easyc)
    - [MASTER_PIC_READ.c](#master_pic_readc)
    - [MASTER_PIC_STRING.c](#master_pic_stringc)
3. [Slave ATMEGA32 Programs](#slave-atmega32-programs)
    - [SLAVE_ATMEGA.c](#slave_atmegac)
    - [SLAVE_ATMEGA_EASY.c](#slave_atmega_easyc)
    - [SLAVE_ATMEGA_SEND.c](#slave_atmega_sendc)
4. [I2C Communication Overview](#i2c-communication-overview)
5. [Hardware Setup](#hardware-setup)


## Project Overview

This project demonstrates the I2C communication between two microcontrollers:
- **Master**: PIC18F4580
- **Slave**: ATMEGA32

The program implements I2C communication between the two devices, where the PIC18F4580 sends data (either a string, integer, or specific character) to the ATMEGA32 over I2C. Additionally, the ATMEGA32 reads the data and transmits it via UART for monitoring purposes. Different examples are provided for various use cases, including sending and receiving data and displaying it over UART.

## Master PIC Programs

### MASTER_PIC.c
- **Overview**: This program initializes I2C communication on the PIC18F4580 and sends specific data (`'S'`, `'M'`) to the ATMEGA32 slave.
- **Key Specifications**:
  - Initializes the I2C communication with a 1kHz frequency.
  - Sends data to the slave device and stops communication afterward.

### MASTER_PIC_EASY.c
- **Overview**: Continuously sends an incrementing integer value (0 to 9) to the ATMEGA32 slave device over I2C.
- **Key Specifications**:
  - Sends an integer value to the slave.
  - Resets the integer to 0 after it exceeds 9.

### MASTER_PIC_READ.c
- **Overview**: Reads data from the ATMEGA32 slave via I2C and transmits the received data over UART.
- **Key Specifications**:
  - Sends a read command to the slave.
  - Reads the data and transmits it to the UART for monitoring.

### MASTER_PIC_STRING.c
- **Overview**: Sends a string (`"HERE WE GO"`) from the PIC18F4580 to the ATMEGA32 slave via I2C.
- **Key Specifications**:
  - Sends a predefined string to the slave.
  - Stops communication after sending the string.

## Slave ATMEGA32 Programs

### SLAVE_ATMEGA.c
- **Overview**: Reads data sent by the PIC18F4580 master over I2C and transmits it over UART.
- **Key Specifications**:
  - Reads data from the I2C bus.
  - Sends the received data to the UART for monitoring.

### SLAVE_ATMEGA_EASY.c
- **Overview**: Continuously reads data from the master and transmits it over UART.
- **Key Specifications**:
  - Reads data from the master device and transmits it via UART in a continuous loop.

### SLAVE_ATMEGA_SEND.c
- **Overview**: Sends predefined characters (`'A'`, `'B'`) to the PIC18F4580 master over I2C.
- **Key Specifications**:
  - Sends data over I2C to the master device.
  - Does not receive any data from the master.

## I2C Communication Overview

- **Master (PIC18F4580)**:
  - Configures and initiates the I2C communication.
  - Sends data to the slave device or requests data from the slave device.
  
- **Slave (ATMEGA32)**:
  - Receives data from the master device over I2C.
  - Transmits received data over UART to provide monitoring or logging information.

## Hardware Setup

- **Master**: The PIC18F4580 is connected to the I2C bus with the ATMEGA32 as the slave.
- **Slave**: The ATMEGA32 is connected to the I2C bus and also communicates with the UART for data transmission.



