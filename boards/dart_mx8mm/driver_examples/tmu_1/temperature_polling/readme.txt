Overview
========
The TMU example shows how to configure TMU register to monitor and report the temperature from
the temperature measurement site located on the chip.

Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- GCC ARM Embedded  9.2.1

Hardware requirements
=====================
- Micro USB cable
- DART-MX8MM SoM
- J-Link Debug Probe
- proper power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1.  Connect proper power supply and J-Link Debug Probe to the board, switch SW8 to power on the board
2.  Connect a proper cable between the host PC and the J12 header (pins UART3 TX, RX and GND) on the target board.
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
When the example runs successfully, you will see the temperature output from the terminal.

Customization options
=====================

