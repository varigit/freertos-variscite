Overview
========
The flexspi_nor_edma_transfer example shows how to use flexspi driver with dma:

In this example, flexspi will send data and operate the external nor flash connected with FLEXSPI. Some simple flash command will
be executed, such as Write Enable, Erase sector, Program page.
Example will first erase the sector and program a page into the flash, at last check if the data in flash is correct.

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
- M.2 NOR FLASH card

Board settings
==============
1. The M.2 NOR FLASH card should be connected to J901
2. The R4 resistor need to replace from 10KΩ to 1.5KΩ, the rework is based on M.2 NOR FLASH card.

Note
1. The Micron Serial Nor flash memory model is MT25QU512ABB.
2. Please run the application in single boot mode.

Prepare the Demo
================
1.  Connect 12V~20V power supply and J-Link Debug Probe to the board, switch SW301 to power on the board.
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Boot Linux BSP to u-boot, and load M core image from SD card to run. (Put the image into SD card before.)
   => load mmc 1:1 0x80000000 /sdk20-app.bin
   => cp.b 0x80000000 0x201e0000 0x20000
   => bootaux 0x1ffe0000 0

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FLEXSPI edma example started!
Vendor ID: 0x20
Erasing Serial NOR over FlexSPI...
Erase data - successfully.
Program data - successfully.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
