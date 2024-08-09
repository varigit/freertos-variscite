Overview
========
This document explains the freertos_mutex example. It shows how mutex manage access to common
resource (terminal output).

The example application creates two identical instances of write_task. Each task will lock the mutex
before printing and unlock it after printing to ensure that the outputs from tasks are not mixed
together.

The test_task accept output message during creation as function parameter. Output message have two
parts. If xMutex is unlocked, the write_task_1 acquire xMutex and print first part of message. Then
rescheduling is performed. In this moment scheduler check if some other task could run, but second
task write_task+_2 is blocked because xMutex is already locked by first write task. The first
write_task_1 continue from last point by printing of second message part. Finaly the xMutex is
unlocked and second instance of write_task_2 is executed.




SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- IAR embedded Workbench  9.40.1
- GCC ARM Embedded  12.2

Hardware requirements
=====================
- Micro USB cable
- USB to UART Adapter
- DART-MX93 SoM(s) and CustomBoard(s)
- Proper power supply
- Personal Computer

Board settings
==============
No special settings are required.


Prepare the Demo
================
1.  Connect the power supply to the board and switch on the board.
2.  Connect the micro USB to J10 (Cortex-A55s) and the USB to UART adapter to J12.11/J12.13 (RX/TX) (Cortex-M33).
3.  Open a serial terminal on the Cortex-M33 serial port with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Load and start the demo on the M33 using either U-Boot (bootaux) or Linux (remoteproc) per the variwiki guide.

Running the demo
================
After the board is flashed the Tera Term will start periodically printing strings synchronized by
mutex.

Example output:
"ABCD | EFGH"
"1234 | 5678"
"ABCD | EFGH"
"1234 | 5678"
