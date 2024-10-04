Overview
========
The PWM project is a simple demonstration program of the SDK PWM driver. It sets up the PWM hardware
block to output PWM signals on one PWM channel. The example also shows PWM duty cycle is increase or decrease.
The FIFO empty interrupt is provided. A new value will be loaded into FIFO when FIFO empty status bit is set. 
The PWM will run at the last set duty-cycle setting if all the values of the FIFO has been utilized, 
until the FIFO is reloaded or the PWM is disabled. When a new value is written, the duty cycle changes after the current period is over.
The outputs can be observed by oscilloscope.

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
Use Oscilloscope to measure and observe the Test Point J14-7 output signal.



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
These instructions are displayed/shown on the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~
PWM driver example.
~~~~~~~~~~~~~~~~~~~~~~~


