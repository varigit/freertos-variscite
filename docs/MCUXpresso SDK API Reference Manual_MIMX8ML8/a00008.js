var a00008 =
[
    [ "asrc_data_format_t", "a00008.html#a00153", [
      [ "dataPosition", "a00008.html#a4581e73b38540c5a6890dfef99d6b9fd", null ],
      [ "dataEndianness", "a00008.html#a9b866b26ec40c86786fafc66804f7301", null ],
      [ "dataWidth", "a00008.html#a47bd47be08dac714c1e3ffb89736a0b4", null ],
      [ "dataType", "a00008.html#a8352973a0c98187dcc15018f33393422", null ],
      [ "dataSign", "a00008.html#a1c7649e688acab6a31ea4d0012c41985", null ]
    ] ],
    [ "asrc_access_ctrl_t", "a00008.html#a00147", [
      [ "accessIterations", "a00008.html#a21b93594b378c67d50e1e8db05bb50b0", null ],
      [ "accessGroupLen", "a00008.html#af1c1fd23d31acb8dac962cafd4a39921", null ],
      [ "accessLen", "a00008.html#a32095169c0d829744b30d9cbc8e84f7e", null ]
    ] ],
    [ "asrc_context_input_config_t", "a00008.html#a00149", [
      [ "sampleRate", "a00008.html#a52b2a9bc93036d786d114f94253ba93e", null ],
      [ "watermark", "a00008.html#a77e60e767e4829911f76ed2f6165dbb1", null ],
      [ "accessCtrl", "a00008.html#ad929e1e5919afdeea7a77f263526ae61", null ],
      [ "dataFormat", "a00008.html#a79a94f894c413de1f693008b921baeab", null ]
    ] ],
    [ "asrc_context_output_config_t", "a00008.html#a00150", [
      [ "sampleRate", "a00008.html#a7218fedb61ee8a22f39ea3097348e671", null ],
      [ "watermark", "a00008.html#a0f03d520112abf2a0a9a9ed2e25acae8", null ],
      [ "accessCtrl", "a00008.html#adb077e59466e13f352a581c2b88e7e57", null ],
      [ "dataFormat", "a00008.html#a1d1026c14cce903d42cfd5e9a785412a", null ],
      [ "enableDither", "a00008.html#adcbd780345b3cbabedff99398c7f0733", null ],
      [ "enableIEC60958", "a00008.html#a5ef8a02a4e68ebc113694f6cc77d775b", null ]
    ] ],
    [ "asrc_context_prefilter_config_t", "a00008.html#a00151", [
      [ "initMode", "a00008.html#a7cbacd163ead86bab8f8433ccaa7daca", null ],
      [ "stopMode", "a00008.html#aed5c3fca9a11f679a5ca656582282ae9", null ],
      [ "stage1Result", "a00008.html#a6134a0408d42ae652b133d0e9cec080d", null ],
      [ "filterSt1Taps", "a00008.html#a4abf778798ac8f6ba1c3e3b6f7896cbd", null ],
      [ "filterSt2Taps", "a00008.html#a01c2cdc5593e354d5ea47867f2517d5e", null ],
      [ "filterSt1Exp", "a00008.html#afa7f5af74d274554cadd25d4197aeb0b", null ],
      [ "filterCoeffAddress", "a00008.html#a2aefe38124e3b985075f6aa00a3df841", null ]
    ] ],
    [ "asrc_context_resampler_config_t", "a00008.html#a00152", [
      [ "initMode", "a00008.html#a6e6cfcaa5271e2b11afcdc1426474e15", null ],
      [ "stopMode", "a00008.html#a0817584cd068a2a88c7eb9a4f52da75e", null ],
      [ "tap", "a00008.html#a2192fc25d544723189e2f655c0afa550", null ],
      [ "filterPhases", "a00008.html#a5d872c907c97db3d6ffacc715856a6cb", null ],
      [ "filterCenterTap", "a00008.html#a36e03a0de995597dada504ecdcc99783", null ],
      [ "filterCoeffAddress", "a00008.html#aef8e2549a0405601125d3a2ef3e5f4e8", null ]
    ] ],
    [ "asrc_context_config_t", "a00008.html#a00148", [
      [ "contextChannelNums", "a00008.html#a2540461b0df2289d02945f18b7783e05", null ],
      [ "contextInput", "a00008.html#ac0c8e499f3d01af236d5bc3875200766", null ],
      [ "contextOutput", "a00008.html#ada4483f50a7a21f0893f764246b4ee3d", null ],
      [ "contextPrefilter", "a00008.html#a1f20ddedf50313db8711835f9935e670", null ],
      [ "contextResampler", "a00008.html#a57c2247585303e8d2b2489c8d0ae54b4", null ]
    ] ],
    [ "asrc_transfer_t", "a00008.html#a00157", [
      [ "inDataAddr", "a00008.html#a789df757ad0418966358f6608c263a8e", null ],
      [ "inDataSize", "a00008.html#a19e41a6dd58dc8b1b03a93c9dad00c07", null ],
      [ "outDataAddr", "a00008.html#ab2038ba02b5fd5c56be730e515c03283", null ],
      [ "outDataSize", "a00008.html#a19173474808ea73d53201508eddbbaad", null ]
    ] ],
    [ "FSL_ASRC_DRIVER_VERSION", "a00008.html#gafae92ba17d0248f0e79417358c6738ba", null ],
    [ "FSL_ASRC_INPUT_FIFO_DEPTH", "a00008.html#ga1c00fe44c4fe17840ba566836c132a93", null ],
    [ "ASRC_SUPPORT_MAXIMUM_CONTEXT_PROCESSOR_NUMBER", "a00008.html#gaa285c8bd0eb74e6212214ea58e77da4f", [
      [ "kStatus_ASRCIdle", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a45ecbd7bc54a0ee7dd4b93e7fb1bb97b", null ],
      [ "kStatus_ASRCBusy", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5ac8e0c682fb431151e5f2fd3e5e43c83f", null ],
      [ "kStatus_ASRCInvalidArgument", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a5504887bed84dbbef9df36553d4046b6", null ],
      [ "kStatus_ASRCConfigureFailed", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5af98cd1977d02aab096776c5fad2ac2db", null ],
      [ "kStatus_ASRCConvertError", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5ab27f5060223a080e1e52ad98b56ce43a", null ],
      [ "kStatus_ASRCNotSupport", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a7d615a0ac8fc067f428da0d89dc97da1", null ],
      [ "kStatus_ASRCQueueFull", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5af079bf800b2287cb7fa1c4b2e2792050", null ],
      [ "kStatus_ASRCQueueIdle", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a61e0a51c98b80e6ea9d45a9b19d00f13", null ],
      [ "kStatus_ASRCLoadFirmwareFailed", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a863ecb7b6ed02a4e5c228d67f76d9912", null ],
      [ "kStatus_ASRCResamplerConfigureFailed", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a0da8ecd9451008bd1459a3d6f6d8bc14", null ],
      [ "kStatus_ASRCPrefilterConfigureFailed", "a00008.html#gga99fb83031ce9923c84392b4e92f956b5a284526c2f0dd3d68b898daae2d5ab918", null ]
    ] ],
    [ "asrc_context_t", "a00008.html#ga023e61e315535ac95996c1ae64ecc857", [
      [ "kASRC_Context0", "a00008.html#gga023e61e315535ac95996c1ae64ecc857aeaea0e8f1b0cb0459ad9e27080ce1349", null ],
      [ "kASRC_Context1", "a00008.html#gga023e61e315535ac95996c1ae64ecc857a87c986440dee6fc28841328438f5f9ce", null ],
      [ "kASRC_Context2", "a00008.html#gga023e61e315535ac95996c1ae64ecc857a9858d15e7de683d9cb8ebd03a7457df8", null ],
      [ "kASRC_Context3", "a00008.html#gga023e61e315535ac95996c1ae64ecc857a3885526fe612c1030b9a41901ff0fd33", null ],
      [ "kASRC_Context0InputFifoOverflow", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04aea9c40bc1cfdd4c7bd8de39462346365", null ],
      [ "kASRC_Context1InputFifoOverflow", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a5c17ef4990019d508a3f707ae7f2ab88", null ],
      [ "kASRC_Context2InputFifoOverflow", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04acac40e1c8e9a07196d797e5bf3d27ba4", null ],
      [ "kASRC_Context3InputFifoOverflow", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a4e93878babc23962d66e74d68dd78db5", null ],
      [ "kASRC_Context0OutFifoReadEmpty", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04ab0623ff44d3d339e843d7263d75ff2d5", null ],
      [ "kASRC_Context1OutFifoReadEmpty", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a04b0a0767272d244799a5f8a24f91853", null ],
      [ "kASRC_Context2OutFifoReadEmpty", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a6261d02e42d2bd5330becf3337b2632d", null ],
      [ "kASRC_Context3OutFifoReadEmpty", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04abbbbdc507b9fe2b4685195c7dbb0ca34", null ],
      [ "kASRC_Context0RunStopDone", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04adac66d1c9ca69a44d0221f7117ad75d4", null ],
      [ "kASRC_Context1RunStopDone", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a0628d2a3f385d2d474c69904aab94f4b", null ],
      [ "kASRC_Context2RunStopDone", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04aa0992a600d71226965c31761fd34dc27", null ],
      [ "kASRC_Context3RunStopDone", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a2692b8233097d447bffb55232dfba67e", null ],
      [ "kASRC_ContextAllInterruptStatus", "a00008.html#ggabc6126af1d45847bc59afa0aa3216b04a3076a07a496f6cd5f70deec544fb32b8", null ],
      [ "kASRC_FifoStatusInputFifoWatermarkFlag", "a00008.html#ggadc29c2ff13d900c2f185ee95427fb06caf75a38c3ff4c5e493fe7b6796a4883be", null ],
      [ "kASRC_FifoStatusOutputFifoWatermarkFlag", "a00008.html#ggadc29c2ff13d900c2f185ee95427fb06ca888cb71e9d1e773330e4e02d4a008295", null ]
    ] ],
    [ "asrc_data_endianness_t", "a00008.html#gaac4bb7d45fe5a0d26263caa77d516964", [
      [ "kASRC_DataEndianLittle", "a00008.html#ggaac4bb7d45fe5a0d26263caa77d516964a6a4ae9ae15cbb05ac9e5afa828d52116", null ],
      [ "kASRC_DataEndianBig", "a00008.html#ggaac4bb7d45fe5a0d26263caa77d516964aa5bb1354eae5629e369d08e300333553", null ]
    ] ],
    [ "asrc_data_width_t", "a00008.html#gaea1d8db6dc0effbb7b93348a6095eaad", [
      [ "kASRC_DataWidth32Bit", "a00008.html#ggaea1d8db6dc0effbb7b93348a6095eaada4d5a0b8596d5b1e74cb9ea2c29446913", null ],
      [ "kASRC_DataWidth24Bit", "a00008.html#ggaea1d8db6dc0effbb7b93348a6095eaada54c8fb38fbb5d80079f8dd04e76183fc", null ],
      [ "kASRC_DataWidth20Bit", "a00008.html#ggaea1d8db6dc0effbb7b93348a6095eaada8bcf76acc035afa8d24e9f981a9036a9", null ],
      [ "kASRC_DataWidth16Bit", "a00008.html#ggaea1d8db6dc0effbb7b93348a6095eaada75bdfffc838219e49cf4636baa41115c", null ]
    ] ],
    [ "asrc_data_type_t", "a00008.html#ga7fcddbcbfcbefbe0df151c2ff44aba7b", [
      [ "kASRC_DataTypeInteger", "a00008.html#gga7fcddbcbfcbefbe0df151c2ff44aba7ba6c5d712be172a949f003b3ba401f548d", null ],
      [ "kASRC_DataTypeFloat", "a00008.html#gga7fcddbcbfcbefbe0df151c2ff44aba7bafc4edd7b3242d4757a8a00de236e0413", null ]
    ] ],
    [ "asrc_data_sign_t", "a00008.html#ga6e07278be3ee1341a4de87140a39e95f", [
      [ "kASRC_DataSigned", "a00008.html#gga6e07278be3ee1341a4de87140a39e95fa3eff1eb4149b84b93b9f6d57978464ba", null ],
      [ "kASRC_DataUnsigned", "a00008.html#gga6e07278be3ee1341a4de87140a39e95fa491b4b0d171cbe00cf32fa0db68ecaac", null ]
    ] ],
    [ "asrc_sampleBuffer_init_mode_t", "a00008.html#gabb95bdb67a9a256d5761bc4a6fe01674", [
      [ "kASRC_SampleBufferNoPreFillOnInit", "a00008.html#ggabb95bdb67a9a256d5761bc4a6fe01674a09dfd192866e36446e759706b4506dd5", null ],
      [ "kASRC_SampleBufferFillFirstSampleOnInit", "a00008.html#ggabb95bdb67a9a256d5761bc4a6fe01674acd5881ecde48b28011e8a37100fd2967", null ],
      [ "kASRC_SampleBufferFillZeroOnInit", "a00008.html#ggabb95bdb67a9a256d5761bc4a6fe01674a9efa52d2202ef415262bfe1e87a5ebb2", null ]
    ] ],
    [ "asrc_sampleBuffer_stop_mode_t", "a00008.html#gab974fe3616cb6f5ad96e3eaa52593c2f", [
      [ "kASRC_SampleBufferFillLastSampleOnStop", "a00008.html#ggab974fe3616cb6f5ad96e3eaa52593c2fa5a5a42260e09f39d0aac79f1f3b870cc", null ],
      [ "kASRC_SampleBufferFillZeroOnStop", "a00008.html#ggab974fe3616cb6f5ad96e3eaa52593c2fa8e33c927d786e6304b2097a53ba724ce", null ]
    ] ],
    [ "asrc_prefilter_stage1_result_t", "a00008.html#ga10ab17fc0f36a201d88b3afd28a2e731", [
      [ "kASRC_PrefilterStage1ResultInt", "a00008.html#gga10ab17fc0f36a201d88b3afd28a2e731adefd96c249f7691ceb477d90ae62ec59", null ],
      [ "kASRC_PrefilterStage1ResultFloat", "a00008.html#gga10ab17fc0f36a201d88b3afd28a2e731a873645a8bb4be32f13629391f8170ae9", null ]
    ] ],
    [ "asrc_resampler_taps_t", "a00008.html#gacd9cd1d2b8c7b66304935a9611f37078", [
      [ "kASRC_ResamplerTaps_32", "a00008.html#ggacd9cd1d2b8c7b66304935a9611f37078ac107aa6d77a67651f61505b625badfb8", null ],
      [ "kASRC_ResamplerTaps_64", "a00008.html#ggacd9cd1d2b8c7b66304935a9611f37078aeb8a26debc8d8a812e00b4e8cb9dcf5c", null ],
      [ "kASRC_ResamplerTaps_128", "a00008.html#ggacd9cd1d2b8c7b66304935a9611f37078a861ce74df75d7c4a415b2b9d997ecd8e", null ],
      [ "kASRC_SampleRate_8000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea05072ddafbb1a9a45ed6ef9b99e2c1fd", null ],
      [ "kASRC_SampleRate_11025", "a00008.html#gga61dadd085c1777f559549e05962b2c9ead3d5377c94fdae64c8f74ead5fe8c801", null ],
      [ "kASRC_SampleRate_12000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea33e2da4f3cc9cf68c30842d96896b852", null ],
      [ "kASRC_SampleRate_16000", "a00008.html#gga61dadd085c1777f559549e05962b2c9eae3c86108ebc805aed400a71fb3885d26", null ],
      [ "kASRC_SampleRate_22050", "a00008.html#gga61dadd085c1777f559549e05962b2c9eab6e296cf83f9226141c551e52e95539d", null ],
      [ "kASRC_SampleRate_24000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea4ecbb85b59ad2b9e8b3f98035ef30f89", null ],
      [ "kASRC_SampleRate_32000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea669b5a95225eba261c1e979085402c58", null ],
      [ "kASRC_SampleRate_44100", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea123ecb1e68bbd123e29ac859f338dd30", null ],
      [ "kASRC_SampleRate_48000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea5bc48be50acad51adf73b0d60d6f8083", null ],
      [ "kASRC_SampleRate_64000", "a00008.html#gga61dadd085c1777f559549e05962b2c9eab3bb895c8549436b13878262cd78526d", null ],
      [ "kASRC_SampleRate_88200", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea4bf375020694d9fc3d10bfa8fc65a189", null ],
      [ "kASRC_SampleRate_96000", "a00008.html#gga61dadd085c1777f559549e05962b2c9eaa9127934318f9b9390fea6087d1a53c0", null ],
      [ "kASRC_SampleRate_128000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea7b182e3dbcf33c16426face8e4af2b98", null ],
      [ "kASRC_SampleRate_176400", "a00008.html#gga61dadd085c1777f559549e05962b2c9eacc5ded026e49bcb65308a4c7c2a9cf41", null ],
      [ "kASRC_SampleRate_192000", "a00008.html#gga61dadd085c1777f559549e05962b2c9eaa9c47399cb66399964f20d42bb78889f", null ],
      [ "kASRC_SampleRate_256000", "a00008.html#gga61dadd085c1777f559549e05962b2c9eaff923180ae391703d0296b71856ed609", null ],
      [ "kASRC_SampleRate_352800", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea8a8b7773108f88a6e07f64487cde5400", null ],
      [ "kASRC_SampleRate_384000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ea7c9763cfca037c60ba44fc7e34dd507f", null ],
      [ "kASRC_SampleRate_768000", "a00008.html#gga61dadd085c1777f559549e05962b2c9ead302c1532b1310fb506fab0a16755ca0", null ]
    ] ],
    [ "ASRC_GetInstance", "a00008.html#ga7f2a01d5abd8c0e5713c934cfe8e6c9c", null ],
    [ "ASRC_Init", "a00008.html#gaf8cb4f4e7ad6cd930d314c6f88bc991e", null ],
    [ "ASRC_Deinit", "a00008.html#ga3e4c828478709d1c144a18ccadeb37b1", null ],
    [ "ASRC_GetContextDefaultConfig", "a00008.html#ga4b9208dc8c8065e33ed16f8234f61ebd", null ],
    [ "ASRC_SetContextConfig", "a00008.html#ga55442a5dc7460e8a0d3b20685444601d", null ],
    [ "ASRC_SetContextOutputConfig", "a00008.html#ga966bf8ededee3ba20eae4329a269bc18", null ],
    [ "ASRC_SetContextInputConfig", "a00008.html#ga55d83f12b004e85b3e9ea9f37d771d4e", null ],
    [ "ASRC_EnableContextRun", "a00008.html#gae9a7716ad96d0e3eb20bff976f675646", null ],
    [ "ASRC_EnableContextRunStop", "a00008.html#gafb7a7d9a3e019c17818012d8c57e5d7c", null ],
    [ "ASRC_EnableContextInDMA", "a00008.html#ga52a589069a08e904c6a0d3cae88b760f", null ],
    [ "ASRC_EnableContextOutDMA", "a00008.html#gacc992f532dfdee6a3ce144d3d6740c56", null ],
    [ "ASRC_EnablePreFilterBypass", "a00008.html#ga008ef79f1e2798628d330b7f60a224c1", null ],
    [ "ASRC_EnableResamplerBypass", "a00008.html#gaa46d31eafa4e88281a39cbce2f164a27", null ],
    [ "ASRC_SetContextChannelNumber", "a00008.html#ga3de70de63a9579a4c43aaef2335da23e", null ],
    [ "ASRC_GetContextOutSampleSize", "a00008.html#gac52013a76bae1ba80d9756d421f61ad8", null ],
    [ "ASRC_EnableInterrupt", "a00008.html#ga0e80f27121214e10238be5c8711575f8", null ],
    [ "ASRC_DisableInterrupt", "a00008.html#gae684b1ec612343f73b00fc7ac445acab", null ],
    [ "ASRC_GetInterruptStatus", "a00008.html#gab05addcd9f068968972e3f41a5902927", null ],
    [ "ASRC_ClearInterruptStatus", "a00008.html#ga3b628bda9cff566be6b2da900245707c", null ],
    [ "ASRC_GetFifoStatus", "a00008.html#ga1c602083218bf0857edfe9ceaa4e4056", null ],
    [ "ASRC_WriteContextFifo", "a00008.html#gac2483fea275eca15b0333de0b1898bec", null ],
    [ "ASRC_ReadContextFifo", "a00008.html#ga7122081ad191336bd35461e6a96c0ede", null ],
    [ "ASRC_GetWriteContextFifoAddr", "a00008.html#ga509996e83eee60b25df879464b83eae3", null ],
    [ "ASRC_GetReadContextFifoAddr", "a00008.html#gaab790cfbce64809bbddb988c90196f9b", null ],
    [ "ASRC_ReadFIFORemainedSample", "a00008.html#ga8ec081a7cae4710f2c3de127adcc1582", null ],
    [ "ASRC_TransferBlocking", "a00008.html#ga9e6afc7152b544575e42c7a8bf6e745d", null ]
];