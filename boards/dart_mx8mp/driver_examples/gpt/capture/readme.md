Overview
========
The gpt_capture project is a simple demonstration program of the SDK GPT driver's input capture feature.
The example sets up a GPT channel for rise-edge capture. Once the input signal is received,
this example will print the capture value.

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.3

Hardware requirements
=====================
- Micro USB cable
- DART-MX8M-PLUS SoM
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
Connect input signal to the Test Point.



Prepare the Demo
================
1.  Connect proper power supply and J-Link Debug Probe to the board, switch SW8 to power on the board
2.  Connect a proper cable between the host PC and the J12 header (pins UART3 TX, RX and GND) on the target board..
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~
GPT input capture example
Once the input signal is received the input capture value is printed
~~~~~~~~~~~~~~~~~~~~~
