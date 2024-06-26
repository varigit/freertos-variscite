Overview
========
The TPM project is a simple demonstration program of the SDK TPM driver. It sets up the TPM
hardware block to output a center-aligned PWM signal(24kHZ). The PWM duty cycle is manually updated and is initially 10%.
On boards that have an LED connected to the TPM pins, the user will see a change in LED
brightness if user enter different values.

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
- Oscilloscope

Board settings
==============
- CM33: Connect J1005-3 and J1005-7(GND) to Oscilloscope

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
TPM example to output center-aligned PWM signal

If an LED is connected to the TPM pin, you will see a change in LED brightness if you enter different values
If no LED is connected to the TPM pin, then probe the signal using an oscilloscope
Please enter a value to update the Duty cycle:
Note: The range of value is 0 to 9.
For example: If enter '5', the duty cycle will be set to 50 percent.
Value:5
The duty cycle was successfully updated!

Please enter a value to update the Duty cycle:
Note: The range of value is 0 to 9.
For example: If enter '5', the duty cycle will be set to 50 percent.
Value:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
