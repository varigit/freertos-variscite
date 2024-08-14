Overview
========
The Hello World project is a simple demonstration program that uses the SDK UART drivere in
combination with FreeRTOS. The purpose of this demo is to show how to use the debug console and to
provide a simple project for debugging and further development.

The example application creates one task called hello_task. This task print "Hello world." message
via debug console utility and suspend itself.




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
- VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
No special settings are required.


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
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
After the board is flashed the Tera Term will print "Hello world" message on terminal.

Example output:
Hello world.
