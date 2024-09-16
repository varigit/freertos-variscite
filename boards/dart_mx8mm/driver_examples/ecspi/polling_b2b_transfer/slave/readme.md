Overview
========
The ecspi_polling_b2b_transfer example shows how to use ECSPI driver in polling way:

In this example , we need two boards, one board used as ECSPI master and another board used as ECSPI slave.
The file 'ecspi_polling_b2b_transfer_slave.c' includes the ECSPI slave code.

1. ECSPI master send/received data to/from ECSPI slave in polling . (ECSPI Slave using interrupt to receive/send the data)

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.3

Hardware requirements
=====================
- Micro USB cable
- DART-MX8M-MINI SoM
- J-Link Debug Probe
- proper power supply
- Personal Computer

Board settings
==============
ECSPI board to board:
Transfers data through the instance 1 of the ECSPI interface. ECSPI1 pins of the master board are
connected to the ECSPI1 pins of the slave board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER BOARD           CONNECTS TO         SLAVE BOARD
Pin Name    Board Location                 Pin Name  Board Location
For ECSPI1 connection, refer to: https://variwiki.com/index.php?title=MCUXpresso&release=MCUXPRESSO_2.15.0_V1.0_DART-MX8M-MINI#Demos_pins
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect proper power supply and J-Link Debug Probe to the board, switch SW8(DT8CustomBoard)/SW7(SymphonyBoard) to power on the board
2.  Connect a proper cable between the host PC and the J12 header(DT8CustomBoard)/J18 header(SymphonyBoard), (pins UART3 TX, RX and GND) on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the debug terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECSPI board to board polling example.

 Slave example is running...
 
 Slave starts to receive data!
 This is ECSPI slave transfer completed callback.
 It's a successful transfer.
 
 Slave starts to transmit data!
 This is ECSPI slave transfer completed callback.
 It's a successful transfer.
 
 Slave receive:
      1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
     11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
     21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
     31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Slave example is running...

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
