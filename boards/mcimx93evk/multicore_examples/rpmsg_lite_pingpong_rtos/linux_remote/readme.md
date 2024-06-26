Overview
========
The Multicore RPMsg-Lite pingpong RTOS project is a simple demonstration program that uses the
MCUXpresso SDK software and the RPMsg-Lite library and shows how to implement the inter-core
communicaton between cores of the multicore system. The primary core releases the secondary core
from the reset and then the inter-core communication is established. Once the RPMsg is initialized
and endpoints are created the message exchange starts, incrementing a virtual counter that is part
of the message payload. The message pingpong finishes when the counter reaches the value of 100.
Then the RPMsg-Lite is deinitialized and the procedure of the data exchange is repeated again.

Shared memory usage
This multicore example uses the shared memory for data exchange. The shared memory region is
defined and the size can be adjustable in the linker file. The shared memory region start address
and the size have to be defined in linker file for each core equally. The shared memory start
address is then exported from the linker to the application.

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- GCC ARM Embedded  12.2
- IAR embedded Workbench  9.40.1

Hardware requirements
=====================
- USB Type-C cable
- MCIMX93-EVK Board
- J-Link Debug Probe
- 12V~20V power supply
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1. Connect a USB cable between the host PC and the J1401 USB port on the target board.
   Open two serial terminals for A Core and M Core with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
    (e.g. /dev/ttyUSB0~3, /dev/ttyUSB2 for A Core, /dev/ttyUSB3 for M Core)
2. Connect 12V~20V power supply and J-Link Debug Probe to the board, switch SW301 to power on the board
3. Boot Linux BSP to u-boot, and load M core image from SD card to run. (Put the image into SD card before.)
   => load mmc 1:1 0x80000000 /rpmsg_lite_pingpong_rtos_linux_remote.bin
   => cp.b 0x80000000 0x201e0000 0x20000
   => bootaux 0x1ffe0000 0
4. Append "clk_ignore_unused" in u-boot "mmcargs" env, before booting linux.
5. Boot to linux. Run "echo '7 4 1 7' > /proc/sys/kernel/printk" to change the message level.
6. After login, make sure imx_rpmsg_pingpong kernel module is inserted (lsmod) or insert it (modprobe imx_rpmsg_pingpong).

Running the demo
================
After the boot process succeeds, the ARM Cortex-M33 terminal displays the following information:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RPMSG Ping-Pong FreeRTOS RTOS API Demo...
RPMSG Share Base Addr is 0xb8000000
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
During boot the Kernel,the ARM Cortex-M33 terminal displays the following information:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Link is up!
Nameservice announce sent.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
After the Linux RPMsg pingpong module was installed, the ARM Cortex-M33 terminal displays the following information:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Waiting for ping...
Sending pong...
Waiting for ping...
Sending pong...
Waiting for ping...
Sending pong...
......
Waiting for ping...
Sending pong...
Ping pong done, deinitializing...
Looping forever...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The Cortex-A terminal displays the following information:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
get 1 (src: 0x1e)
get 3 (src: 0x1e)
......
get 99 (src: 0x1e)
get 101 (src: 0x1e)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
