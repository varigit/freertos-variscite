Overview
========
CMSIS-Driver defines generic peripheral driver interfaces for middleware making it reusable across a wide 
range of supported microcontroller devices. The API connects microcontroller peripherals with middleware 
that implements for example communication stacks, file systems, or graphic user interfaces. 
More information and usage method please refer to http://www.keil.com/pack/doc/cmsis/Driver/html/index.html.

The cmsis_i2c_edma_b2b_transfer_master example shows how to use i2c driver as master to do board to board transfer 
with EDMA:

In this example, one i2c instance as master and another i2c instance on the other board as slave. Master sends a 
piece of data to slave, and receive a piece of data from slave. This example checks if the data received from 
slave is correct.

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.2

Hardware requirements
=====================
- USB Type-C cable
- two MCIMX93-EVK boards
- J-Link Debug Probe
- 12V~20V power supply
- Personal Computer

Board settings
==============
Connection as below:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER(LPI2C1)                connect to        SLAVE(LPI2C1)
Pin Name    Board Location                      Pin Name    Board Location
SCL         J1005 pin 3                         SCL         J1005 pin 3
SDA         J1005 pin 5                         SDA         J1005 pin 5
GND         J1005 pin 7                         GND         J1005 pin 7
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect 12V~20V power supply and J-Link Debug Probe to the board, switch SW301 to power on the board.
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Boot Linux BSP to u-boot, and load M core image from SD card to run. (Put the image into SD card before.)
   => load mmc 1:1 0x80000000 /sdk20-app.bin
   => cp.b 0x80000000 0x201e0000 0x20000
   => bootaux 0x1ffe0000 0

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
CMSIS LPI2C board2board EDMA example -- Slave transfer.

Slave received data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
