Overview
========
In this demo, M core receives audio from microphones and provide them to Linux on Cortex A in DDR and notifies it through RPMSG protocol.
If Linux is suspended, the audio is processed locally with teh selected algorithm
(VAD or wakeword or any future extension).
When voice algorithms triggers (VAD detects voice activity, or wakeword engine detects the wakeword), then A core
is resumed and audio streaming from M core to A core restarts.
When Cortex A is running, music playback from A core can also be sent to M core through DDR and RPMSG protocol but no playback is supported when M core only is running.

SDK version
===========
- Version: 2.15.000

Toolchain supported
===================
- GCC ARM Embedded  12.2

Hardware requirements
=====================
- Micro USB cable
- EVK-MIMX8M Plus board
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- Headphone
- 8MIC-PRI-MX8

Board settings
==============
Connect the 8MIC-PRI-MX8 Microphone board to J21 on the base board if sound capture is needed.

#### Note! ####
1.  This case does not support ddr and flash target.
2.  This case runs together with Linux and the Linux release version should be not lower than 5.15.X_2.0.0.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board
2.  Connect a USB cable between the host PC and the J23 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

******************
NOTE
******************
1.  wm8960 codec is used for audio playback and PDM microphones from "8MIC" add-on board are used for audio recording through imx8MM MICFIL hardware.
2.  Make sure the FDT file is correctly set before booting the linux kernel. The following command can be used to set FDT file in uboot console:
    u-boot=>setenv fdtfile imx8mp-evk-rpmsg-lpv.dtb
    Set the "snd_pcm.max_alloc_per_card" in bootargs, use the following command to print default mmcargs and add "snd_pcm.max_alloc_per_card=134217728" to the end. 
    u-boot=>printenv mmcargs
        For example, "mmcargs=setenv bootargs ${jh_clk} ${mcore_clk} console=${console} root=${mmcroot}" is printed, then set the mmcargs using the following command. 
    u-boot=>setenv mmcargs 'setenv bootargs ${jh_clk} ${mcore_clk} console=${console} root=${mmcroot} snd_pcm.max_alloc_per_card=134217728'
    u-boot=>saveenv
    u-boot=>run prepare_mcore
3.  After M core running, please boot the linux kernel to create the rpmsg channel between A core and M core.

******************
Audio record command (no specific audio processing on Linux)
******************
Note:
1. Please use the command "cat /proc/asound/cards" to check the wm8960 sound card number.
E.g: Type command:
        ~# cat /proc/asound/cards
 0 [btscoaudio     ]: simple-card - bt-sco-audio
                      bt-sco-audio
 1 [imxaudioxcvr   ]: imx-audio-xcvr - imx-audio-xcvr
                      imx-audio-xcvr
 2 [audiohdmi      ]: audio-hdmi - audio-hdmi
                      audio-hdmi
 3 [wm8960audio    ]: wm8960-audio - wm8960-audio
                      wm8960-audio
 4 [micfilaudio    ]: micfil-audio - micfil-audio
                      micfil-audio

2. micfil has ID: 4. Then start audio recording with command (-c option can be tuned to select number of microphones):
    "arecord -Dhw:4,0 -r16000 --buffer-time=10000000 -fS32_LE -c2 test.wav &"

3. Make Linux on A core enter suspend:
    "echo mem > /sys/power/state"

4. When a wakeword ("Hey NXP") is detected by M core, Linux will resume and audio record will continue on Linux.

5. Following command can be used to playback an audio file:
      "aplay -Dplughw:3,0 xxx.wav"
   Note that playback will be automatically paused when Linux suspends and restarted after Linux has resumed.

******************
usage with NXP-AFE and advanced audio processing on Linux
******************
See NXP-AFE documentation (https://source.codeaurora.org/external/imx/nxp-afe/) to properly configure Linux ALSA paths and enable advanced audio processing applications.
Then Linux can be suspended by "echo mem > /sys/power/state"
It will be resumed when Cortex-M detects the wakeword.


Running the demo
================
1. When the demo boots successfully on M Core, the log on the terminal will look like:

#################### LOW POWER VOICE DEMO START ####################

Build Time: Mar 31 2022--10:16:54
VoiceSeekerLight_Create status: 0x0
VoiceSpot library version: 0.23.1.1648542135
VoiceSpot model version: 0.13.1
VoiceSpot model string: HeyNXP_en-US_1
********************************
Wait the Linux kernel boot up to create the link between M core and A core.

********************************
The rpmsg channel between M core and A core created!
********************************

No audio, M core enters STOP mode!



2. When Linux starts the audio recording:

Playback or record is running, M core enters RUN mode!


3. When Linux is suspended and wakeword is detected:

VoiceSpot: wakeword detected



