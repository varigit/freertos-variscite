Overview
========
The freertos_lpspi_b2b_master example shows how to use LPSPI driver in FreeRTOS.
In this example are required two boards, one board is used as LPSPI master on which
is runnuing freertos_lpspi_b2b_master and another board is used as LPSPI slave on which
is running freertos_lpspi_b2b_slave example.

Connection of boards is in section Board settings.

It is required to run first the slave demo.



Toolchain supported
===================
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- USB to UART Adapter
- two VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
Transfer data from one board instance to another board's instance.
SPI6 pins are connected with SPI6 pins of another board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0(SPI6)     CONNECTS TO         INSTANCE0(SPI6)
Pin Name   Board Location       Pin Name  Board Location
SPI6_SCK    J16   pin 2        SPI6_SCK  J16   pin 2
SPI6_SIN    J16   pin 6        SPI6_SOUT J16   pin 8
SPI6_SOUT   J16   pin 8        SPI6_SIN  J16   pin 6
SPI6_PCS0   J16   pin 4        SPI6_PCS0 J16   pin 4
GND                             GND
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect the micro USB to J29 (Cortex-A55s) and the USB to UART adapter to J18.5/J18.3 (RX/TX) (Cortex-M33).
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

This example uses two boards to connect with one as master and anohter as slave.
Master and slave are both use interrupt way.
Please make sure you make the correct line connection. Basically, the connection is:
LPSPI_master -- LPSPI_slave
    CLK      --    CLK
    PCS      --    PCS
    SOUT     --    SIN
    SIN      --    SOUT

LPSPI master transfer completed successfully.
LPSPI transfer all data matched !
