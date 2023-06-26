Ethos-U Core Software

Content
-------
1. Introduction
2. Directory structure
3. Inference with Ethos-U example applications
4. Test process
5. Release notes
6. Limitations

1. Introduction
---------------
Arm Ethos-U65 microNPU is integrated into i.MX93 applications processors, enabling developers
to create more capable, cost-effective and energy-efficient ML applications. It improves
the inference performance of neural networks and is supported with an open-source driver and
compiler. The NPU targets quantized Convolutional Neural Networks (CNN) and Recurrent Neural
Networks (RNN).

This component is Ethos-U core software for Cortex-M core. It provides the example applications
and core driver.

2. Directory structure
--------------------------------------
<MCUXpresso-SDK-root>
|-- boards
|   -- <board>
|      -- demo_apps               - Example build projects
|         -- ethosu_apps_rpmsg    - Ethos-U app with rpmsg example
|         -- ethosu_apps          - Ethos-U app example
|
|-- middleware/ethos-u-core-software
    -- applications               - The inference process APIs
    -- boards                     - The board related initialization and configuration files
    -- core_driver                - Ethos-U core driver which includes reading/writing registers
    -- examples                   - Ethos-U example applications
       -- ethosu_apps_rpmsg       - Ethos-U app with rpmsg example
       -- ethosu_apps             - Ethos-U app example

3. Inference with Ethos-U example applications
-----------------------------------------
3.1 Introduction
    The example ethosu_apps_rpmsg aims to parse the inference request from Cortex-A core, configure
    the NPU’s registers, accomplish the inference, and send back the inference result to Cortex-A
    core. The inference engine is TensorFlow Lite or TensorFlow Lite Micro(TFLM).

    The example ethosu_apps accomplish the inference for conv2d op model. The inference engine is
    TensorFlow Lite Micro.

    The package contains Ethos-U example applications. The build projects can be found in
    the /boards/<board>/demo_apps/ethosu_apps* folders.

3.2 Toolchains supported
    - IAR Embedded Workbench for ARM
    - ArmGCC - GNU Tools ARM Embedded

3.3 Supported board and settings
    - mcimx93evk:
      No special settings are required.

4. Test process
---------------
4.1 Example ethosu_apps_rpmsg is built as .out or .elf and installed in rootfs. In Linux command line,
    user can run the following command to do inference for the model.
    #./inference_runner -d /dev/ethosu0 -n mobilenet_v1_1.0_224_pb_int8_vela.tflite -i stopwatch.bmp -l labels.txt -o output_data_detection -t 1080000000

    When the examples runs, the log and inference result would be seen on the terminal as below.

    Send Ping
    Send version request
    Send capabilities request
    Capabilities:
            version_status:1
            version:{ major=0, minor=0, patch=0 }
            product:{ major=6, minor=0, patch=0 }
            architecture:{ major=1, minor=0, patch=6 }
            driver:{ major=0, minor=16, patch=0 }
            macs_per_cc:8
            cmd_stream_version:0
            custom_dma:false
    Create network
    Create inference
    Wait for inferences
    Inference status: success

    Detected: jinrikisha, confidence:70
    Detected: horse cart, confidence:70
    Detected: academic gown, confidence:70
    Detected: howler monkey, confidence:70

    For other demos, such as face recognition, please refer to the user manual.

4.2 Example ethous_apps is built as .bin. In U-Boot prompt, user can run the following command to do
    inference for the conv2d op model.
    u-boot=> tftp 0x80000000 ethosu_apps.bin;cp.b 0x80000000 0x201e0000 0x20000;bootaux 0x201e0000 0

    When the example runs, the log and inference result would be seen on the terminal as below.

    Initialize Arm Ethos-U
    Inference status: success

5. Release notes
----------------
The software is based on ARM ethos-u-core-software version 22.02.
http://git.mlplatform.org/ml/ethos-u/ethos-u-core-software.git
http://git.mlplatform.org/ml/ethos-u/ethos-u-core-driver.git

6. Limitations
--------------

