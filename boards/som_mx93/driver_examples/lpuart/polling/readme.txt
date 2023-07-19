Overview
========
The lpuart_polling Example project is to demonstrate usage of the KSDK lpuart driver.
In the example, you can send characters to the console back and they will be printed out onto console
 instantly.
Note: Please input one character at a time. If you input too many characters each time, the receiver may overflow
because the LPUART uses simple polling way for receiving.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- USB to UART Adapter
- VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
No special settings are required.


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
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
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
Lpuart polling example
Board will send back received characters
~~~~~~~~~~~~~~~~~~~~~
