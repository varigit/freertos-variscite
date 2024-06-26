Overview
========
The TMU example shows how to configure TMU register to monitor and report the temperature from one 
remote temperature measurement sites located on the chip.

TMU has access to temperature measurement site strategically located on the
chip. It monitors the site and can signal an alarm if a programmed threshold is ever
exceeded.

Note: Before monitoring the temperature, we must programming the calibration table.

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
- MCIMX93-EVK board
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
Start TMU monitor report example.
Board immediate temperature is  35.85 celsius degree.
Board immediate temperature is  36.35 celsius degree.
Board immediate temperature is  36.85 celsius degree.
Board immediate temperature is  36.85 celsius degree.
Board immediate temperature is  36.85 celsius degree.
~~~~~~~~~~~~~~~~~~~~~
