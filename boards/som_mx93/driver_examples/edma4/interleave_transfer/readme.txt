Overview
========
The EDMA interleave transfer example is a simple demonstration program that uses the SDK software.
It excuates interleave transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the interleave feature of EDMA and to provide a simple example for
debugging and further development.
The example demostrates the interleave transfer by features:


Toolchain supported
===================
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect the micro USB to J29 (Cortex-A55s) and the USB to UART adapter to J18.5/J18.3 (RX/TX) (Cortex-M33). 
2.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EDMA interleave transfer example begin.

Destination Buffer:

0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	

EDMA interleave transfer example finish.

Destination Buffer:

1	0	2	0	3	0	4	0	5	0	6	0	7	0	8	0	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

