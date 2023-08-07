Overview
========
The LPI2C Example project is a demonstration program that uses the KSDK software to manipulate the Low Power Inter-
Integrated Circuit.
The example uses two instances of LPI2C, one in configured as master and the other one as slave.
The LPI2C master sends data to LPI2C slave. The slave will check the data it receives and shows the log.


Toolchain supported
===================
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- USB to UART Adapter
- two VAR-SOM-MX93 SoM(s) and Symphony Board(s)
- Proper power supply
- Personal Computer

Board settings
==============
Connection as below:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER(LPI2C7)                connect to        SLAVE(LPI2C7)
Pin Name    Board Location                      Pin Name    Board Location
SCL         J16   pin 10                         SCL         J16   pin 10
SDA         J16   pin 12                         SDA         J16   pin 12
GND         J16   pin 19                         GND         J16   pin 19
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
Master:
LPI2C example -- MasterInterrupt_SlaveInterrupt.
Master will send data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f

I2C master transfer completed successfully.

Slave:
LPI2C example -- MasterInterrupt_SlaveInterrupt.
I2C slave transfer completed successfully.


 Transfer successfully!

Slave received data :
0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7
0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f
0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f
~~~~~~~~~~~~~~~~~~~~~
