Overview
========
The EDMA wrap transfer example is a simple demonstration program that uses the SDK software.
It excuates wrap transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the wrap feature of EDMA and to provide a simple example for
debugging and further development.


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
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either re-power up your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EDMA wrap transfer example begin.

Destination Buffer:

0	0	0	0	0	0	0	0	

EDMA wrap transfer example finish.

Destination Buffer:

1	2	3	4	1	2	3	4
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
