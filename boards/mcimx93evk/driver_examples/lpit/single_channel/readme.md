Overview
========
The LPIT single channel project is a simple example of the SDK LPIT driver. It sets up the LPIT
hardware block to trigger a periodic interrupt after every 1 second. When the LPIT interrupt is triggered
a message a printed on the serial terminal and an LED is toggled on the board.


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
When the example runs successfully, you can see the similar information from the terminal as below but you can't see LED toggled on the board
because there is no led connected on the MCIMX93-EVK board .

~~~~~~~~~~~~~~~~~~~~~
Starting channel No.0 ...
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 ........................
~~~~~~~~~~~~~~~~~~~~~
