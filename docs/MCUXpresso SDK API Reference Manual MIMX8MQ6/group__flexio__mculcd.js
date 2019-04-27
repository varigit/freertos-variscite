var group__flexio__mculcd =
[
    [ "FlexIO eDMA MCU Interface LCD Driver", "group__flexio__edma__mculcd.html", "group__flexio__edma__mculcd" ],
    [ "FLEXIO_MCULCD_Type", "group__flexio__mculcd.html#structFLEXIO__MCULCD__Type", [
      [ "flexioBase", "group__flexio__mculcd.html#abf2b6adbb0db513d52fcb5f40c02a2b1", null ],
      [ "busType", "group__flexio__mculcd.html#a36a8730492f2b1f4e059db4e5419609c", null ],
      [ "dataPinStartIndex", "group__flexio__mculcd.html#adb0e01a30225a21919c2889e69283ff6", null ],
      [ "ENWRPinIndex", "group__flexio__mculcd.html#a3e118bd09ffc6506a31c91c026790a5f", null ],
      [ "RDPinIndex", "group__flexio__mculcd.html#a73b8476bbca6a7c72d02f07a6c717a72", null ],
      [ "txShifterStartIndex", "group__flexio__mculcd.html#a07f087030bdde6b2b1fb74ec4cd7ec9f", null ],
      [ "txShifterEndIndex", "group__flexio__mculcd.html#a142fc31119a18ad79cc347d872b41258", null ],
      [ "rxShifterStartIndex", "group__flexio__mculcd.html#a33116db2624e27651064ce2cc52d0b54", null ],
      [ "rxShifterEndIndex", "group__flexio__mculcd.html#a2f0d20608d6392ab2c0d913981ecc2b3", null ],
      [ "timerIndex", "group__flexio__mculcd.html#a41a8218e90069d0907e7fbdd8e9960a0", null ],
      [ "setCSPin", "group__flexio__mculcd.html#a39fedbabf47cc113657120a921188fd7", null ],
      [ "setRSPin", "group__flexio__mculcd.html#a49c806eebd7c0a7f7bd19050d87f978a", null ],
      [ "setRDWRPin", "group__flexio__mculcd.html#a528162f7f3a5eeca0a7533131ffd6792", null ]
    ] ],
    [ "flexio_mculcd_config_t", "group__flexio__mculcd.html#structflexio__mculcd__config__t", [
      [ "enable", "group__flexio__mculcd.html#aec7f75c47425865274cb6e3a59e375e5", null ],
      [ "enableInDoze", "group__flexio__mculcd.html#a4979ef759a7da0411f944c8341bb5d29", null ],
      [ "enableInDebug", "group__flexio__mculcd.html#a06d679c4a415fc922cdcb7d31aa7a227", null ],
      [ "enableFastAccess", "group__flexio__mculcd.html#ac485f769dab33c787197bff31507bae7", null ],
      [ "baudRate_Bps", "group__flexio__mculcd.html#a3a36a9832963afadadba0d2937d4c879", null ]
    ] ],
    [ "flexio_mculcd_transfer_t", "group__flexio__mculcd.html#structflexio__mculcd__transfer__t", [
      [ "command", "group__flexio__mculcd.html#aa447f012ca360d9b06b569879f0342c7", null ],
      [ "mode", "group__flexio__mculcd.html#ac69465289fcc81b805c8ee84d4f5f526", null ],
      [ "dataAddrOrSameValue", "group__flexio__mculcd.html#a8dc56304688ac3d2ecf1084316e06202", null ],
      [ "dataSize", "group__flexio__mculcd.html#ac9fefa4bb4e9dbf94a8769d5dc6369f4", null ]
    ] ],
    [ "flexio_mculcd_handle_t", "group__flexio__mculcd.html#struct__flexio__mculcd__handle", [
      [ "dataAddrOrSameValue", "group__flexio__mculcd.html#afd6b5ba7856e4a60b09284d8648927f6", null ],
      [ "dataCount", "group__flexio__mculcd.html#a96a7d3183ca79dc52ea96f1cf3cdaee1", null ],
      [ "remainingCount", "group__flexio__mculcd.html#a84abb6b0e289e316142b979d5e937b26", null ],
      [ "state", "group__flexio__mculcd.html#a16ed075abcf8c2f5d3604abb200a19fb", null ],
      [ "completionCallback", "group__flexio__mculcd.html#a64d9f1044cf8d50ff94e2626373ca43f", null ],
      [ "userData", "group__flexio__mculcd.html#a42bd1c4946df77d6f11b1c06481c2c48", null ]
    ] ],
    [ "FSL_FLEXIO_MCULCD_DRIVER_VERSION", "group__flexio__mculcd.html#gafe7ea67ab39450e0c1d774db6da66748", null ],
    [ "FLEXIO_MCULCD_WAIT_COMPLETE_TIME", "group__flexio__mculcd.html#gad4820c07952c35d8111bff9731b181cd", null ],
    [ "FLEXIO_MCULCD_DATA_BUS_WIDTH", "group__flexio__mculcd.html#ga99d509e0e5dae07eefc11c826e91aa20", null ],
    [ "flexio_mculcd_pin_func_t", "group__flexio__mculcd.html#ga488a641aac28ea18d6126851f5c6b181", null ],
    [ "flexio_mculcd_transfer_callback_t", "group__flexio__mculcd.html#ga9c5e282fd6d1cae13dc533a106a3da23", null ],
    [ "_flexio_mculcd_status", "group__flexio__mculcd.html#ga596727a1e93037ba51455460f2b24bb9", [
      [ "kStatus_FLEXIO_MCULCD_Idle", "group__flexio__mculcd.html#gga596727a1e93037ba51455460f2b24bb9a2dff5d93dfb65bc74ebfc97dd185517f", null ],
      [ "kStatus_FLEXIO_MCULCD_Busy", "group__flexio__mculcd.html#gga596727a1e93037ba51455460f2b24bb9a04c11c9c91be5814653e720200470e62", null ],
      [ "kStatus_FLEXIO_MCULCD_Error", "group__flexio__mculcd.html#gga596727a1e93037ba51455460f2b24bb9afa90a745e2b170d4e7b9e3b6d4ef7074", null ]
    ] ],
    [ "flexio_mculcd_bus_t", "group__flexio__mculcd.html#gaa17db8a882f5f3fe15456cb122260d19", [
      [ "kFLEXIO_MCULCD_8080", "group__flexio__mculcd.html#ggaa17db8a882f5f3fe15456cb122260d19a1f2ac09da8933f9e57b942a59e863085", null ],
      [ "kFLEXIO_MCULCD_6800", "group__flexio__mculcd.html#ggaa17db8a882f5f3fe15456cb122260d19aa4675f6cdc5c469fbc20c4eb7e655037", null ]
    ] ],
    [ "_flexio_mculcd_interrupt_enable", "group__flexio__mculcd.html#gaae20f091cb4c5e097d422acd027c4e53", [
      [ "kFLEXIO_MCULCD_TxEmptyInterruptEnable", "group__flexio__mculcd.html#ggaae20f091cb4c5e097d422acd027c4e53a541cab9de040225d78aff57f72e5dc17", null ],
      [ "kFLEXIO_MCULCD_RxFullInterruptEnable", "group__flexio__mculcd.html#ggaae20f091cb4c5e097d422acd027c4e53ab8cd4be55b8e2476f81eb1b247ba6b4a", null ]
    ] ],
    [ "_flexio_mculcd_status_flags", "group__flexio__mculcd.html#ga1115ba328b8237943367dcf1243d0383", [
      [ "kFLEXIO_MCULCD_TxEmptyFlag", "group__flexio__mculcd.html#gga1115ba328b8237943367dcf1243d0383a034bbb18f24ba508fd3154c44744236f", null ],
      [ "kFLEXIO_MCULCD_RxFullFlag", "group__flexio__mculcd.html#gga1115ba328b8237943367dcf1243d0383a16aab9d49fb5edf16a4c3b9a78b48a62", null ]
    ] ],
    [ "_flexio_mculcd_dma_enable", "group__flexio__mculcd.html#ga05d200ee8911ec4a25ff67a3b00d4399", [
      [ "kFLEXIO_MCULCD_TxDmaEnable", "group__flexio__mculcd.html#gga05d200ee8911ec4a25ff67a3b00d4399a9f641b7f44a9a5b941b01d8a5c368fd0", null ],
      [ "kFLEXIO_MCULCD_RxDmaEnable", "group__flexio__mculcd.html#gga05d200ee8911ec4a25ff67a3b00d4399ad33c9f0d9303c626389c1bfe7480b391", null ]
    ] ],
    [ "flexio_mculcd_transfer_mode_t", "group__flexio__mculcd.html#ga55d4cd02882552a32f3fc1f6c5603de5", [
      [ "kFLEXIO_MCULCD_ReadArray", "group__flexio__mculcd.html#gga55d4cd02882552a32f3fc1f6c5603de5a9ad8b512c6d9588dafea9c7fdf056abe", null ],
      [ "kFLEXIO_MCULCD_WriteArray", "group__flexio__mculcd.html#gga55d4cd02882552a32f3fc1f6c5603de5a92d2d1a92d55debf0b9a8a11b0c3ebbf", null ],
      [ "kFLEXIO_MCULCD_WriteSameValue", "group__flexio__mculcd.html#gga55d4cd02882552a32f3fc1f6c5603de5ada670943bd6afbdfb31cc3ceb8095e96", null ]
    ] ],
    [ "FLEXIO_MCULCD_Init", "group__flexio__mculcd.html#gadf487d6481b434db73d3ba7c12eac135", null ],
    [ "FLEXIO_MCULCD_Deinit", "group__flexio__mculcd.html#ga364629429e78e49bf62b9379aaca0059", null ],
    [ "FLEXIO_MCULCD_GetDefaultConfig", "group__flexio__mculcd.html#gad635328d02e4ea3029647f99aaef6825", null ],
    [ "FLEXIO_MCULCD_GetStatusFlags", "group__flexio__mculcd.html#ga50c2ea78f7380e90029006dbb6c6567b", null ],
    [ "FLEXIO_MCULCD_ClearStatusFlags", "group__flexio__mculcd.html#ga8774960515b3f986997d1b2a50a00a98", null ],
    [ "FLEXIO_MCULCD_EnableInterrupts", "group__flexio__mculcd.html#ga380b9affdffd32f92360e5052e81af13", null ],
    [ "FLEXIO_MCULCD_DisableInterrupts", "group__flexio__mculcd.html#ga6889e2dd21f510d3076d6806a5cbd3db", null ],
    [ "FLEXIO_MCULCD_EnableTxDMA", "group__flexio__mculcd.html#gafbb11d6e80f294456646d6b3334068a1", null ],
    [ "FLEXIO_MCULCD_EnableRxDMA", "group__flexio__mculcd.html#ga7d502fbdf74b6d359e201efc1002aa91", null ],
    [ "FLEXIO_MCULCD_GetTxDataRegisterAddress", "group__flexio__mculcd.html#ga678e005c9ace311c8ad1478659bcc582", null ],
    [ "FLEXIO_MCULCD_GetRxDataRegisterAddress", "group__flexio__mculcd.html#ga16509f7b06b29fed63984998e6e2cd15", null ],
    [ "FLEXIO_MCULCD_SetBaudRate", "group__flexio__mculcd.html#ga70af865987db6e3790b85c53efde41c3", null ],
    [ "FLEXIO_MCULCD_SetSingleBeatWriteConfig", "group__flexio__mculcd.html#gaca5282756ad79ee4bb83e0630b8d79b7", null ],
    [ "FLEXIO_MCULCD_ClearSingleBeatWriteConfig", "group__flexio__mculcd.html#ga015873a3c1c7d4a9e052fca0987b1244", null ],
    [ "FLEXIO_MCULCD_SetSingleBeatReadConfig", "group__flexio__mculcd.html#ga7c5f2081f91455329156e2c5241f977d", null ],
    [ "FLEXIO_MCULCD_ClearSingleBeatReadConfig", "group__flexio__mculcd.html#ga1f71d3040f5514a1078dcbef106b1724", null ],
    [ "FLEXIO_MCULCD_SetMultiBeatsWriteConfig", "group__flexio__mculcd.html#gaea5f907193346fd69f29062f63809385", null ],
    [ "FLEXIO_MCULCD_ClearMultiBeatsWriteConfig", "group__flexio__mculcd.html#ga9d833f8dbabaa1f05226739c0342ee6b", null ],
    [ "FLEXIO_MCULCD_SetMultiBeatsReadConfig", "group__flexio__mculcd.html#ga090661b0490fc986674cc5be24c86d5e", null ],
    [ "FLEXIO_MCULCD_ClearMultiBeatsReadConfig", "group__flexio__mculcd.html#ga5353455708f60c557437d6efc30bb7d4", null ],
    [ "FLEXIO_MCULCD_Enable", "group__flexio__mculcd.html#ga90187643fdfbc55f40fd5ab2a5ff33da", null ],
    [ "FLEXIO_MCULCD_ReadData", "group__flexio__mculcd.html#ga17a7674235c3924980d530d0d19d6e8c", null ],
    [ "FLEXIO_MCULCD_WriteData", "group__flexio__mculcd.html#ga4af2f413701c4e9a07f05eede894954d", null ],
    [ "FLEXIO_MCULCD_StartTransfer", "group__flexio__mculcd.html#ga806a41ef95febb0fe0d46b71a645e390", null ],
    [ "FLEXIO_MCULCD_StopTransfer", "group__flexio__mculcd.html#ga05b6ed9dfe511b544ea1b0c2542d0aa6", null ],
    [ "FLEXIO_MCULCD_WaitTransmitComplete", "group__flexio__mculcd.html#ga214fc1863c4a15a4fb3898a926b39bf5", null ],
    [ "FLEXIO_MCULCD_WriteCommandBlocking", "group__flexio__mculcd.html#ga6e62bd4a886f252a9c35de3d3f00c053", null ],
    [ "FLEXIO_MCULCD_WriteDataArrayBlocking", "group__flexio__mculcd.html#gab853acd9b2dc7fbb0ec892cded822b82", null ],
    [ "FLEXIO_MCULCD_ReadDataArrayBlocking", "group__flexio__mculcd.html#ga94f8fbe3c2bb214f0d6297ff7149d9ef", null ],
    [ "FLEXIO_MCULCD_WriteSameValueBlocking", "group__flexio__mculcd.html#gaf31c4a57c7aa5a309d6b400cd5a416e2", null ],
    [ "FLEXIO_MCULCD_TransferBlocking", "group__flexio__mculcd.html#gabf1077e74cabc35b87abfa22ad31eddd", null ],
    [ "FLEXIO_MCULCD_TransferCreateHandle", "group__flexio__mculcd.html#ga6b7ade08a56ca89861e1fca6998ac2f2", null ],
    [ "FLEXIO_MCULCD_TransferNonBlocking", "group__flexio__mculcd.html#ga784cd1cf213eb02669b781ff2500d23c", null ],
    [ "FLEXIO_MCULCD_TransferAbort", "group__flexio__mculcd.html#gaf7231251cc0eaf135b3a6d57e5dcf65a", null ],
    [ "FLEXIO_MCULCD_TransferGetCount", "group__flexio__mculcd.html#ga0468b17e6bf6f681a7f1d77ad7464399", null ],
    [ "FLEXIO_MCULCD_TransferHandleIRQ", "group__flexio__mculcd.html#ga0a868861318bdcd8c91557a6196365b7", null ]
];