var group__UART__Adapter =
[
    [ "hal_uart_config_t", "group__UART__Adapter.html#structhal__uart__config__t", [
      [ "srcClock_Hz", "group__UART__Adapter.html#a4c820b7ed94ec22cd864fb6074a71ca9", null ],
      [ "baudRate_Bps", "group__UART__Adapter.html#a5077b9c742082e6fb8bb1466dac5d185", null ],
      [ "parityMode", "group__UART__Adapter.html#a58f013d71e3fa22986c63dcd487d6b00", null ],
      [ "stopBitCount", "group__UART__Adapter.html#a9a261c83422f412e90fb633bd48df6ed", null ],
      [ "enableRx", "group__UART__Adapter.html#a46268fe1cb3d929ffb31e4460baa497a", null ],
      [ "enableTx", "group__UART__Adapter.html#a5129a38843a6260d55e828d48314193e", null ],
      [ "instance", "group__UART__Adapter.html#a533c2c22fe4d9651080b40d039a90c4c", null ]
    ] ],
    [ "hal_uart_transfer_t", "group__UART__Adapter.html#structhal__uart__transfer__t", [
      [ "data", "group__UART__Adapter.html#a94611d152125ec134542f6a83a4ea348", null ],
      [ "dataSize", "group__UART__Adapter.html#ad015b3dc81e0a8baecaeb12d5e353660", null ]
    ] ],
    [ "UART_ADAPTER_NON_BLOCKING_MODE", "group__UART__Adapter.html#ga1e416e28a4597d2c7bb899dd77f03035", null ],
    [ "HAL_UART_TRANSFER_MODE", "group__UART__Adapter.html#ga16a70d80d91c156451608862bb0f3d69", null ],
    [ "hal_uart_transfer_callback_t", "group__UART__Adapter.html#ga465cf4da9359face10f612a6efa72ff0", null ],
    [ "hal_uart_status_t", "group__UART__Adapter.html#gac4c3672846627eed4a661d5728686f81", [
      [ "kStatus_HAL_UartSuccess", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81ace53957d3570fb00454fdd51484e8a4b", null ],
      [ "kStatus_HAL_UartTxBusy", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81aef9c1d027988265c69aef95219493bf6", null ],
      [ "kStatus_HAL_UartRxBusy", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81a58742a06efe6f0a686c82d1bbf1347e4", null ],
      [ "kStatus_HAL_UartTxIdle", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81a191f28681f86e8a374711e455949fa3d", null ],
      [ "kStatus_HAL_UartRxIdle", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81acd7b1ae53a0bcb77d67cc66701c3c7f5", null ],
      [ "kStatus_HAL_UartBaudrateNotSupport", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81a56abdea917d92b3a62fb1ee09bfc416f", null ],
      [ "kStatus_HAL_UartProtocolError", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81a4dad70c2171b2445de1224d65645164e", null ],
      [ "kStatus_HAL_UartError", "group__UART__Adapter.html#ggac4c3672846627eed4a661d5728686f81a3e539021cfde4b3468c00de4f834e84e", null ]
    ] ],
    [ "hal_uart_parity_mode_t", "group__UART__Adapter.html#ga943d5d451423bfaee89ffcd13ad2a604", [
      [ "kHAL_UartParityDisabled", "group__UART__Adapter.html#gga943d5d451423bfaee89ffcd13ad2a604a08fcd92b9342a589174cb30bc87c8536", null ],
      [ "kHAL_UartParityEven", "group__UART__Adapter.html#gga943d5d451423bfaee89ffcd13ad2a604ad5aa4e9333286303c2aacaf0720d0393", null ],
      [ "kHAL_UartParityOdd", "group__UART__Adapter.html#gga943d5d451423bfaee89ffcd13ad2a604abf5f4cdb5e90b0fc1c3e079d305cb90d", null ]
    ] ],
    [ "hal_uart_stop_bit_count_t", "group__UART__Adapter.html#ga6ef1d7b5071292588d43708ec3d6ab8d", [
      [ "kHAL_UartOneStopBit", "group__UART__Adapter.html#gga6ef1d7b5071292588d43708ec3d6ab8da34f5d0e676eead962173aa956b850476", null ],
      [ "kHAL_UartTwoStopBit", "group__UART__Adapter.html#gga6ef1d7b5071292588d43708ec3d6ab8dab4bec3351a5a5818347a899989cd65e4", null ]
    ] ],
    [ "HAL_UartInit", "group__UART__Adapter.html#gac234c4bcffe995d8aa1b2392162af796", null ],
    [ "HAL_UartDeinit", "group__UART__Adapter.html#gab68259998677f787072799042ed0ce34", null ],
    [ "HAL_UartReceiveBlocking", "group__UART__Adapter.html#ga652499fca5739b0d61df775e371279bb", null ],
    [ "HAL_UartSendBlocking", "group__UART__Adapter.html#gae7104925b7bff899a7631c5ee708dc5c", null ],
    [ "HAL_UartInstallCallback", "group__UART__Adapter.html#gae9d70dd0b175d45cc9212332af883542", null ],
    [ "HAL_UartReceiveNonBlocking", "group__UART__Adapter.html#ga9a273311aeb550c6dfa176fa0b919e56", null ],
    [ "HAL_UartSendNonBlocking", "group__UART__Adapter.html#ga2100f02e849a297acbf7735d7717a032", null ],
    [ "HAL_UartGetReceiveCount", "group__UART__Adapter.html#ga5e8f1b464e7f3e37e42c796cb4e8e0d5", null ],
    [ "HAL_UartGetSendCount", "group__UART__Adapter.html#ga6b9529aa491cb1407ce02b6123d0764c", null ],
    [ "HAL_UartAbortReceive", "group__UART__Adapter.html#ga3a34b73dc663ff0e93d7b316ffa021d4", null ],
    [ "HAL_UartAbortSend", "group__UART__Adapter.html#ga5024669b09b79eb9fcfbde894d072fef", null ],
    [ "HAL_UartIsrFunction", "group__UART__Adapter.html#gab75136e7430067097980dd89e0838b71", null ]
];