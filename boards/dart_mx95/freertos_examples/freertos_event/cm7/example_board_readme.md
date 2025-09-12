Hardware requirements
=====================
- Micro USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
============
No special settings are required.



Prepare the Demo
===============
1.  Connect the power supply to the board and switch on the board. switch SW4 to power on the board
2.  Connect a USB cable between the host PC and the J31 USB port on the target board.
3.  Open a serial terminal on the Cortex-M7 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M7 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
${ANCHOR}
