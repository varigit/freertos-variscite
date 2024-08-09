Overview
========
The LPIT single channel project is a simple example of the SDK LPIT driver. It sets up the LPIT
hardware block to trigger a periodic interrupt after every 1 second. When the LPIT interrupt is triggered
a message a printed on the serial terminal and an LED is toggled on the board.


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
- DART-MX93 SoM(s) and CustomBoard(s)
- Proper power supply
- Personal Computer

Board settings
==============
No special settings are required.


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect the micro USB to J10 (Cortex-A55s) and the USB to UART adapter to J12.11/J12.13 (RX/TX) (Cortex-M33).
3.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, you can see similar information from the terminal as below:

~~~~~~~~~~~~~~~~~~~~~
Starting channel No.0 ...
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 ........................
~~~~~~~~~~~~~~~~~~~~~
