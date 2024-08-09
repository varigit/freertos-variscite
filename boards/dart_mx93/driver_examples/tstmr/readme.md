Overview
========

The tstmr example shows the usage of TSTMR driver in application. The TSTMR module is a free running incrementing counter that starts running after system reset de-assertion and can be read at any time by the software for determining the software ticks.The TSTMR runs off the 1 MHz clock and resets on every system reset.

In this example, it would output a time stamp information when the application is ready. And then, delay for 1 second with TSTMR_DelayUs() function. Before and after the delay, it would output the two time stamps information again.


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
When the demo runs successfully, will get the similar messages on the terminal.

~~~~~~~~~~~~~~~~~~~~~~
 Timestamp1 = 01c98d6

 Test the delay function, delay for 1 second

 Start time = 01cb123

 End time = 02bfbd3
~~~~~~~~~~~~~~~~~~~~~~
