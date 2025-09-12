Hardware requirements
=====================
- Micro USB cable
- two DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
==============
Connection as below:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER(LPI2C4)                connect to        SLAVE(LPI2C4)
Pin Name    Board Location                      Pin Name    Board Location
SCL         J12.18/J6.18 (DT8MCB/Sonata)                         SCL         J12.18/J6.18 (DT8MCB/Sonata)
SDA         J12.20/J6.20 (DT8MCB/Sonata)                         SDA         J12.20/J6.20 (DT8MCB/Sonata)
GND         J12.15/J6.15 (DT8MCB/Sonata)                         GND         J12.15/J6.15 (DT8MCB/Sonata)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Please note this application can't support running with Linux BSP!**

Prepare the Demo
================
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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
CMSIS LPI2C board2board interrupt example -- Slave transfer.

Slave received data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
