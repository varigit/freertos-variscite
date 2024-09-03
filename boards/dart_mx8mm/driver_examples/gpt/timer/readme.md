Overview
========
The gpt_timer project is a simple demonstration program of the SDK GPT driver. It sets up the GPT
hardware block to trigger a periodic interrupt after every 1 second. When the GPT interrupt is triggered
a message a printed on the UART terminal.

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
- DART-MX8M-MINI SoM
- J-Link Debug Probe
- proper power supply
- Personal Computer

Board settings
==============
No special is needed.



Prepare the Demo
================
1.  Connect proper power supply and J-Link Debug Probe to the board, switch SW8(DT8CustomBoard)/SW7(SymphonyBoard) to power on the board
2.  Connect a proper cable between the host PC and the J12 header(DT8CustomBoard)/J18 header(SymphonyBoard), (pins UART3 TX, RX and GND) on the target board.
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

Press any key to start the example
s
Starting GPT timer ...
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 .
 .
 .
 GPT interrupt is occurred !
 .
 .
 .
~~~~~~~~~~~~~~~~~~~~~
