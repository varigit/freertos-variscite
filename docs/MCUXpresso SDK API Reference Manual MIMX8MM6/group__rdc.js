var group__rdc =
[
    [ "rdc_hardware_config_t", "group__rdc.html#structrdc__hardware__config__t", [
      [ "domainNumber", "group__rdc.html#a739ea4a24186ac54d3d97ec1bcda5631", null ],
      [ "masterNumber", "group__rdc.html#a81842ff8d313ca38916e3226efdd3bde", null ],
      [ "periphNumber", "group__rdc.html#ac02b7c759b76aac047c8dfd86fd93a59", null ],
      [ "memNumber", "group__rdc.html#afb605761a847c152ab23a5790b44dee9", null ]
    ] ],
    [ "rdc_domain_assignment_t", "group__rdc.html#structrdc__domain__assignment__t", [
      [ "domainId", "group__rdc.html#a6e918db4f50ef773621e9f90a8dd0aa1", null ],
      [ "__pad0__", "group__rdc.html#a8d76c2ce9f3ab1bd748c21c409e14b08", null ],
      [ "lock", "group__rdc.html#add7373049bb837ae009d9d6f54d6c042", null ]
    ] ],
    [ "rdc_periph_access_config_t", "group__rdc.html#structrdc__periph__access__config__t", [
      [ "periph", "group__rdc.html#a7472e8b72f7646864b1244f491559d48", null ],
      [ "lock", "group__rdc.html#a9a39e94946c18bba0593a7d063e39ead", null ],
      [ "enableSema", "group__rdc.html#ae3359bd3ece8b0075310586208b0f18e", null ],
      [ "policy", "group__rdc.html#a8e401a7aabd8cd79807858b4eb89cd70", null ]
    ] ],
    [ "rdc_mem_access_config_t", "group__rdc.html#structrdc__mem__access__config__t", [
      [ "mem", "group__rdc.html#ad4e1e98d9c5b9bf9fbbadf2f90c46dfc", null ],
      [ "lock", "group__rdc.html#af7b74c739bdc6cf8d13c3a9679ea934b", null ],
      [ "baseAddress", "group__rdc.html#a8e8b96bf0942a146d5f15927a1d7871b", null ],
      [ "endAddress", "group__rdc.html#a65762fb507c7d9bd67043a6b7d85e351", null ],
      [ "policy", "group__rdc.html#aa8fa0fa776b881c0b884461f4f96f827", null ]
    ] ],
    [ "rdc_mem_status_t", "group__rdc.html#structrdc__mem__status__t", [
      [ "hasViolation", "group__rdc.html#a64e77210e7d78eab8f492aec96ab1812", null ],
      [ "domainID", "group__rdc.html#a9cdb8148ebf80d343b95716e03964127", null ],
      [ "address", "group__rdc.html#a702289fbf20c6b8a9450192654f230d7", null ]
    ] ],
    [ "FSL_RDC_DRIVER_VERSION", "group__rdc.html#gab67e391faac732c355db7375a550f6c8", null ],
    [ "_rdc_interrupts", "group__rdc.html#ga43f5d8d1ed667a8c73ab204a74925892", [
      [ "kRDC_RestoreCompleteInterrupt", "group__rdc.html#gga43f5d8d1ed667a8c73ab204a74925892a5088cfe20c6ef9e259657e6f6ecc7387", null ]
    ] ],
    [ "_rdc_flags", "group__rdc.html#ga30afa024532b0207bdeeee3344af9ebd", [
      [ "kRDC_PowerDownDomainOn", "group__rdc.html#gga30afa024532b0207bdeeee3344af9ebda5e58c4dabb46b1f4a47b7ae8cd0f61e3", null ]
    ] ],
    [ "_rdc_access_policy", "group__rdc.html#gad1f726221167c740e1500317ea80beb2", [
      [ "kRDC_NoAccess", "group__rdc.html#ggad1f726221167c740e1500317ea80beb2a3abbfd7f6818ca32df8d30300aba7f1a", null ],
      [ "kRDC_WriteOnly", "group__rdc.html#ggad1f726221167c740e1500317ea80beb2af704f2f758ba0d96ddea53e686325efe", null ],
      [ "kRDC_ReadOnly", "group__rdc.html#ggad1f726221167c740e1500317ea80beb2acad6ad0fa9f2d31d48ec9e7b2898cdb6", null ],
      [ "kRDC_ReadWrite", "group__rdc.html#ggad1f726221167c740e1500317ea80beb2a45a95e9ad49ab28807dc57a67e770ebd", null ]
    ] ],
    [ "RDC_Init", "group__rdc.html#ga5e55854cf5534e9ea2844c6447630d29", null ],
    [ "RDC_Deinit", "group__rdc.html#gad67bd7441a6770382a42871a73cab1e9", null ],
    [ "RDC_GetHardwareConfig", "group__rdc.html#ga00ad216ad6ee434f4684c804c845974d", null ],
    [ "RDC_EnableInterrupts", "group__rdc.html#gac4fd27fb3b91add96b402a316f5257d1", null ],
    [ "RDC_DisableInterrupts", "group__rdc.html#ga8431d5742c72d100e9d5ea8acb828164", null ],
    [ "RDC_GetInterruptStatus", "group__rdc.html#ga2daf610d7330112bdefdaf737d88057d", null ],
    [ "RDC_ClearInterruptStatus", "group__rdc.html#ga46324815d4934688c553fa427068aebf", null ],
    [ "RDC_GetStatus", "group__rdc.html#ga607d3cb8467e3dad81c01b99b262b025", null ],
    [ "RDC_ClearStatus", "group__rdc.html#gaa78b6ce74c4abe2fb4f8696dba4bab58", null ],
    [ "RDC_SetMasterDomainAssignment", "group__rdc.html#ga0743d1da240ea2defb5e8d88bb7fb4e7", null ],
    [ "RDC_GetDefaultMasterDomainAssignment", "group__rdc.html#ga75b61e0de26784fb5ed9c487a46b3fb4", null ],
    [ "RDC_LockMasterDomainAssignment", "group__rdc.html#ga7bac728610bbf0d1fc8ef54684453a67", null ],
    [ "RDC_SetPeriphAccessConfig", "group__rdc.html#gad7761fcab34b52ebf80024199d0390bc", null ],
    [ "RDC_GetDefaultPeriphAccessConfig", "group__rdc.html#ga3960b46c770474ae90a3efe6bbf0848f", null ],
    [ "RDC_LockPeriphAccessConfig", "group__rdc.html#gad726f804c6f29e6f08014749883816f8", null ],
    [ "RDC_SetMemAccessConfig", "group__rdc.html#ga8a2282cbee8cbb2eeb38c98325351d64", null ],
    [ "RDC_GetDefaultMemAccessConfig", "group__rdc.html#gad38513d641ad47ccbb003c47bb3c9727", null ],
    [ "RDC_LockMemAccessConfig", "group__rdc.html#ga8e9f9b9bb90724ed625ee5b5cd2a8d41", null ],
    [ "RDC_SetMemAccessValid", "group__rdc.html#ga50e5d41f56901ea8924e6bb1f6e92fbd", null ],
    [ "RDC_GetMemViolationStatus", "group__rdc.html#ga76711caa424d57a32847831f60cac1aa", null ],
    [ "RDC_ClearMemViolationFlag", "group__rdc.html#gaf594d7e71d47df3bdc89a62e45b944a1", null ],
    [ "RDC_GetCurrentMasterDomainId", "group__rdc.html#gacf0861a99d3a45d022fef5dd35f158c5", null ]
];