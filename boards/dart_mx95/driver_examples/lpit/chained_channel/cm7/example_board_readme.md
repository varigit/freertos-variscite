Hardware requirements
=====================
- Micro USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
============
No special settings are required.

**Please note this application can't support running with Linux BSP!**

Prepare the Demo
===============
1.  Connect the power supply to the board and switch on the board.
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
When the example runs successfully, you will see the similar information from the terminal shown as below.
Detail prints for each channel depends on by the total numbs of chained channels and the order of 
interrupt flag handler process for each channel. 

~~~~~~~~~~~~~~~~~~~~~
Starting channel No.0 ...
Starting channel No.1 ...
Starting channel No.2 ...
Starting channel No.3 ...

 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !

 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !

 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.3 Chained with Channel No.2 interrupt is occurred !
 .....................................
 .....................................
 .....................................

~~~~~~~~~~~~~~~~~~~~~
