Overview
========
The TPM project is a demonstration program of the SDK TPM driver's dual-edge capture feature.
This feature is available only on certain SoC's.
The example sets up a TPM channel-pair for dual-edge capture. Meanwhile, the capture mode is set up one-shot, 
using API TPM_SetupDualEdgeCapture(). Once the input signal is received and the second edge is detected,
the interrupt flag will be cleared and the interrupt overflow will be disabled.
The example gets the capture value of the input signal using API TPM_GetChannelValue().
This example will print the capture values and period of the input signal on the terminal window.

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
- J-Link Debug Probe
- 12V~20V power supply
- Personal Computer

Board settings
==============
- CM33: Connect input signal to J1005-3
- note: square wave at fixed rate is recommended as the input signal for easily checking the result. 

Prepare the Demo
================
1.  Connect 12V~20V power supply and J-Link Debug Probe to the board, switch SW301 to power on the board.
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the cpu board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TPM dual-edge capture example

Once the input signal is received the input capture values are printed

The input signal's pulse width is calculated from the capture values & printed

Capture value C(n)V=8c40

Capture value C(n+1)V=e104

Input signals pulse width=904 us 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
