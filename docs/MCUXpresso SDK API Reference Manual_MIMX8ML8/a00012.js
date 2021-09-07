var a00012 =
[
    [ "ecspi_channel_config_t", "a00012.html#a00162", [
      [ "channelMode", "a00012.html#ae4b6b855f5d5202d69995657f6b495f9", null ],
      [ "clockInactiveState", "a00012.html#aa08cd8243e60e65e43e5425c8a560a07", null ],
      [ "dataLineInactiveState", "a00012.html#a9ad22b79de30e56cb705c239c7bb62fd", null ],
      [ "chipSlectActiveState", "a00012.html#a373701fa6b25844c20404dbda4b08612", null ],
      [ "polarity", "a00012.html#aa6327b0a05d54c85c01ca246e86b50c4", null ],
      [ "phase", "a00012.html#aad4e0d3e01790b01e7c0ca7c6c5920af", null ]
    ] ],
    [ "ecspi_master_config_t", "a00012.html#a00163", [
      [ "channel", "a00012.html#ab7f80a7f7b11d5c4d3d08a39199dacfd", null ],
      [ "channelConfig", "a00012.html#a5a267f3458edd5cb57aea83c3a17ae1f", null ],
      [ "samplePeriodClock", "a00012.html#ae5056430705436de599aa16a0796f45b", null ],
      [ "burstLength", "a00012.html#aadad8a26aa23fe97db1b1ebf26a6d7a1", null ],
      [ "chipSelectDelay", "a00012.html#a6b4868a81aa300dd78374535af8a5993", null ],
      [ "samplePeriod", "a00012.html#ae1827f3ca16c86b5da47b2009be91c00", null ],
      [ "txFifoThreshold", "a00012.html#a04ef6f7d1d2914b3c28d8a6cf1cf2194", null ],
      [ "rxFifoThreshold", "a00012.html#ae83eee3dd8599490cde034beb9243170", null ],
      [ "baudRate_Bps", "a00012.html#a8b5fce2d680a7e33f0ca1c03108f5a50", null ],
      [ "enableLoopback", "a00012.html#aa8d6779d34787c5fd43a3cdf6a12b42d", null ]
    ] ],
    [ "ecspi_slave_config_t", "a00012.html#a00164", [
      [ "burstLength", "a00012.html#a47dc1fd0b2e1db49b4b0adb242cce23f", null ],
      [ "txFifoThreshold", "a00012.html#a878b083da83577aec35e0767d0e6842a", null ],
      [ "rxFifoThreshold", "a00012.html#a5b28b64178ee94d946c401519eeda64c", null ],
      [ "channelConfig", "a00012.html#af49e825bd581a557850df75f07e880ea", null ]
    ] ],
    [ "ecspi_transfer_t", "a00012.html#a00165", [
      [ "txData", "a00012.html#a024d7352f22d1a5b4e826cbc024581f0", null ],
      [ "rxData", "a00012.html#afc78bda57ee3f9b7d7d732ef02973c2c", null ],
      [ "dataSize", "a00012.html#ab2775e32b2da5edd97ca780106b17ca1", null ],
      [ "channel", "a00012.html#a6f085d63c254287974a6a9175befc55e", null ]
    ] ],
    [ "ecspi_master_handle_t", "a00012.html#a00137", [
      [ "channel", "a00012.html#aa6c13a233cdacc489cf97bc3cd0fb6f5", null ],
      [ "txData", "a00012.html#a32a4f2d44ea110f92b775e1ec7824063", null ],
      [ "rxData", "a00012.html#aadd279e36f9879f8d7ce4881861cbe6f", null ],
      [ "txRemainingBytes", "a00012.html#a3a4689219aa53ca5bdb63ce171d2285c", null ],
      [ "rxRemainingBytes", "a00012.html#ae6b19b31a8d8428a10088831ab03f27b", null ],
      [ "state", "a00012.html#aa07e9a421f101147c70b860b63b24d72", null ],
      [ "transferSize", "a00012.html#a072b80c6510d0d99ce8336ed8c33d6e1", null ],
      [ "callback", "a00012.html#acf5bbc4426afa7bea77b107dbc37652c", null ],
      [ "userData", "a00012.html#a3ed57ad9fe76002e40f129febe160654", null ]
    ] ],
    [ "FSL_ECSPI_DRIVER_VERSION", "a00012.html#ga49e359ce2a195388c177d885b5fd3e74", null ],
    [ "ECSPI_DUMMYDATA", "a00012.html#ga885f0195612ef6aa0d8e48aa644cea57", null ],
    [ "SPI_RETRY_TIMES", "a00012.html#gaa4717c15ca9604c505a5e5c60df29ebe", null ],
    [ "ecspi_slave_handle_t", "a00012.html#gaba2d0ab06e8ec3b144ce09b38717c73a", null ],
    [ "ecspi_master_callback_t", "a00012.html#ga6d23219efb6e309fb8b4cbd1edc86e98", null ],
    [ "ecspi_slave_callback_t", "a00012.html#ga14759db6a77598c3d0b901154129b58d", [
      [ "kStatus_ECSPI_Busy", "a00012.html#gga726ca809ffd3d67ab4b8476646f26635a8a46fcccbbfc30bb81a0f324c5f3d860", null ],
      [ "kStatus_ECSPI_Idle", "a00012.html#gga726ca809ffd3d67ab4b8476646f26635a7a5f40ca776d628f47310d95e68fa245", null ],
      [ "kStatus_ECSPI_Error", "a00012.html#gga726ca809ffd3d67ab4b8476646f26635acff86cd4db27adbb14cfdbc60cc4e04f", null ],
      [ "kStatus_ECSPI_HardwareOverFlow", "a00012.html#gga726ca809ffd3d67ab4b8476646f26635ad4e8224a416538ed087176bc033267e7", null ],
      [ "kStatus_ECSPI_Timeout", "a00012.html#gga726ca809ffd3d67ab4b8476646f26635abd5fecfe81ffd7963e65d0d3f7c99e9b", null ]
    ] ],
    [ "ecspi_clock_polarity_t", "a00012.html#gae0418192a24558da46fad3181ad2aac6", [
      [ "kECSPI_PolarityActiveHigh", "a00012.html#ggae0418192a24558da46fad3181ad2aac6a87b0cb4747fed7d6f25b0107ceea9a86", null ],
      [ "kECSPI_PolarityActiveLow", "a00012.html#ggae0418192a24558da46fad3181ad2aac6a2b62838dac3b0f2fe12f4d423636ff68", null ]
    ] ],
    [ "ecspi_clock_phase_t", "a00012.html#ga776487ec9cfe2ee52d26b62f4adc6878", [
      [ "kECSPI_ClockPhaseFirstEdge", "a00012.html#gga776487ec9cfe2ee52d26b62f4adc6878a3bd1e7add02733a4fdc701b55a28d83c", null ],
      [ "kECSPI_ClockPhaseSecondEdge", "a00012.html#gga776487ec9cfe2ee52d26b62f4adc6878acad0974595c9bbf39c64e1b11951a78b", null ],
      [ "kECSPI_TxfifoEmptyInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2daf3d3bd3c344fecda9888c66b63f9b2bc", null ],
      [ "kECSPI_TxFifoDataRequstInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da2550332987e4b2832993eec7571c102d", null ],
      [ "kECSPI_TxFifoFullInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2dab51c3b033fa2b8519a53a074be3ba6f7", null ],
      [ "kECSPI_RxFifoReadyInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da6113d2098b055e3f08420ce9e3ac2d4c", null ],
      [ "kECSPI_RxFifoDataRequstInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da58dfb462d67e67e437b6fdc9449b1b6f", null ],
      [ "kECSPI_RxFifoFullInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da98ffad56047a874910ff53ba36bcaf30", null ],
      [ "kECSPI_RxFifoOverFlowInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2daef5f1ecfd8cb6b4f6ea898169b1c96dd", null ],
      [ "kECSPI_TransferCompleteInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da759acc23595685c28efd304219dacd7c", null ],
      [ "kECSPI_AllInterruptEnable", "a00012.html#gga0411cd49bb5b71852cecd93bcbf0ca2da970cc4e4c20aa8a433953c4b3530b99f", null ],
      [ "kECSPI_TxfifoEmptyFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600ab655bd71113cf592dae74e2776a721dc", null ],
      [ "kECSPI_TxFifoDataRequstFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600acbb31605593949923e0d7f09c3859142", null ],
      [ "kECSPI_TxFifoFullFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600a72d999ee17dcca997f3cc9ac56647cf7", null ],
      [ "kECSPI_RxFifoReadyFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600a262aac414af41bb3db795e0aeb70b520", null ],
      [ "kECSPI_RxFifoDataRequstFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600a707210bff1488bdb9bfaa71ca043b810", null ],
      [ "kECSPI_RxFifoFullFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600a366f72bc39e182080c5e07d2922e490b", null ],
      [ "kECSPI_RxFifoOverFlowFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600aa5457be11d61af76cf8192ffe872f1c9", null ],
      [ "kECSPI_TransferCompleteFlag", "a00012.html#ggabed82baf7f470b522273a3e37c24c600a3ca312f3c579ca0524ae433a4bd2758f", null ],
      [ "kECSPI_TxDmaEnable", "a00012.html#ggab04a0655cd1e3bcac5e8f48c18df1a57af73555b2b4eb12d7fcab8774e9dfb34b", null ],
      [ "kECSPI_RxDmaEnable", "a00012.html#ggab04a0655cd1e3bcac5e8f48c18df1a57a53af55fec388ff98aafcfa4c947fc215", null ],
      [ "kECSPI_DmaAllEnable", "a00012.html#ggab04a0655cd1e3bcac5e8f48c18df1a57aef9846743f20a85f6429f16d7b98687d", null ]
    ] ],
    [ "ecspi_Data_ready_t", "a00012.html#ga3f9aab667da727ae384a6b76e09fd5c0", [
      [ "kECSPI_DataReadyIgnore", "a00012.html#gga3f9aab667da727ae384a6b76e09fd5c0ae840f8158fce546e682c6ab1710d90b0", null ],
      [ "kECSPI_DataReadyFallingEdge", "a00012.html#gga3f9aab667da727ae384a6b76e09fd5c0a77fc4d56d82923c8cb0fcc9e5521b647", null ],
      [ "kECSPI_DataReadyLowLevel", "a00012.html#gga3f9aab667da727ae384a6b76e09fd5c0af48e5a90d193e110bfd88dc1b4a5c0be", null ]
    ] ],
    [ "ecspi_channel_source_t", "a00012.html#ga0946f249a6cbdb8987baa5f4bd39a0ab", [
      [ "kECSPI_Channel0", "a00012.html#gga0946f249a6cbdb8987baa5f4bd39a0aba1ac961fb6f497e8ad9082fb07504e9c5", null ],
      [ "kECSPI_Channel1", "a00012.html#gga0946f249a6cbdb8987baa5f4bd39a0aba3186dfb67a1311c21c6fc81a845324db", null ],
      [ "kECSPI_Channel2", "a00012.html#gga0946f249a6cbdb8987baa5f4bd39a0aba16c4a01e134f7db5001f496b34bb080a", null ],
      [ "kECSPI_Channel3", "a00012.html#gga0946f249a6cbdb8987baa5f4bd39a0aba0993f73a469ede063091c7de076c006e", null ]
    ] ],
    [ "ecspi_master_slave_mode_t", "a00012.html#gaa8ffe589b98df551c09da7fbd5fd8149", [
      [ "kECSPI_Slave", "a00012.html#ggaa8ffe589b98df551c09da7fbd5fd8149a492c128adc36b27e968376463d339b6c", null ],
      [ "kECSPI_Master", "a00012.html#ggaa8ffe589b98df551c09da7fbd5fd8149afa1c745867b3076523985e99aad4b58a", null ]
    ] ],
    [ "ecspi_data_line_inactive_state_t", "a00012.html#ga7756b59f227697a8d4fe335a2f40fa74", [
      [ "kECSPI_DataLineInactiveStateHigh", "a00012.html#gga7756b59f227697a8d4fe335a2f40fa74ab9b16d2f8e51662551756b6923d8384b", null ],
      [ "kECSPI_DataLineInactiveStateLow", "a00012.html#gga7756b59f227697a8d4fe335a2f40fa74a6d736df09298222db7f060e5bf8dae35", null ]
    ] ],
    [ "ecspi_clock_inactive_state_t", "a00012.html#ga524b46a0bed966cf616715354a0468a2", [
      [ "kECSPI_ClockInactiveStateLow", "a00012.html#gga524b46a0bed966cf616715354a0468a2ac7c53cfc3b3a445bdb4eb3a78d3d236a", null ],
      [ "kECSPI_ClockInactiveStateHigh", "a00012.html#gga524b46a0bed966cf616715354a0468a2a8be6d1327a55926da4cc1504e3763475", null ]
    ] ],
    [ "ecspi_chip_select_active_state_t", "a00012.html#ga75ba01276811af8ffaef76e74173ac7b", [
      [ "kECSPI_ChipSelectActiveStateLow", "a00012.html#gga75ba01276811af8ffaef76e74173ac7ba9940e869c485c1f937b0b2f9b4f7a777", null ],
      [ "kECSPI_ChipSelectActiveStateHigh", "a00012.html#gga75ba01276811af8ffaef76e74173ac7bade90bcbe7e7f3cf34547cf8b67b965f9", null ]
    ] ],
    [ "ecspi_sample_period_clock_source_t", "a00012.html#ga8e15db09a9c66cb10350282507f3d5c6", [
      [ "kECSPI_spiClock", "a00012.html#gga8e15db09a9c66cb10350282507f3d5c6a86a48f9e83419196fadcc8189ed6e841", null ],
      [ "kECSPI_lowFreqClock", "a00012.html#gga8e15db09a9c66cb10350282507f3d5c6a02660ea6610c018123dd691c19939f5f", null ]
    ] ],
    [ "ECSPI_GetInstance", "a00012.html#gac93d90f992b4a279021a609ce3d76aff", null ],
    [ "ECSPI_MasterGetDefaultConfig", "a00012.html#ga3984ed3d0a8755835f1244334ff59f67", null ],
    [ "ECSPI_MasterInit", "a00012.html#ga26e03d859a266145121e60a94d84e04b", null ],
    [ "ECSPI_SlaveGetDefaultConfig", "a00012.html#ga76aa1e3db8310570d7621766958e4249", null ],
    [ "ECSPI_SlaveInit", "a00012.html#ga9d64d89082d59ff4634df9cfafd92401", null ],
    [ "ECSPI_Deinit", "a00012.html#ga684087107b71beeb41401d78f4983685", null ],
    [ "ECSPI_Enable", "a00012.html#ga2e4d1cabe92e6f4b35c540ba3c8b0308", null ],
    [ "ECSPI_GetStatusFlags", "a00012.html#gacebe36e1f278e18350d4bf971af2fc7e", null ],
    [ "ECSPI_ClearStatusFlags", "a00012.html#gaa437a7c7a740dfabb3f2296b0e989adf", null ],
    [ "ECSPI_EnableInterrupts", "a00012.html#gad3f9f4d11b99c104503aa4b7dda53833", null ],
    [ "ECSPI_DisableInterrupts", "a00012.html#gac9bac11d5dcd977a97a0607d77791ba1", null ],
    [ "ECSPI_SoftwareReset", "a00012.html#gadc13d57141df32cefbb4b0040e6404f6", null ],
    [ "ECSPI_IsMaster", "a00012.html#ga92268573eb4bcbb82d4cc2417ac4933a", null ],
    [ "ECSPI_EnableDMA", "a00012.html#gab2f7c2269309fd273f8e41f11833e313", null ],
    [ "ECSPI_GetTxFifoCount", "a00012.html#ga88e66c4f5f15754fb7ba7fc016f6dc41", null ],
    [ "ECSPI_GetRxFifoCount", "a00012.html#gaded76e7db6b46c3a53922a528d755c57", null ],
    [ "ECSPI_SetChannelSelect", "a00012.html#ga3175e7552062e74bffa3538195b8df6a", null ],
    [ "ECSPI_SetChannelConfig", "a00012.html#gaa4a223ca2612f4e73fae0982afcff226", null ],
    [ "ECSPI_SetBaudRate", "a00012.html#ga4b5b00f89c45cb1164af2a4685e984d5", null ],
    [ "ECSPI_WriteBlocking", "a00012.html#gab0233870c51a5096af0b247ec99014d0", null ],
    [ "ECSPI_WriteData", "a00012.html#ga99b6a9e30ad735c3634d60b81c500c2e", null ],
    [ "ECSPI_ReadData", "a00012.html#ga3c50b084acf2fe74f19575cc10069bbe", null ],
    [ "ECSPI_MasterTransferCreateHandle", "a00012.html#ga1ab5918361a605a7f0467bcb3d1760ac", null ],
    [ "ECSPI_MasterTransferBlocking", "a00012.html#ga20f68343a19b3772e814a8ee61d7be7f", null ],
    [ "ECSPI_MasterTransferNonBlocking", "a00012.html#gad77408a45d6982958068a49149ac60b6", null ],
    [ "ECSPI_MasterTransferGetCount", "a00012.html#ga85aef57f678a64cbe3e718ec59043841", null ],
    [ "ECSPI_MasterTransferAbort", "a00012.html#gacda4c03d5c4b1c2ba78578ff5213a2f5", null ],
    [ "ECSPI_MasterTransferHandleIRQ", "a00012.html#gada190053bf71b9ce53a619b7d6c7c245", null ],
    [ "ECSPI_SlaveTransferCreateHandle", "a00012.html#ga63b3bb057b97b1115ad082e9e056632b", null ],
    [ "ECSPI_SlaveTransferNonBlocking", "a00012.html#gad4a51681f1b62b0f26be844a209e6e10", null ],
    [ "ECSPI_SlaveTransferGetCount", "a00012.html#gacea2421bc4aaee6e9cc19f7d4f48e3e5", null ],
    [ "ECSPI_SlaveTransferAbort", "a00012.html#ga2512b5ae1d6591e8ba1d70f15221c689", null ],
    [ "ECSPI_SlaveTransferHandleIRQ", "a00012.html#ga8bc32a537b99b7e988228650957f25d8", null ]
];