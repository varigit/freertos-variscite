Overview
========
The lpspi_interrupt_b2b example shows how to use LPSPI driver in interrupt way:

In this example , we need two boards , one board used as LPSPI master and another board used as LPSPI slave.
The file 'dspi_interrupt_b2b_slave.c' includes the LPSPI slave code.
This example does not use the transactional API in LPSPI driver. It's a demonstration that how to use the interrupt in KSDK driver.

1. LPSPI master send/received data to/from LPSPI slave in interrupt . (LPSPI Slave using interrupt to receive/send the data)

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.2

Hardware requirements
=====================
- Micro USB cable
- USB to UART Adapter
- two DART-MX93 SoM(s) and CustomBoard(s)
- Proper power supply
- Personal Computer

Board settings
==============
Transfer data from one board instance to another board's instance.
SPI5 pins are connected with SPI5 pins of another board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0(SPI5)     CONNECTS TO         INSTANCE0(SPI5)
Pin Name   Board Location       Pin Name  Board Location
SPI5_SCK    J13   pin 18        SPI5_SCK  J13   pin 18
SPI5_SIN    J13   pin 10        SPI5_SOUT J13   pin 12
SPI5_SOUT   J13   pin 12        SPI5_SIN  J13   pin 10
SPI5_PCS0   J13   pin 8        SPI5_PCS0 J13   pin 8
GND                             GND
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect the micro USB to J10 (Cortex-A55s) and the USB to UART adapter to J12.11/J12.13 (RX/TX) (Cortex-M33).
3.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPSPI board to board functional interrupt example.
  Slave start to receive data...

LPSPI transfer all data matched! 

 Slave received:

  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
 20 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F
 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F
End of slave example! 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
