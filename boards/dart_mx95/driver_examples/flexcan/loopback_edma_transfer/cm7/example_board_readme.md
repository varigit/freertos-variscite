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
1.  Connect 12V~20V power supply and JLink Plus to the board, switch SW4 to power on the board
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
When the example runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~

==FlexCAN loopback edma example -- Start.==

Send Msg1 to Rx FIFO: word0 = 0x11111111, word1 = 0x11111111.
Send Msg2 to Rx FIFO: word0 = 0x22222222, word1 = 0x22222222.
Send Msg3 to Rx FIFO: word0 = 0x33333333, word1 = 0x33333333.
Send Msg4 to Rx FIFO: word0 = 0x44444444, word1 = 0x44444444.

Receive Msg1 from FIFO: word0 = 0x11111111, word1 = 0x11111111, ID Filter Hit2.
Receive Msg2 from FIFO: word0 = 0x22222222, word1 = 0x22222222, ID Filter Hit2.
Receive Msg3 from FIFO: word0 = 0x33333333, word1 = 0x33333333, ID Filter Hit2.
Receive Msg4 from FIFO: word0 = 0x44444444, word1 = 0x44444444, ID Filter Hit2.

==FlexCAN loopback EDMA example -- Finish.==
~~~~~~~~~~~~~~~~~~~~~
