var group__sai__driver =
[
    [ "sai_config_t", "group__sai__driver.html#structsai__config__t", [
      [ "protocol", "group__sai__driver.html#ae6b6e06a6051825c0797e1ab7fce5f92", null ],
      [ "syncMode", "group__sai__driver.html#a1c625b880a5721c9bf58ab081c08fea5", null ],
      [ "bclkSource", "group__sai__driver.html#a156dc7868da25bfc262bfac4bd4499a1", null ],
      [ "masterSlave", "group__sai__driver.html#a2c16d7b69db892ed087ced965280be77", null ]
    ] ],
    [ "sai_transfer_format_t", "group__sai__driver.html#structsai__transfer__format__t", [
      [ "sampleRate_Hz", "group__sai__driver.html#a629aeb07579875fda77e38851c683ae0", null ],
      [ "bitWidth", "group__sai__driver.html#ad4f8f19e4e01850841127ca7d0920302", null ],
      [ "stereo", "group__sai__driver.html#a1398f0cd36eabc05f7bc448db6355562", null ],
      [ "masterClockHz", "group__sai__driver.html#a26e51457310ccb2a7cfeb7eec8068ae7", null ],
      [ "watermark", "group__sai__driver.html#a8ba95ed67ac358a1b7fed626cd9400f1", null ],
      [ "channel", "group__sai__driver.html#ac9e9a371b0922bb1a82b2a06e11b9d70", null ],
      [ "channelMask", "group__sai__driver.html#af4da9c845f2ec3f203d928d395425bcd", null ],
      [ "endChannel", "group__sai__driver.html#a9df5dc7f7f43d168c4c32cba863248cc", null ],
      [ "channelNums", "group__sai__driver.html#a549071723581d7ac31f2fd5521a5bbb7", null ],
      [ "protocol", "group__sai__driver.html#a2df4853c14ae76c214bddc23787e2327", null ],
      [ "isFrameSyncCompact", "group__sai__driver.html#ada875cc5c68938e26714e01ac909cc25", null ]
    ] ],
    [ "sai_transfer_t", "group__sai__driver.html#structsai__transfer__t", [
      [ "data", "group__sai__driver.html#a5a8e66b73932caa8eaf99df59127e389", null ],
      [ "dataSize", "group__sai__driver.html#a9518c75eb06dadc3b73f44ee49f4e0ff", null ]
    ] ],
    [ "sai_handle_t", "group__sai__driver.html#struct__sai__handle", [
      [ "base", "group__sai__driver.html#a39a102177f33c97feccda8cdfa9c7335", null ],
      [ "state", "group__sai__driver.html#a5b505d55e77d3b5329b368d3007ce816", null ],
      [ "callback", "group__sai__driver.html#a05bc395932b5262476fa9a10fde9ede5", null ],
      [ "userData", "group__sai__driver.html#a593e606183fad166fae74bd5e5cc70b5", null ],
      [ "bitWidth", "group__sai__driver.html#a6031e7b8e826009f5f2964b6a53bb66b", null ],
      [ "channel", "group__sai__driver.html#a0f25131b0b0e2f2e7483848697465d5e", null ],
      [ "channelMask", "group__sai__driver.html#acbd7a834bc182707e4c0bad51237bee5", null ],
      [ "endChannel", "group__sai__driver.html#aea72f72f07a29659472ac0eb557ef17b", null ],
      [ "channelNums", "group__sai__driver.html#aeadd85773c1b99966f2e0dc37bc225ef", null ],
      [ "saiQueue", "group__sai__driver.html#ae598be176e033f2849b6bd567e1a09bc", null ],
      [ "transferSize", "group__sai__driver.html#a43e75ec27110a0e71ebfbc0be8d69c25", null ],
      [ "queueUser", "group__sai__driver.html#a9bc00ccd6c986f28ca3cbd0c45469b59", null ],
      [ "queueDriver", "group__sai__driver.html#a18dfdb245cb737f8a66976b707d3d487", null ],
      [ "watermark", "group__sai__driver.html#aebd37d24e2151d811652ee8de4873f40", null ]
    ] ],
    [ "FSL_SAI_DRIVER_VERSION", "group__sai__driver.html#ga90d7087431db03b22516e7a311aebeb1", null ],
    [ "SAI_XFER_QUEUE_SIZE", "group__sai__driver.html#ga580bf35fe1f08d7bb054bee399f8b085", null ],
    [ "sai_transfer_callback_t", "group__sai__driver.html#gacda077e13dd34cd0fa1e865354591fe2", null ],
    [ "_sai_status_t", "group__sai__driver.html#ga143ecba4f3b3e833be0c38baeab02330", [
      [ "kStatus_SAI_TxBusy", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330ae095b9b1a3ec7b998d722b1e1d73ca44", null ],
      [ "kStatus_SAI_RxBusy", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a8e432517b16b5784a72a95e0caf7bb4a", null ],
      [ "kStatus_SAI_TxError", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a5f17818e41e2fb07e35e43e1a03bfeb9", null ],
      [ "kStatus_SAI_RxError", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a0d8c8cec03abcd722d2ec4358451461c", null ],
      [ "kStatus_SAI_QueueFull", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a19680647d09a7437afd6b6ae7013095e", null ],
      [ "kStatus_SAI_TxIdle", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a2a58fb377508baa31df58beb5f406761", null ],
      [ "kStatus_SAI_RxIdle", "group__sai__driver.html#gga143ecba4f3b3e833be0c38baeab02330a0f398d330abd6df4255be13d39968e1d", null ]
    ] ],
    [ "_sai_channel_mask", "group__sai__driver.html#ga40c4c1562c52fc3b25faba766b037926", [
      [ "kSAI_Channel0Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926aa21f6e0475cce1ba88f8105ab4f692c7", null ],
      [ "kSAI_Channel1Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926a4f8ec142406d199623daa8671b62285b", null ],
      [ "kSAI_Channel2Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926a4d28325c4e3225b6bc90a3e6da72943b", null ],
      [ "kSAI_Channel3Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926aebd450167bf4da5b7825b633a76b50f7", null ],
      [ "kSAI_Channel4Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926a028b3c77f8f6d83b5f53d889751b41fb", null ],
      [ "kSAI_Channel5Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926a2e64fd8c9b0cb2ae5366f03129f65553", null ],
      [ "kSAI_Channel6Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926a15f0e04bf2f22b27d472d09730bb1290", null ],
      [ "kSAI_Channel7Mask", "group__sai__driver.html#gga40c4c1562c52fc3b25faba766b037926aed34fb3a4004a734740d463a3544ef1d", null ]
    ] ],
    [ "sai_protocol_t", "group__sai__driver.html#gad13dff47e2ed5ce5d8eae47df8ac8e0f", [
      [ "kSAI_BusLeftJustified", "group__sai__driver.html#ggad13dff47e2ed5ce5d8eae47df8ac8e0fa5c6ddb713e2ebd5e243d5d8156869baf", null ],
      [ "kSAI_BusRightJustified", "group__sai__driver.html#ggad13dff47e2ed5ce5d8eae47df8ac8e0faebff095e8a510ada79aab2c90df6c4ef", null ],
      [ "kSAI_BusI2S", "group__sai__driver.html#ggad13dff47e2ed5ce5d8eae47df8ac8e0fa67d163f59267b3c6f6dfb731de711197", null ],
      [ "kSAI_BusPCMA", "group__sai__driver.html#ggad13dff47e2ed5ce5d8eae47df8ac8e0fa1a4da830cfb4f08554a690de65d2870f", null ],
      [ "kSAI_BusPCMB", "group__sai__driver.html#ggad13dff47e2ed5ce5d8eae47df8ac8e0fa6b5e627cbe3644cf561eb0997699aefe", null ]
    ] ],
    [ "sai_master_slave_t", "group__sai__driver.html#gaa968c964aac0ab72a6957d89cb7b5bb0", [
      [ "kSAI_Master", "group__sai__driver.html#ggaa968c964aac0ab72a6957d89cb7b5bb0ace27a481cd1aee827602f2997e9e9d24", null ],
      [ "kSAI_Slave", "group__sai__driver.html#ggaa968c964aac0ab72a6957d89cb7b5bb0afc74ad2cca556b75857bfcb3c2f754b3", null ]
    ] ],
    [ "sai_mono_stereo_t", "group__sai__driver.html#ga23ffdf03cf1409d3385f3ead175a97c4", [
      [ "kSAI_Stereo", "group__sai__driver.html#gga23ffdf03cf1409d3385f3ead175a97c4a68780a0cf179c054ccccdd0d57fb780e", null ],
      [ "kSAI_MonoRight", "group__sai__driver.html#gga23ffdf03cf1409d3385f3ead175a97c4a2763e95289b6d3f7015cba718964580b", null ],
      [ "kSAI_MonoLeft", "group__sai__driver.html#gga23ffdf03cf1409d3385f3ead175a97c4a06bf33c6e548abd3cd5136b4e8d7bd29", null ]
    ] ],
    [ "sai_data_order_t", "group__sai__driver.html#ga671f20a72e99f08a11498b79d7259e05", [
      [ "kSAI_DataLSB", "group__sai__driver.html#gga671f20a72e99f08a11498b79d7259e05ad5ea6f8b25daf462e099db5959a58c8f", null ],
      [ "kSAI_DataMSB", "group__sai__driver.html#gga671f20a72e99f08a11498b79d7259e05a810e97cb159dd3e4009a98bf91e829c5", null ]
    ] ],
    [ "sai_clock_polarity_t", "group__sai__driver.html#ga311302fe418002fddb7b0e553e73d22d", [
      [ "kSAI_PolarityActiveHigh", "group__sai__driver.html#gga311302fe418002fddb7b0e553e73d22dae61dfe51028ddaa2f902dd74b6804d7b", null ],
      [ "kSAI_PolarityActiveLow", "group__sai__driver.html#gga311302fe418002fddb7b0e553e73d22da53b413986854f303b7661f25619b755f", null ]
    ] ],
    [ "sai_sync_mode_t", "group__sai__driver.html#ga88390dba856027f775cac9e6f6ecbc17", [
      [ "kSAI_ModeAsync", "group__sai__driver.html#gga88390dba856027f775cac9e6f6ecbc17a1eedfe4039fefc137958a911f67840c1", null ],
      [ "kSAI_ModeSync", "group__sai__driver.html#gga88390dba856027f775cac9e6f6ecbc17a8a39fe8640d0a3a2de851e41bc3ebbdd", null ],
      [ "kSAI_ModeSyncWithOtherTx", "group__sai__driver.html#gga88390dba856027f775cac9e6f6ecbc17a87f5fdf3addd5b7dcb91d6bca043a791", null ],
      [ "kSAI_ModeSyncWithOtherRx", "group__sai__driver.html#gga88390dba856027f775cac9e6f6ecbc17ac3992e47e86faa518c9b1b26da64aa5c", null ]
    ] ],
    [ "sai_mclk_source_t", "group__sai__driver.html#gad4559fc57adfd1eb3596f03d9012e5ae", [
      [ "kSAI_MclkSourceSysclk", "group__sai__driver.html#ggad4559fc57adfd1eb3596f03d9012e5aeaa996ab18c8b18160b7b70b7b23eecb8d", null ],
      [ "kSAI_MclkSourceSelect1", "group__sai__driver.html#ggad4559fc57adfd1eb3596f03d9012e5aeac5a9692e8334ad2542c5a9221704ac22", null ],
      [ "kSAI_MclkSourceSelect2", "group__sai__driver.html#ggad4559fc57adfd1eb3596f03d9012e5aea18d79884e3de46ce85e46560ac84e04c", null ],
      [ "kSAI_MclkSourceSelect3", "group__sai__driver.html#ggad4559fc57adfd1eb3596f03d9012e5aea148502f7a9db92e579c19cb0d78db2cf", null ]
    ] ],
    [ "sai_bclk_source_t", "group__sai__driver.html#ga4922f5f6332e7cb0715b6ebf70a4bf87", [
      [ "kSAI_BclkSourceBusclk", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87a76edb348d999ad21e50f9d46d46f7e4c", null ],
      [ "kSAI_BclkSourceMclkOption1", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87a04244436208c8b2b8e7c56989a08f842", null ],
      [ "kSAI_BclkSourceMclkOption2", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87a2452df30e11c7cc88eae97720aca2765", null ],
      [ "kSAI_BclkSourceMclkOption3", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87a3f7799293e0d637f15cf0685c9ee1c5c", null ],
      [ "kSAI_BclkSourceMclkDiv", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87ab4c297bd65ee5ef56c49808b8ac0d94d", null ],
      [ "kSAI_BclkSourceOtherSai0", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87ab812a4070f7960ee602e14c9af93873f", null ],
      [ "kSAI_BclkSourceOtherSai1", "group__sai__driver.html#gga4922f5f6332e7cb0715b6ebf70a4bf87a4174df66b1e3f83cd8456564517c25b6", null ]
    ] ],
    [ "_sai_interrupt_enable_t", "group__sai__driver.html#ga842f8f2052288ad264dd45e8b652feb3", [
      [ "kSAI_WordStartInterruptEnable", "group__sai__driver.html#gga842f8f2052288ad264dd45e8b652feb3a544d76157d9e4e99a322e31b03f2de99", null ],
      [ "kSAI_SyncErrorInterruptEnable", "group__sai__driver.html#gga842f8f2052288ad264dd45e8b652feb3a3adb555d2455aa86878f78a0c0ef6566", null ],
      [ "kSAI_FIFOWarningInterruptEnable", "group__sai__driver.html#gga842f8f2052288ad264dd45e8b652feb3a0557da436cdad3e9551e4c2ab3319526", null ],
      [ "kSAI_FIFOErrorInterruptEnable", "group__sai__driver.html#gga842f8f2052288ad264dd45e8b652feb3a1eb2783c3d30845f08cb7b613d92d84b", null ],
      [ "kSAI_FIFORequestInterruptEnable", "group__sai__driver.html#gga842f8f2052288ad264dd45e8b652feb3aba8ca41b00b881e5d7507e3d20974831", null ]
    ] ],
    [ "_sai_dma_enable_t", "group__sai__driver.html#ga77974e76dbf8ccb44e36eb003a159443", [
      [ "kSAI_FIFOWarningDMAEnable", "group__sai__driver.html#gga77974e76dbf8ccb44e36eb003a159443aa6bcd82f3ff9e711f85f1c05ff288eab", null ],
      [ "kSAI_FIFORequestDMAEnable", "group__sai__driver.html#gga77974e76dbf8ccb44e36eb003a159443a8d208db72a30ce3625803ba11f292086", null ]
    ] ],
    [ "_sai_flags", "group__sai__driver.html#ga68a5da2423e4fc5dc11ed493b0b3bb93", [
      [ "kSAI_WordStartFlag", "group__sai__driver.html#gga68a5da2423e4fc5dc11ed493b0b3bb93a8856ff23f0703c9a170163edcee534ea", null ],
      [ "kSAI_SyncErrorFlag", "group__sai__driver.html#gga68a5da2423e4fc5dc11ed493b0b3bb93ad35f8fa189ca7adc41905dc692aea237", null ],
      [ "kSAI_FIFOErrorFlag", "group__sai__driver.html#gga68a5da2423e4fc5dc11ed493b0b3bb93a66affbcb587814dc0df6f12733ea3f5c", null ],
      [ "kSAI_FIFORequestFlag", "group__sai__driver.html#gga68a5da2423e4fc5dc11ed493b0b3bb93af90c6aca78ac96fb694157d3a8dc6388", null ],
      [ "kSAI_FIFOWarningFlag", "group__sai__driver.html#gga68a5da2423e4fc5dc11ed493b0b3bb93a41f8ba146a17136cebefb1ef142c4563", null ]
    ] ],
    [ "sai_reset_type_t", "group__sai__driver.html#gae33638b9b4e26245e21faa2ed10bbf7f", [
      [ "kSAI_ResetTypeSoftware", "group__sai__driver.html#ggae33638b9b4e26245e21faa2ed10bbf7fa67ca93a283d762ba72176ef609bc4134", null ],
      [ "kSAI_ResetTypeFIFO", "group__sai__driver.html#ggae33638b9b4e26245e21faa2ed10bbf7fa9749b5efe5bb45db10089360992a683a", null ],
      [ "kSAI_ResetAll", "group__sai__driver.html#ggae33638b9b4e26245e21faa2ed10bbf7fae75ddd8d7c742dce4aef59aff2c81f38", null ]
    ] ],
    [ "sai_fifo_packing_t", "group__sai__driver.html#ga0741098d4c9a5a481746c2c27980e4ad", [
      [ "kSAI_FifoPackingDisabled", "group__sai__driver.html#gga0741098d4c9a5a481746c2c27980e4adae267a04864a1f653962222a90909472f", null ],
      [ "kSAI_FifoPacking8bit", "group__sai__driver.html#gga0741098d4c9a5a481746c2c27980e4ada547adf2b9d268fb205d939b617aba68e", null ],
      [ "kSAI_FifoPacking16bit", "group__sai__driver.html#gga0741098d4c9a5a481746c2c27980e4adae1d4fb3eb871e1d1f51a75a97d00bc2c", null ]
    ] ],
    [ "sai_sample_rate_t", "group__sai__driver.html#ga8d668e297c3e93bbc326c44538fefce5", [
      [ "kSAI_SampleRate8KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a33faf3aa4adc2430b4892a60bf82f847", null ],
      [ "kSAI_SampleRate11025Hz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a20a0ee7adde7aca59883b3f7b5698d98", null ],
      [ "kSAI_SampleRate12KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5ab6f2876028ff4201e6e9411bd450e5e9", null ],
      [ "kSAI_SampleRate16KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a37f8460732967ce92f540c44d89b45ae", null ],
      [ "kSAI_SampleRate22050Hz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a932187b8e03e6c60e5f6665f55e3f209", null ],
      [ "kSAI_SampleRate24KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5aec9824e27135f9641e61399b0c7ee72c", null ],
      [ "kSAI_SampleRate32KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5aa745cb456e46ad4982c3d58882fb34a0", null ],
      [ "kSAI_SampleRate44100Hz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5aa00db6732444bb1976f130b8a283276c", null ],
      [ "kSAI_SampleRate48KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a3539b8834c98c260c99b6092e7766cfc", null ],
      [ "kSAI_SampleRate96KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a345e0cda3185af26335f3720e0691aca", null ],
      [ "kSAI_SampleRate192KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5afa3d9a8a48ca6981ec61aeacfbf75a32", null ],
      [ "kSAI_SampleRate384KHz", "group__sai__driver.html#gga8d668e297c3e93bbc326c44538fefce5a137ad38af2b993bb54c46289478fc517", null ]
    ] ],
    [ "sai_word_width_t", "group__sai__driver.html#gae357d8842863ba610f57acd1e1f35528", [
      [ "kSAI_WordWidth8bits", "group__sai__driver.html#ggae357d8842863ba610f57acd1e1f35528ac282421ee51ea251da06e459af3014a1", null ],
      [ "kSAI_WordWidth16bits", "group__sai__driver.html#ggae357d8842863ba610f57acd1e1f35528a0328fc45f36f361f958cacd8378d4923", null ],
      [ "kSAI_WordWidth24bits", "group__sai__driver.html#ggae357d8842863ba610f57acd1e1f35528a98f99f6e508d609333313277057d29a0", null ],
      [ "kSAI_WordWidth32bits", "group__sai__driver.html#ggae357d8842863ba610f57acd1e1f35528a238d482a0f4a707bc199f5c54c168233", null ]
    ] ],
    [ "SAI_TxInit", "group__sai__driver.html#gae30b99a76b3189b36d19cff113a42fdf", null ],
    [ "SAI_RxInit", "group__sai__driver.html#gacc398a5283804e04e006218810070e57", null ],
    [ "SAI_TxGetDefaultConfig", "group__sai__driver.html#gacea3121e96a50e2ceb2dee437aac8c56", null ],
    [ "SAI_RxGetDefaultConfig", "group__sai__driver.html#gac047637738322f87496c5ccc8fdf20d1", null ],
    [ "SAI_Deinit", "group__sai__driver.html#gae3acf95d83128d355a2935bb7ccd85ea", null ],
    [ "SAI_TxReset", "group__sai__driver.html#ga66657a9e3eb593e979389cc1136fd277", null ],
    [ "SAI_RxReset", "group__sai__driver.html#ga76c8fce1a9222a408a073873a27430f0", null ],
    [ "SAI_TxEnable", "group__sai__driver.html#ga32b2f06766a8bb92dd778a152dfd8b2e", null ],
    [ "SAI_RxEnable", "group__sai__driver.html#gaeaa118415a867f016efa6af3e0d06e17", null ],
    [ "SAI_TxGetStatusFlag", "group__sai__driver.html#ga1cd557fc5610173b3f5007f9594db2ae", null ],
    [ "SAI_TxClearStatusFlags", "group__sai__driver.html#ga11127bb45b18dfa9d897046ab69b218d", null ],
    [ "SAI_RxGetStatusFlag", "group__sai__driver.html#ga9857a73c0d40d12438a9bd336e237dfe", null ],
    [ "SAI_RxClearStatusFlags", "group__sai__driver.html#ga3329969cbf718114c37f10d88e527669", null ],
    [ "SAI_TxSoftwareReset", "group__sai__driver.html#ga5130499a5c0da79e9ddfa9882c2f8328", null ],
    [ "SAI_RxSoftwareReset", "group__sai__driver.html#ga3884861b9de4eb9dacd5f45d98a974d7", null ],
    [ "SAI_TxSetChannelFIFOMask", "group__sai__driver.html#ga633f5af270fa98e7dad379a2c78b4d72", null ],
    [ "SAI_RxSetChannelFIFOMask", "group__sai__driver.html#ga7fd29bef62a3d5609a78bb25f6fb66d6", null ],
    [ "SAI_TxSetDataOrder", "group__sai__driver.html#ga27fad059ad2e1ef81ef83fbce4284e13", null ],
    [ "SAI_RxSetDataOrder", "group__sai__driver.html#gaa5e0af3f06391d2577d3dfb42912ef85", null ],
    [ "SAI_TxSetBitClockPolarity", "group__sai__driver.html#ga18cb5b7f55e8ef0b25f1caf78a5b8a79", null ],
    [ "SAI_RxSetBitClockPolarity", "group__sai__driver.html#ga9847aa9eedcf6a08a77874d80e5fa54e", null ],
    [ "SAI_TxSetFrameSyncPolarity", "group__sai__driver.html#gafbbd4e7253ad01bb527c83cc3c41a09f", null ],
    [ "SAI_RxSetFrameSyncPolarity", "group__sai__driver.html#gae0b73b62039762bea3d43d846e3aa0f5", null ],
    [ "SAI_TxSetFIFOPacking", "group__sai__driver.html#ga837e2e4efa7401415cf3a922baa1b8e7", null ],
    [ "SAI_RxSetFIFOPacking", "group__sai__driver.html#ga69676e9585362f036f2d925481c21a26", null ],
    [ "SAI_TxSetFIFOErrorContinue", "group__sai__driver.html#gacfdf75b35fffd1931f6c412f7156f14d", null ],
    [ "SAI_RxSetFIFOErrorContinue", "group__sai__driver.html#ga2e5a3ad4e715bb1116eed303ef87c8a2", null ],
    [ "SAI_TxEnableInterrupts", "group__sai__driver.html#gae298cb3fe881e951a8e291028d7cf3df", null ],
    [ "SAI_RxEnableInterrupts", "group__sai__driver.html#ga43c4f7cbaf1188f9fd15c8c3a017870a", null ],
    [ "SAI_TxDisableInterrupts", "group__sai__driver.html#ga5baa11cc20615c1a9b32eea5f6021e66", null ],
    [ "SAI_RxDisableInterrupts", "group__sai__driver.html#ga9cbeb122b61a580d052438157661c46f", null ],
    [ "SAI_TxEnableDMA", "group__sai__driver.html#ga131a59354eae81bb20068b7c5e805f9a", null ],
    [ "SAI_RxEnableDMA", "group__sai__driver.html#ga8061229e53203dfca2ed45b2f7648ca5", null ],
    [ "SAI_TxGetDataRegisterAddress", "group__sai__driver.html#gac19d42fce7cc3f6ab68f279be959f3bb", null ],
    [ "SAI_RxGetDataRegisterAddress", "group__sai__driver.html#ga2b90519b672bb8cb8b0aa6386f66c251", null ],
    [ "SAI_TxSetFormat", "group__sai__driver.html#gaeeab03e24aa74980dd770d9e740c0b06", null ],
    [ "SAI_RxSetFormat", "group__sai__driver.html#ga542afa36d64a6848bf174cb0e695b42b", null ],
    [ "SAI_WriteBlocking", "group__sai__driver.html#ga32e4d2e732142517cc9ae2c1d12ee641", null ],
    [ "SAI_WriteMultiChannelBlocking", "group__sai__driver.html#gaf7dc2b062b866a82bbc1798eda2b7f7c", null ],
    [ "SAI_WriteData", "group__sai__driver.html#ga6299cd60dee1e684683f3473a62e831b", null ],
    [ "SAI_ReadBlocking", "group__sai__driver.html#ga0f954b031a8e2a857a0fddf87a9a1368", null ],
    [ "SAI_ReadMultiChannelBlocking", "group__sai__driver.html#ga85217823bf3acbe6616f1dc325f7a87b", null ],
    [ "SAI_ReadData", "group__sai__driver.html#gada44ab158250b8e94258b9d8fd3a63dd", null ],
    [ "SAI_TransferTxCreateHandle", "group__sai__driver.html#ga69eaf09522d88c69b47ec104c11875de", null ],
    [ "SAI_TransferRxCreateHandle", "group__sai__driver.html#ga4c29a38ae0802fa81e304eee337ecf6b", null ],
    [ "SAI_TransferTxSetFormat", "group__sai__driver.html#ga636cdc91fc752587bfd449fbf5f540bb", null ],
    [ "SAI_TransferRxSetFormat", "group__sai__driver.html#gaf9253863ef8232b06e82b5c6b69f20c1", null ],
    [ "SAI_TransferSendNonBlocking", "group__sai__driver.html#gaefe0557861a223913d7b1d8959a56995", null ],
    [ "SAI_TransferReceiveNonBlocking", "group__sai__driver.html#gad23a55af8054fbd0cb8cbb175f2e497c", null ],
    [ "SAI_TransferGetSendCount", "group__sai__driver.html#gac2b7aaa215232aa8e12eb751b0edd90f", null ],
    [ "SAI_TransferGetReceiveCount", "group__sai__driver.html#gafb739944ba12a66543842993c1716464", null ],
    [ "SAI_TransferAbortSend", "group__sai__driver.html#ga9fca6aa3b5cbcf05ca2c0b6637b476e7", null ],
    [ "SAI_TransferAbortReceive", "group__sai__driver.html#gab2859ed8b6805a962d45d5eb16a9095f", null ],
    [ "SAI_TransferTerminateSend", "group__sai__driver.html#ga9dcd9e96ab549fc44f5a9d521c87ab87", null ],
    [ "SAI_TransferTerminateReceive", "group__sai__driver.html#ga4770cca8a45e8fa32026850dcd721981", null ],
    [ "SAI_TransferTxHandleIRQ", "group__sai__driver.html#ga40d3fede9289fcea2706679138ce466a", null ],
    [ "SAI_TransferRxHandleIRQ", "group__sai__driver.html#gab66ff18cc17137d132a3b5c8accbdb34", null ]
];