Hardware requirements
=====================
- Type-C USB cable
- DART-MX95 SoM on DT8MCB or Sonata boards
- Proper power supply
- Personal Computer

Board settings
============
Connect J12-4/J6-4 (GPIO DT8MCB/Sonata) and J12-15/J6-15 (GND DT8MCB/Sonata) to oscilloscope

**Please note this application can't support running with Linux BSP!**

====

Prepare the Demo
===============
1.  Connect the power supply to the board and switch on the board.
2.  Connect a Type-C USB cable between the host PC and the J31 USB port on the target board.
3.  Open a serial terminal on the Cortex-M7 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M7 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
When the example runs successfully, if the input duty cycle range is 0~100,
You can see similar information from the terminal as follows and 
square wave observed by oscilloscope will modify duty cycle due to input:
~~~~~~~~~~~~
FLEXIO_PWM demo start.

Please input a value (0 - 100) to set duty cycle: 10
Input value is 10

PWM duty cycle is: 10

PWM leave is: 0

Please input a value (0 - 100) to set duty cycle: 150
Input value is 150
Your value is output of range.
Set pwm output to IDLE.

Please input pwm idle status (0 or 1): 1
Input IDLE state value is 1

PWM leave is: 1

Please input a value (0 - 100) to set duty cycle:
......
~~~~~~~~~~~~
Note:
1. The duty cycle of the PWM is variable, except for the idle state, 0 and 100.
2. If the input duty cycle range exceeds 100, the pwm will be set to idle state
3. If the set pwm idle value is out of range, it will output "Your value is output of range."
   and then return to set the duty cycle.
