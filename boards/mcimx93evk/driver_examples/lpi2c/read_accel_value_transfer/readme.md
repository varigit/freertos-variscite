Overview
========
The lpi2c_read_accel_value example shows how to use LPI2C driver to communicate with an lpi2c device:

 1. How to use the lpi2c driver to read a lpi2c device who_am_I register.
 2. How to use the lpi2c driver to write/read the device registers.

In this example, the values of three-axis accelerometer print to the serial terminal on PC through
the virtual serial port on board.

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
- MCIMX93-EVK  board
- J-Link Debug Probe
- 12V~20V power supply
- Personal Computer

Board settings
==============
No special settings are required.

Note
Please run the application in Low Power boot mode (without Linux BSP).
The IP module resource of the application is also used by Linux BSP.
Or, run with Single Boot mode by changing Linux BSP to avoid resource
conflict.

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
4.  Download the program to the target board.
5.  Either re-power up your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- Read Accelerometer Value
Found an LSDM6DSO on board , the device address is 0x6A.
The accel values:
status_reg = 0x5 , x = 17156 , y = 22528 , z = -17600
status_reg = 0x5 , x = 16132 , y = 21760 , z = -17344
status_reg = 0x5 , x = 15108 , y = 21760 , z = -17344
status_reg = 0x5 , x = 16132 , y = 22272 , z = -18368
status_reg = 0x5 , x = 16132 , y = 23040 , z = -17344
status_reg = 0x5 , x = 16644 , y = 22272 , z = -16320
status_reg = 0x5 , x = 15364 , y = 23040 , z = -16576
status_reg = 0x5 , x = 16388 , y = 22528 , z = -17344
status_reg = 0x5 , x = 17412 , y = 21760 , z = -16832
status_reg = 0x5 , x = 16644 , y = 23296 , z = -15808

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
