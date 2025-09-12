Hardware requirements
=====================
- Micro USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
==============
- CM33: Connect input signal to R881
- note: square wave at fixed rate is recommended as the input signal for easily checking the result. 

Prepare the Demo
===============
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
===============
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TPM dual-edge capture example

Once the input signal is received the input capture values are printed

The input signal's pulse width is calculated from the capture values & printed

Capture value C(n)V=8c40

Capture value C(n+1)V=e104

Input signals pulse width=904 us 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
