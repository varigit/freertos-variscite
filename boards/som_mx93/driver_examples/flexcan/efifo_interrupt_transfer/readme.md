Overview
========
The flexcan_efifo_interrupt_transfer example shows how to use FlexCAN Enhanced Rx FIFO in none-blocking interrupt way:

In this example, when setting ENABLE_LOOPBACK macro, only one board is needed. The example will config one FlexCAN Message
Buffer to Tx Message Buffer and setup Enhanced Rx FIFO. After that, the example will send 4 CAN FD Messages
from Tx Message Buffer to Enhanced Rx FIFO through internal loopback interconnect. The sent and received message will be print 
out to terminal

2 boards are required to be connected through CAN bus if ENABLE_LOOPBACK is not defined. Endpoint A(board A) send a CAN Message to
Endpoint B(board B) when user press space key in terminal. Endpoint B receives the message by Enhanced Rx FIFO, and print
the message content to terminal after receive 4 CAN FD messages.


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
- two VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
The example requires connecting between CAN pins of two boards.
The connection should be set as follows:

Between two boards:
- J16.20-1(CANH) node A, J16.20-2(CANH) node B
- J16.18-1(CANL) node A, J16.18-2(CANL) node B
- J16.19-1(GND) node A, J16.19-2(GND) node B


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board
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
When the example runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~
This message displays on the node A terminal:

********* FLEXCAN Interrupt EXAMPLE *********

    Message format: Standard (11 bit id)

    Message buffer 9 used for Rx.

    Message buffer 8 used for Tx.

    Interrupt Mode: Enabled

    Operation Mode: TX and RX --> Normal

*********************************************

Please select local node as A or B:

Note: Node B should start first.

Node:a

Press any key to trigger one-shot transmission

Rx MB ID: 0x123, Rx MB data: 0x0, Time stamp: 8877

Press any key to trigger the next transmission!

Rx MB ID: 0x123, Rx MB data: 0x1, Time stamp: 32459

Press any key to trigger the next transmission!
~~~~~~~~~~~~~~~~~~~~~

This message displays on the node B terminal:

********* FLEXCAN Interrupt EXAMPLE *********

    Message format: Standard (11 bit id)

    Message buffer 9 used for Rx.

    Message buffer 8 used for Tx.

    Interrupt Mode: Enabled

    Operation Mode: TX and RX --> Normal

*********************************************

Please select local node as A or B:

Note: Node B should start first.

Node:b

Start to Wait data from Node A

Rx MB ID: 0x321, Rx MB data: 0x0, Time stamp: 5759

Wait Node A to trigger the next transmission!

Rx MB ID: 0x321, Rx MB data: 0x1, Time stamp: 57276

Wait Node A to trigger the next transmission!
~~~~~~~~~~~~~~~~~~~~~
