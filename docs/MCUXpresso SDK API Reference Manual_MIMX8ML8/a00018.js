var a00018 =
[
    [ "_i2c_master_config", "a00018.html#a00198", [
      [ "enableMaster", "a00018.html#a7a58fd313d0615ac1ca70d2b4f17ae9a", null ],
      [ "baudRate_Bps", "a00018.html#a282b6a9bd8e98bf35e8183665488d98c", null ]
    ] ],
    [ "_i2c_master_transfer", "a00018.html#a00200", [
      [ "flags", "a00018.html#a84861e140902bd67ae901b2f4c53bfc0", null ],
      [ "slaveAddress", "a00018.html#aa6d93caa78fc9bf0f0aac10f66b8eba1", null ],
      [ "direction", "a00018.html#a7bd3afcf89b78d9397b2f0c55f9deb27", null ],
      [ "subaddress", "a00018.html#a7a4f43a16e63d9f286bc41b6255b5e3f", null ],
      [ "subaddressSize", "a00018.html#a810393f12a8bd6360e04b79ea83fcf3b", null ],
      [ "data", "a00018.html#a89a3ac8137ef778590d0ab3581187a60", null ],
      [ "dataSize", "a00018.html#a2e4cb139c00e6dd854232d4b2bfcf87a", null ]
    ] ],
    [ "_i2c_master_handle", "a00018.html#a00199", [
      [ "transfer", "a00018.html#a403d5da02efab45e1ebb8bef2ae063d5", null ],
      [ "transferSize", "a00018.html#aab5058b059faf2268848645a1b204cfe", null ],
      [ "state", "a00018.html#ade67a2d6339836711ee255a18405e750", null ],
      [ "completionCallback", "a00018.html#a0c6862e22cf2047661ce05975756093a", null ],
      [ "userData", "a00018.html#a862e1a312eb8b2bd537f1a22a48f455f", null ]
    ] ],
    [ "_i2c_slave_config", "a00018.html#a00201", [
      [ "enableSlave", "a00018.html#ad720331a891010209a1209585056a2b7", null ],
      [ "slaveAddress", "a00018.html#a60784d4b0182f877068255d5c2f54732", null ]
    ] ],
    [ "_i2c_slave_transfer", "a00018.html#a00203", [
      [ "event", "a00018.html#a461d482d4a91765e8820b55b17e7e53c", null ],
      [ "data", "a00018.html#a0d4fde45f82fa9dfdb7d13d4e123a894", null ],
      [ "dataSize", "a00018.html#a59fbecd8b66464de8013c39e40eb4b30", null ],
      [ "completionStatus", "a00018.html#a5c09cb680bd188a4176823b6dfa21335", null ],
      [ "transferredCount", "a00018.html#aae53c04dd44495a5f8cf8813e715a53e", null ]
    ] ],
    [ "_i2c_slave_handle", "a00018.html#a00202", [
      [ "state", "a00018.html#a238db96c276b4536be2290d2fe37d230", null ],
      [ "transfer", "a00018.html#a1dc2ffa11e396aad054370efeb3f2510", null ],
      [ "eventMask", "a00018.html#a769c9b64e73a1ddb99dfbf8cbc244b14", null ],
      [ "callback", "a00018.html#aa1a2ab536368e7b2e8981879f1a3f5ca", null ],
      [ "userData", "a00018.html#a0c21a56aa399763f1969a28fbea35054", null ]
    ] ],
    [ "FSL_I2C_DRIVER_VERSION", "a00018.html#ga60fdaec284298758a650ce1122aef231", null ],
    [ "I2C_RETRY_TIMES", "a00018.html#gaac288786aaa7d0cb947c91591baf42d7", null ],
    [ "i2c_direction_t", "a00018.html#ga4bf954d998f086594eece268c780bec7", null ],
    [ "i2c_master_config_t", "a00018.html#gad739710b6b65e12ca5ba9dc2a2a2b463", null ],
    [ "i2c_master_handle_t", "a00018.html#ga2fd51f58b8cfd309be985bce4b817fdc", null ],
    [ "i2c_master_transfer_callback_t", "a00018.html#ga1c6e059706357c744c165ce7ecd1c185", null ],
    [ "i2c_master_transfer_t", "a00018.html#ga0e25c3c153992361c8d359a86b70d3c6", null ],
    [ "i2c_slave_transfer_event_t", "a00018.html#ga95f120f6a73af41648364538cf9a6eca", null ],
    [ "i2c_slave_handle_t", "a00018.html#ga394e5278816efe62815de9d25be84752", null ],
    [ "i2c_slave_config_t", "a00018.html#gaa70dd0ec9815617269569190efd2de5d", null ],
    [ "i2c_slave_transfer_t", "a00018.html#ga69e696cb21165bc58176475879a471cf", null ],
    [ "i2c_slave_transfer_callback_t", "a00018.html#ga974310ded85af5ef341811d542db650c", [
      [ "kStatus_I2C_Busy", "a00018.html#gga0ed680fdb405e7195d9f14032851eebba49091894b590d7e479605bf113918952", null ],
      [ "kStatus_I2C_Idle", "a00018.html#gga0ed680fdb405e7195d9f14032851eebba628d242f7bc0e3d5949c7f73eafaa508", null ],
      [ "kStatus_I2C_Nak", "a00018.html#gga0ed680fdb405e7195d9f14032851eebba72fd33d0b5263a63766e62f71d16be00", null ],
      [ "kStatus_I2C_ArbitrationLost", "a00018.html#gga0ed680fdb405e7195d9f14032851eebba139b52cc3305ec2c06d0ac94313c221f", null ],
      [ "kStatus_I2C_Timeout", "a00018.html#gga0ed680fdb405e7195d9f14032851eebba81ad7cc198436cabbe91ea55c5288747", null ],
      [ "kStatus_I2C_Addr_Nak", "a00018.html#gga0ed680fdb405e7195d9f14032851eebbadf7437bfedcc0d57338ed33f1be5c805", null ]
    ] ],
    [ "_i2c_flags", "a00018.html#ga1f1337bbe9d0b184d9dcee31f9ebade2", [
      [ "kI2C_ReceiveNakFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a4c3c2928e17ddbfbc1c346c6b9a8dccd", null ],
      [ "kI2C_IntPendingFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a647d0b1d1f9514ad483bef3ea3926c3b", null ],
      [ "kI2C_TransferDirectionFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a249f698970909f33b1b96139c05bd969", null ],
      [ "kI2C_ArbitrationLostFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a39fab5ef04e74d00ef4c4574899ab589", null ],
      [ "kI2C_BusBusyFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a37fb20742a15a63c1bc2551b997cdcff", null ],
      [ "kI2C_AddressMatchFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a10cd5797b1b8f809192423486a85d5fe", null ],
      [ "kI2C_TransferCompleteFlag", "a00018.html#gga1f1337bbe9d0b184d9dcee31f9ebade2adb8f10365dfc2a3e849f05173fa4d83e", null ]
    ] ],
    [ "_i2c_interrupt_enable", "a00018.html#ga87c81dd985dad07dc26cb93125a94ec7", [
      [ "kI2C_GlobalInterruptEnable", "a00018.html#gga87c81dd985dad07dc26cb93125a94ec7a5526e27ef6e8317ba928849da890b3b2", null ]
    ] ],
    [ "_i2c_direction", "a00018.html#ga1625497320644ba123718bafdd2c1f39", [
      [ "kI2C_Write", "a00018.html#gga1625497320644ba123718bafdd2c1f39a93b476b469c2a4bfed5916b458ae9bb0", null ],
      [ "kI2C_Read", "a00018.html#gga1625497320644ba123718bafdd2c1f39a3a7bb24dc8d1c1be8925603eeafe9b30", null ]
    ] ],
    [ "_i2c_master_transfer_flags", "a00018.html#ga87ea07668194cfb46c7c368d2cb42433", [
      [ "kI2C_TransferDefaultFlag", "a00018.html#gga87ea07668194cfb46c7c368d2cb42433ae80f7b768b1621e42ac965d3d23de5e2", null ],
      [ "kI2C_TransferNoStartFlag", "a00018.html#gga87ea07668194cfb46c7c368d2cb42433a5cb44bf860c0482c0ca0165cf0d31d8a", null ],
      [ "kI2C_TransferRepeatedStartFlag", "a00018.html#gga87ea07668194cfb46c7c368d2cb42433aadf112471ef12f194985a093cd9b9721", null ],
      [ "kI2C_TransferNoStopFlag", "a00018.html#gga87ea07668194cfb46c7c368d2cb42433afb8aeea71b5b7475e3d3df86220db566", null ]
    ] ],
    [ "_i2c_slave_transfer_event", "a00018.html#ga87e42e170b60f17f657ef3c06a918133", [
      [ "kI2C_SlaveAddressMatchEvent", "a00018.html#gga87e42e170b60f17f657ef3c06a918133acb1ae174dd6798a6fd79800a9e39a3c6", null ],
      [ "kI2C_SlaveTransmitEvent", "a00018.html#gga87e42e170b60f17f657ef3c06a918133a2f85039a57379838909876a1d509b7aa", null ],
      [ "kI2C_SlaveReceiveEvent", "a00018.html#gga87e42e170b60f17f657ef3c06a918133aac8593e808a8137d1b5d3a51640779de", null ],
      [ "kI2C_SlaveTransmitAckEvent", "a00018.html#gga87e42e170b60f17f657ef3c06a918133a43c045da27fa60e7a0540c743eca4e79", null ],
      [ "kI2C_SlaveCompletionEvent", "a00018.html#gga87e42e170b60f17f657ef3c06a918133a38cca3cd668e73f51b8e574835d419df", null ],
      [ "kI2C_SlaveAllEvents", "a00018.html#gga87e42e170b60f17f657ef3c06a918133a94b030ebdac378a84961893ae567bfbc", null ]
    ] ],
    [ "I2C_MasterInit", "a00018.html#ga29f967b3ae8487a36ba2a58deb01ccae", null ],
    [ "I2C_MasterDeinit", "a00018.html#gadcf7122f0a38d4d9da0f052fcb167957", null ],
    [ "I2C_MasterGetDefaultConfig", "a00018.html#gad69f2d63ea756dda60749ff6b09f587d", null ],
    [ "I2C_SlaveInit", "a00018.html#gae6e155a5aadb43d527418e2965e39123", null ],
    [ "I2C_SlaveDeinit", "a00018.html#gadb50014db29dd75ea2001fb7bc837e77", null ],
    [ "I2C_SlaveGetDefaultConfig", "a00018.html#ga7115f80e28b62bbbd3be1a2a918529ba", null ],
    [ "I2C_Enable", "a00018.html#gaaaaab1e83cb8c6117046bdb5bcbf9ac6", null ],
    [ "I2C_MasterGetStatusFlags", "a00018.html#ga8219cf80c3be6c15fc5035326b7f62dc", null ],
    [ "I2C_MasterClearStatusFlags", "a00018.html#ga437271ffb955b77df0a5dee9ea80cc63", null ],
    [ "I2C_SlaveGetStatusFlags", "a00018.html#gac2794e138d94d9b6a761c074ad0899cd", null ],
    [ "I2C_SlaveClearStatusFlags", "a00018.html#ga545c1a43d8d49c4675de493d45a4063a", null ],
    [ "I2C_EnableInterrupts", "a00018.html#ga577e094cc4d39b88ec5bbe49bc199c77", null ],
    [ "I2C_DisableInterrupts", "a00018.html#ga9839c1fd49a0f62f42b0adfa74f62853", null ],
    [ "I2C_MasterSetBaudRate", "a00018.html#gafeab1d5249a8b39c8d9e1a54a85c23f0", null ],
    [ "I2C_MasterStart", "a00018.html#ga7664234966e4162e952b6d57efcaa8a6", null ],
    [ "I2C_MasterStop", "a00018.html#gaf46a8cc094fc18c6cadea8de71448723", null ],
    [ "I2C_MasterRepeatedStart", "a00018.html#ga42ff265d25e713326c7d152adf350147", null ],
    [ "I2C_MasterWriteBlocking", "a00018.html#gac4e1a954243aa852cb4d358e90091efd", null ],
    [ "I2C_MasterReadBlocking", "a00018.html#gaf77526f32a16109abf265dbb022a26ba", null ],
    [ "I2C_SlaveWriteBlocking", "a00018.html#ga280404c6b1ede542f2c1c20bd382869c", null ],
    [ "I2C_SlaveReadBlocking", "a00018.html#ga89baaf8bc82b19c837032665e89a1707", null ],
    [ "I2C_MasterTransferBlocking", "a00018.html#ga35cae3a5b4aa50ce8db28e3eb703a027", null ],
    [ "I2C_MasterTransferCreateHandle", "a00018.html#ga31e3de02b57801c6896e6045c4a31268", null ],
    [ "I2C_MasterTransferNonBlocking", "a00018.html#gac7f76a04b6f6873c52ad176d58901fe9", null ],
    [ "I2C_MasterTransferGetCount", "a00018.html#ga7d720842e68161d2d52d56d119f20665", null ],
    [ "I2C_MasterTransferAbort", "a00018.html#gabb386e53b2bc64e29b2915bdfac36800", null ],
    [ "I2C_MasterTransferHandleIRQ", "a00018.html#gad091cd1857d2bd8ce64583739b3a35d5", null ],
    [ "I2C_SlaveTransferCreateHandle", "a00018.html#gac9b90f575d92ff8ad3cc350a5c8ad1b9", null ],
    [ "I2C_SlaveTransferNonBlocking", "a00018.html#gaa387d81ea08a9d4b39cfeb3dfec505f7", null ],
    [ "I2C_SlaveTransferAbort", "a00018.html#ga5ae9f5e6e854d14d33ba3029128bd6f0", null ],
    [ "I2C_SlaveTransferGetCount", "a00018.html#gabf38a498bd3527ea0b7cc947ae71e17e", null ],
    [ "I2C_SlaveTransferHandleIRQ", "a00018.html#ga097c0b20503381de44cccba311dcf236", null ]
];