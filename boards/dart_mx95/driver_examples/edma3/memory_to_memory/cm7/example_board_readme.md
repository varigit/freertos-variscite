Hardware requirements
=====================
- Micro USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect the micro USB to J10/J32 (Cortex-A55s on DT8MCB/Sonata) and the USB to UART adapter to (J12.11/J12.13)/(J6.11/J6.13) (RX/TX Cortex-M7 on DT8MCB/Sonata).
3.  Open a serial terminal on the Cortex-M7 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M7 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~
EDMA memory to memory transfer example begin.

Destination Buffer:
0       0       0       0

EDMA memory to memory transfer example finish.

Destination Buffer:
1       2       3       4
~~~~~~~~~~~~~~~~~~~~~

