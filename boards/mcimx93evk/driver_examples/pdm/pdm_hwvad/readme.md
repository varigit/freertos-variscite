Overview
========
The pdm hwvad example shows how to use pdm driver with hwvad:


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
- MCIMX93-EVK  board
- J-Link Debug Probe
- 12V~20V power supply
- Personal Computer

Board settings
==============
No special settings are required.

Note
Please run the application in Low Power boot mode (without Linux BSP).
The IP module resource of the application is also used by Linux BSP.
Or, run with Single Boot mode by changing Linux BSP to avoid resource
conflict.

Prepare the Demo
================
1.  Connect 12V~20V power supply and JLink Plus to the board, switch SW301 to power on the board
2.  Connect a USB Type-C cable between the host PC and the J1401 USB port on the target board.
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
When the demo runs successfully, please speak or play a song nearby microphone,
then you will see log on the terminal like:
~~~~~~~~~~~~~~~~~~~
PDM hwvad example started!

Voice detected

Voice detected

...

PDM hwvad example finished!
~~~~~~~~~~~~~~~~~~~

Note: There is a variable in this example which initial as 50, once voice detected, it will decrease by one until 0, then example finish.
