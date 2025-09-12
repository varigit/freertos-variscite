Hardware requirements
=====================
- Micro USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
============
Connect J12-4/J6-4 (GPIO DT8MCB/Sonata) and J12-15/J6-15 (GND DT8MCB/Sonata) to oscilloscope

====

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
There is no led connected to the pin, need to see oscilloscope, square wave should be observed.
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
FLEXIO PIN Driver example
The LED is taking turns to shine.
~~~~~~~~~~~~~~~~~~~~~
