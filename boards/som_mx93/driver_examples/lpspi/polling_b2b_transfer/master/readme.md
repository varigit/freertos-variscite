Overview
========
The lpspi_polling_b2b_transfer example shows how to use LPSPI driver in polling way:

In this example , we need two boards, one board used as LPSPI master and another board used as LPSPI slave.
The file 'lpspi_polling_b2b_transfer_master.c' includes the LPSPI master code.

1. LPSPI master send/received data to/from LPSPI slave in polling . (LPSPI Slave using interrupt to receive/send the data)

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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPSPI board to board polling example.
This example use one board as master and another as slave.
Master uses polling way and slave uses interrupt way. 
Please make sure you make the correct line connection. Basically, the connection is: 
LPSPI_master --  LPSPI_slave   
   CLK       --    CLK  
   PCS       --    PCS 
   SOUT      --    SIN  
   SIN       --    SOUT 
   GND       --    GND 

 Master transmit:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40
 
LPSPI transfer all data matched! 

 Master received:

  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Press any key to run again
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
