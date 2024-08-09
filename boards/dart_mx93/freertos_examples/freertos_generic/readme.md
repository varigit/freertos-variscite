Overview
========

This document explains the freertos_generic example. It is based on code FreeRTOS documentation from
http://www.freertos.org/Hardware-independent-RTOS-example.html. It shows combination of several
tasks with queue, software timer, tick hook and semaphore.

The example application creates three tasks. The prvQueueSendTask periodically sending data to
xQueue queue. The prvQueueReceiveTask is waiting for incoming message and counting number of
received messages. Task prvEventSemaphoreTask is waiting for xEventSemaphore semaphore given from
vApplicationTickHook. Tick hook give semaphore every 500 ms.

Other hook types used for RTOS and resource statistics are also demonstrated in example:
* vApplicationIdleHook
* vApplicationStackOverflowHook
* vApplicationMallocFailedHook



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
After the board is flashed the Tera Term will start periodically printing the state of generic example.

Example output:
Event task is running.
Receive message counter: 1.
Receive message counter: 2.
Receive message counter: 3.
Receive message counter: 4.
Receive message counter: 5.
Receive message counter: 6.
Receive message counter: 7.
Receive message counter: 8.
Receive message counter: 9.
Receive message counter: 10.
Receive message counter: 11.
Receive message counter: 12.
Event task is running.
Receive message counter: 13.
Receive message counter: 14.
...
