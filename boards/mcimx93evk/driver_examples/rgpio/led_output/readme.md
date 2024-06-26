Overview
========
The RGPIO Example project is a demonstration program that uses the SDK software to manipulate the general-purpose
outputs.
The example is supported by the set, clear, and toggle write-only registers for each port output data register. The 
example take turns to shine the LED.


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


Prepare the Demo
================
1.  Connect 12V~20V power supply and JLink Plus to the board, switch SW301 to power on the board
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Either re-power up your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
Since no LED connected to the RGPIO. Please use oscilloscope probe to the pin to check the output. The output will toggle periodically.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 RGPIO Driver example
 The LED is taking turns to shine.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
