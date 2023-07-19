Overview
========
The flexcan_loopback_functional example shows how to use the loopback test mode to debug your CAN Bus design:

To demonstrates this example, only one board is needed. The example will config one FlexCAN Message
Buffer to Rx Message Buffer and the other FlexCAN Message Buffer to Tx Message Buffer with same ID.
After that, the example will send a CAN Message from the Tx Message Buffer to the Rx Message Buffer
throuth internal loopback interconnect and print out the Message payload to terminal.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- GCC ARM Embedded  10.3.1

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
2.  Connect the micro USB to J29 (Cortex-A55s) and the USB to UART adapter to J18.5/J18.3 (RX/TX) (Cortex-M33).
3.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
==FlexCAN loopback functional example -- Start.==

Send message from MB0 to MB1
tx word0 = 0x0
tx word1 = 0x1
tx word2 = 0x2
tx word3 = 0x3
tx word4 = 0x4
tx word5 = 0x5
tx word6 = 0x6
tx word7 = 0x7

Received message from MB1
rx word0 = 0x0
rx word1 = 0x1
rx word2 = 0x2
rx word3 = 0x3
rx word4 = 0x4
rx word5 = 0x5
rx word6 = 0x6
rx word7 = 0x7

==FlexCAN loopback functional example -- Finish.==
~~~~~~~~~~~~~~~~~~~~~

