Hardware requirements
=====================
- Micro USB cable
- two DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
==============
The example requires connecting between CAN pins of two boards.
The connection should be set as follows:

Between two boards:
- J16.7-1/J10.7-1 (CANH DT8MCB/Sonata) node A  J16.7-2/J10.7-2 (CANH DT8MCB/Sonata) node B
- J16.9-1/J10.9-1 (CANL DT8MCB/Sonata) node A, J16.9-2/J10.9-2 (CANL DT8MCB/Sonata) node B
- J16.10-1/J10.10-1 (GND DT8MCB/Sonata) node A, J16.10-2/J10.10-2 (GND DT8MCB/Sonata) node B

Prepare the Demo
================
1.  Connect 12V~20V power supply and JLink Plus to the board, switch SW4 to power on the board
2.  Connect a micro USB cable between the host PC and the J31 USB port on the target board.
3.  Open a serial terminal on the Cortex-M7 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M7 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

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
