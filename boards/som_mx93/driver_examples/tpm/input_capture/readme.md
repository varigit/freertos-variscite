Overview
========
The TPM project is a demonstration program of the SDK TPM driver's input capture feature.
The example sets up a TPM channel for dual-edge capture. Once the input signal is received,
this example will print the capture value.

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
- CM33: Connect input signal to J18-2 and J16-19(GND).

Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the cpu board.
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TPM input capture example
Once the input signal is received the input capture value is printed
Capture value C(n)V=1f61
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
