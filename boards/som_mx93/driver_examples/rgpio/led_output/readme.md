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
- VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
No special settings are required.


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the target board.
3.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
Since no LED connected to the RGPIO. Please use oscilloscope probe to the pin (J17.6) to check the output (1.8V) to check the output. The output will toggle periodically.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 RGPIO Driver example
 The LED is taking turns to shine.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
