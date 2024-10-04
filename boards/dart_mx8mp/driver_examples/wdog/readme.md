Overview
========
The WDOG Example project is to demonstrate usage of the KSDK wdog driver.
In this example,implemented to test the wdog.
Please notice that because WDOG control registers are write-once only. And
for the field WDT, once software performs a write "1" operation to this bit,
it can not be reset/cleared until the next POR, this bit does not get reset/
cleared due to any system reset. So the WDOG_Init function can be called 
only once after power reset when WDT set, and the WDOG_Disable function can 
be called only once after reset.

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.3

Hardware requirements
=====================
- Micro USB cable
- DART-MX8M-PLUS SoM
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special is needed.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1.  Connect proper power supply and J-Link Debug Probe to the board, switch SW8 to power on the board
2.  Connect a proper cable between the host PC and the J12 header (pins UART3 TX, RX and GND) on the target board..
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
******** System Start ********
System reset by: Power On Reset!

- 3.Test the WDOG refresh function by using interrupt.
--- wdog Init done---

WDOG has be refreshed!
WDOG has be refreshed!
WDOG has be refreshed!
WDOG has be refreshed!
WDOG has be refreshed!
...
~~~~~~~~~~~~~~~~~~~~~
