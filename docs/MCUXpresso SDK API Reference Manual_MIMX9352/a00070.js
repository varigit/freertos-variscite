var a00070 =
[
    [ "trdc_hardware_config_t", "a00070.html#a00488", [
      [ "masterNumber", "a00070.html#a2ff0974a976440b3a2bc5ab57102c8d5", null ],
      [ "domainNumber", "a00070.html#ab73b239124ec56087efff9207139ee34", null ],
      [ "mbcNumber", "a00070.html#a954bbb0f3bb3d63065d4a5b12fd812a8", null ],
      [ "mrcNumber", "a00070.html#a206e75ce5feb6c95d93c3505cfb2eb2e", null ]
    ] ],
    [ "trdc_slave_memory_hardware_config_t", "a00070.html#a00499", [
      [ "blockNum", "a00070.html#a74e4c4f5c1c28141beebc9e3f2f882e7", null ],
      [ "blockSize", "a00070.html#a361d82773033dadb1a200d2640abe738", null ]
    ] ],
    [ "trdc_processor_domain_assignment_t", "a00070.html#a00498", [
      [ "domainId", "a00070.html#a2ab32fadef7b4d85cc4e9d8aaaca809c", null ],
      [ "domainIdSelect", "a00070.html#a17ff536f2291240431193f647da4a3bb", null ],
      [ "pidDomainHitConfig", "a00070.html#ab24a4341f16eb37683537cf87abc826a", null ],
      [ "pidMask", "a00070.html#a0a5ab502d388c112ae726884a2c2d694", null ],
      [ "secureAttr", "a00070.html#a1ce64f1c53fe978f4cd618390b5ce99c", null ],
      [ "pid", "a00070.html#a5ff882a5b1c2c89d1b1d50135bde7097", null ],
      [ "__pad0__", "a00070.html#a234329e14a28762d49846c72a9751faa", null ],
      [ "lock", "a00070.html#a3fa0e17838b97d0d9bd8c8a220538a40", null ],
      [ "__pad1__", "a00070.html#a00658c1a597839c60cb863231054cf29", null ]
    ] ],
    [ "trdc_non_processor_domain_assignment_t", "a00070.html#a00496", [
      [ "domainId", "a00070.html#a34b9615a38f1816e7e9552e5eac8df97", null ],
      [ "privilegeAttr", "a00070.html#ae1f70ea5656b4ad7b3caa579e5a3085f", null ],
      [ "secureAttr", "a00070.html#af2f3fdaefeba5ff9358b3498a96d9f0d", null ],
      [ "bypassDomainId", "a00070.html#a7fd213f7f18374a09e218b07da21a1ed", null ],
      [ "__pad0__", "a00070.html#a79733292573ccccea83df822320c4ca6", null ],
      [ "lock", "a00070.html#a25ecb0be4b6b6f00511bdb1440b3db61", null ],
      [ "__pad1__", "a00070.html#ae03e2bd93156cf602ec894ec04e9dcf3", null ]
    ] ],
    [ "trdc_pid_config_t", "a00070.html#a00497", [
      [ "pid", "a00070.html#a80bf9d5ed5222df84ce6e2d520a52ae1", null ],
      [ "__pad0__", "a00070.html#ac93d67b9e506d2aa966bed91d0047f65", null ],
      [ "lock", "a00070.html#aa8055e31dcd9007f1fc60b420b09cf2d", null ],
      [ "__pad1__", "a00070.html#ac8a930e6e0022d479b80b0f4efcc23a4", null ]
    ] ],
    [ "trdc_idau_config_t", "a00070.html#a00489", [
      [ "__pad0__", "a00070.html#aee61560d2c326b753010d438253957b6", null ],
      [ "lockSecureVTOR", "a00070.html#ac5ad7f1d58c7ff9532e0ffc42e4aab71", null ],
      [ "lockNonsecureVTOR", "a00070.html#a186baeccfa8c4021247d01d80246a653", null ],
      [ "lockSecureMPU", "a00070.html#a701e2da131743691fcf9011b078066f1", null ],
      [ "lockNonsecureMPU", "a00070.html#a17c497d48dd5cb15407076f0b07fbe90", null ],
      [ "lockSAU", "a00070.html#aed171a15162eb5555f3578a4cf40b782", null ],
      [ "__pad1__", "a00070.html#aced37d0c6b1f5e02f993e724a7dd798c", null ]
    ] ],
    [ "trdc_flw_config_t", "a00070.html#a00485", [
      [ "blockCount", "a00070.html#a22f02da191b1c3f9d306b4c0ef7b0c5c", null ],
      [ "arrayBaseAddr", "a00070.html#a202d324f94d0ad180fcc4df1c67989ef", null ],
      [ "lock", "a00070.html#afc2a63cd637426e9a6b46ebb0c00ce41", null ],
      [ "enable", "a00070.html#acb1c6d9042fcffa6bb01707034f26637", null ]
    ] ],
    [ "trdc_domain_error_t", "a00070.html#a00482", [
      [ "controller", "a00070.html#a0ab7fe2e988b26cc413ced30a208fd7d", null ],
      [ "address", "a00070.html#a4f68815bf09bfc653d6e6df45e6bda52", null ],
      [ "errorState", "a00070.html#a39b5837384304fa944ae262799108830", null ],
      [ "errorAttr", "a00070.html#a1a233f910a17497c773cdc4ee3088572", null ],
      [ "errorType", "a00070.html#a498c30a2c7b0d6b9b6b3cceba794afb5", null ],
      [ "errorPort", "a00070.html#a156ef8d42d4d9a644ad4339bce2db6dd", null ],
      [ "domainId", "a00070.html#ab43ea686294933509ce1f1e7100e8665", null ],
      [ "slaveMemoryIdx", "a00070.html#a32f367879e51efe11a2fdefca3f0f93b", null ]
    ] ],
    [ "trdc_memory_access_control_config_t", "a00070.html#a00493", [
      [ "nonsecureUsrX", "a00070.html#a9c71c515495b9dff79231c1b598f249a", null ],
      [ "nonsecureUsrW", "a00070.html#a356c2d64c1f53870f718a56aecad756c", null ],
      [ "nonsecureUsrR", "a00070.html#ae85c0b219826d30f49ed4b8759e7c6f7", null ],
      [ "__pad0__", "a00070.html#addf3fa53928c0fb08308f756ca07cae7", null ],
      [ "nonsecurePrivX", "a00070.html#ac724452cb605348ade0c5b45523b38a8", null ],
      [ "nonsecurePrivW", "a00070.html#afa85f3afb384b91ba782b86d8cd44bd0", null ],
      [ "nonsecurePrivR", "a00070.html#aaf49281105db00456c3519aef4d06941", null ],
      [ "__pad1__", "a00070.html#ac0cae8f6a40b97365832fa3a888605bb", null ],
      [ "secureUsrX", "a00070.html#aa97aeaa51102c7663ed940341cc77298", null ],
      [ "secureUsrW", "a00070.html#a03162e0228a4f0b9d08b2284dd74c923", null ],
      [ "secureUsrR", "a00070.html#a6d0a2509dd425eed1bf259b434f2f915", null ],
      [ "__pad2__", "a00070.html#a5aa2443df20dfb1c361454b4c0b8d333", null ],
      [ "securePrivX", "a00070.html#a68f1cde7b60e3d0f036daf3a13d53458", null ],
      [ "securePrivW", "a00070.html#a7a6d913400a65c22caabf513eff0682f", null ],
      [ "securePrivR", "a00070.html#ac389d6713ee1370711269bbc33c4aba1", null ],
      [ "__pad3__", "a00070.html#a033456e3e9c99a2f5fa36496d76778f4", null ],
      [ "lock", "a00070.html#a56741b709ff13b7f8540ebd898773503", null ]
    ] ],
    [ "trdc_mrc_region_descriptor_config_t", "a00070.html#a00494", [
      [ "memoryAccessControlSelect", "a00070.html#a5ccfaf777183fc124663995be7bbab9f", null ],
      [ "startAddr", "a00070.html#a964f568e99b5331f2fd8106e924be89b", null ],
      [ "valid", "a00070.html#a37d31e64a67c1c097fe3f8032e38d5d7", null ],
      [ "nseEnable", "a00070.html#a916d262eec0aaebf1eb4d65b3957fa24", null ],
      [ "endAddr", "a00070.html#a161f06429471eb8106899345ceef70f3", null ],
      [ "mrcIdx", "a00070.html#a69d49aa6fef196a936317109fd397aa4", null ],
      [ "domainIdx", "a00070.html#a850c06e3b1ecdcb942c53f00b2b3a6ea", null ],
      [ "regionIdx", "a00070.html#a0c145bb54eb974790c0c8a735c8be121", null ]
    ] ],
    [ "trdc_mbc_nse_update_config_t", "a00070.html#a00491", [
      [ "autoIncrement", "a00070.html#a8020f2f3c8a67b87b44a6d87331f5e4f", null ],
      [ "__pad0__", "a00070.html#a5d0b5b06c35141bdb64a2836beb458f1", null ],
      [ "wordIdx", "a00070.html#a7295cd817a40dd108e672c998e54eb3d", null ],
      [ "__pad1__", "a00070.html#a7925d23b829bf82b57bd255034ce670c", null ],
      [ "memorySelect", "a00070.html#abe5594c8e5c0a1ed557b5ee210b525dc", null ],
      [ "__pad2__", "a00070.html#adf0c2c742a9c208d45dbd86441ad667c", null ],
      [ "domianSelect", "a00070.html#ad01fbda71927b5cdd1344f4d09826669", null ]
    ] ],
    [ "trdc_mbc_memory_block_config_t", "a00070.html#a00490", [
      [ "memoryAccessControlSelect", "a00070.html#a301f06b675c644f256a78c4745e9534e", null ],
      [ "nseEnable", "a00070.html#ac0e2df4e5be4e039759ec602a047eeae", null ],
      [ "mbcIdx", "a00070.html#a127307415c6fa781f19dfeee2d54ac7c", null ],
      [ "domainIdx", "a00070.html#a79946f116b0eb21a04c129334af2bc14", null ],
      [ "slaveMemoryIdx", "a00070.html#a215d4aae3ccc0b1b274d88e5bc8dab21", null ],
      [ "memoryBlockIdx", "a00070.html#a883fe6deec2d47222b1a2fd7df821cef", null ]
    ] ],
    [ "trdc_did_sel_t", "a00070.html#ga41ff67b5a240afa87edad8568e1a0e30", [
      [ "kTRDC_DidMda", "a00070.html#gga41ff67b5a240afa87edad8568e1a0e30a56b0306aa2e3e2f84bf0d7be8b8ccfea", null ],
      [ "kTRDC_DidInput", "a00070.html#gga41ff67b5a240afa87edad8568e1a0e30a24b131f13f1dfa5bd19d36ca03dbe0c9", null ],
      [ "kTRDC_DidMdaAndInput", "a00070.html#gga41ff67b5a240afa87edad8568e1a0e30a57a7f3b128db35447f1bab304b6523ac", null ],
      [ "kTRDC_DidReserved", "a00070.html#gga41ff67b5a240afa87edad8568e1a0e30afc87236c53ee44277f751fce6a60dd92", null ]
    ] ],
    [ "trdc_secure_attr_t", "a00070.html#ga57c774d0fbbcd09b69d8ccd7c5e71801", [
      [ "kTRDC_ForceSecure", "a00070.html#gga57c774d0fbbcd09b69d8ccd7c5e71801a40913866f46041f795aa8e60dd83e638", null ],
      [ "kTRDC_ForceNonSecure", "a00070.html#gga57c774d0fbbcd09b69d8ccd7c5e71801ab6073ddc0869c8f8d0a7eae7ee39791e", null ],
      [ "kTRDC_MasterSecure", "a00070.html#gga57c774d0fbbcd09b69d8ccd7c5e71801a9f5d47282cb9fc708cfd5026fe1a62a2", null ],
      [ "kTRDC_MasterSecure1", "a00070.html#gga57c774d0fbbcd09b69d8ccd7c5e71801a239b39807214452976e8b4ae719ed27b", null ]
    ] ],
    [ "trdc_pid_domain_hit_config_t", "a00070.html#gaf923ce0c6a804cea325f2ddc96b92a3e", [
      [ "kTRDC_pidDomainHitNone0", "a00070.html#ggaf923ce0c6a804cea325f2ddc96b92a3ea7d19c729dae7ef3dbe43649c54a782c5", null ],
      [ "kTRDC_pidDomainHitNone1", "a00070.html#ggaf923ce0c6a804cea325f2ddc96b92a3eac9da678a533a006ecc5c2e576dfd0f96", null ],
      [ "kTRDC_pidDomainHitInclusive", "a00070.html#ggaf923ce0c6a804cea325f2ddc96b92a3ea41d443a7cbe985350de1caad4f3c81e8", null ],
      [ "kTRDC_pidDomainHitExclusive", "a00070.html#ggaf923ce0c6a804cea325f2ddc96b92a3ea60e409e8309a8f1cb2b33f0a98f2cfa8", null ]
    ] ],
    [ "trdc_privilege_attr_t", "a00070.html#gaa2b6818deec35aadafcff11a60f8247a", [
      [ "kTRDC_ForceUser", "a00070.html#ggaa2b6818deec35aadafcff11a60f8247aaf6426ef17044c180e0354bf2fb8bd003", null ],
      [ "kTRDC_ForcePrivilege", "a00070.html#ggaa2b6818deec35aadafcff11a60f8247aaf6a3da873fc5969612d54c485e4fd785", null ],
      [ "kTRDC_MasterPrivilege", "a00070.html#ggaa2b6818deec35aadafcff11a60f8247aa5f4557d82d55589739dbd09f964556c9", null ],
      [ "kTRDC_MasterPrivilege1", "a00070.html#ggaa2b6818deec35aadafcff11a60f8247aa53bc0ca765fee678ebdba466a4de4941", null ]
    ] ],
    [ "trdc_pid_lock_t", "a00070.html#gafa4118e3f2a6b136b4be4cd4e6bea127", [
      [ "kTRDC_PidUnlocked0", "a00070.html#ggafa4118e3f2a6b136b4be4cd4e6bea127ac1120c7b516b24b79a63e978d7948f95", null ],
      [ "kTRDC_PidUnlocked1", "a00070.html#ggafa4118e3f2a6b136b4be4cd4e6bea127a5b3a1ab82410060329574be79521369e", null ],
      [ "kTRDC_PidUnlocked2", "a00070.html#ggafa4118e3f2a6b136b4be4cd4e6bea127a5aaf354fa76aa28e8d66d0e118c0c6b9", null ],
      [ "kTRDC_PidLocked", "a00070.html#ggafa4118e3f2a6b136b4be4cd4e6bea127ae606dced973b72804d071d880037b0bb", null ]
    ] ],
    [ "trdc_controller_t", "a00070.html#ga9c2405b76789b6edc1ba6f6f80120dc6", [
      [ "kTRDC_MemBlockController0", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6ab4595e3c87d3262a1f44ae4ed46c3e4c", null ],
      [ "kTRDC_MemBlockController1", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6a9f6dd91f44857fa0158039f66f3dc205", null ],
      [ "kTRDC_MemBlockController2", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6ad0676b08103d32b6ba22f907477b031d", null ],
      [ "kTRDC_MemBlockController3", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6a41c8738396efeb3743668194b9d21316", null ],
      [ "kTRDC_MemRegionChecker0", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6ab79cff14ad872ca8782e52e7fcc660a3", null ],
      [ "kTRDC_MemRegionChecker1", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6a4ffbeb26198f06dcf474590ca9468587", null ],
      [ "kTRDC_MemRegionChecker2", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6af229587947c408ecc197901c69cbc992", null ],
      [ "kTRDC_MemRegionChecker3", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6aa47d36bcd8bdb1b34408ed90f1d21424", null ],
      [ "kTRDC_MemRegionChecker4", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6aeaf0b2cfd2f518ffe6db99965a1841a1", null ],
      [ "kTRDC_MemRegionChecker5", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6a4f4a3bf3cc28610b99219e2d5d2a38e5", null ],
      [ "kTRDC_MemRegionChecker6", "a00070.html#gga9c2405b76789b6edc1ba6f6f80120dc6a24cf57372b5c0ad1cce9711cd20c314e", null ]
    ] ],
    [ "trdc_error_state_t", "a00070.html#ga48fe078df3d244f5cecb7b834271ed39", [
      [ "kTRDC_ErrorStateNone", "a00070.html#gga48fe078df3d244f5cecb7b834271ed39a1f461ce5501a103bc97ffc1b3a875443", null ],
      [ "kTRDC_ErrorStateNone1", "a00070.html#gga48fe078df3d244f5cecb7b834271ed39abbce6acaa192e6c79eecc6fa9630927c", null ],
      [ "kTRDC_ErrorStateSingle", "a00070.html#gga48fe078df3d244f5cecb7b834271ed39a15145be0da7acc195d1f8061b0023c5c", null ],
      [ "kTRDC_ErrorStateMulti", "a00070.html#gga48fe078df3d244f5cecb7b834271ed39aabbb9a22805fbc928795dd03c3df5469", null ]
    ] ],
    [ "trdc_error_attr_t", "a00070.html#ga098064e0a44b4a9c9bfb0e12bf84c068", [
      [ "kTRDC_ErrorSecureUserInst", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068a90f560f0847d3c2b839ea141321ee5f3", null ],
      [ "kTRDC_ErrorSecureUserData", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068a796de0f7476581276949b091d6683fb5", null ],
      [ "kTRDC_ErrorSecurePrivilegeInst", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068ad49153b923cfc5e8eee74f9cb9058954", null ],
      [ "kTRDC_ErrorSecurePrivilegeData", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068ab3c8fcd61763412d8cea715407ef3e39", null ],
      [ "kTRDC_ErrorNonSecureUserInst", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068af42edfeb07f91e0c7c3220b9858bff2d", null ],
      [ "kTRDC_ErrorNonSecureUserData", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068a1e1153df85cf823eef6e69eb1c90230b", null ],
      [ "kTRDC_ErrorNonSecurePrivilegeInst", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068a9d644e2c333c4b8b86e2e365d9dc621e", null ],
      [ "kTRDC_ErrorNonSecurePrivilegeData", "a00070.html#gga098064e0a44b4a9c9bfb0e12bf84c068a7c589f7ebee21a0e40532cf9dd70dc34", null ]
    ] ],
    [ "trdc_error_type_t", "a00070.html#ga976257378236315429f87ad411d931d8", [
      [ "kTRDC_ErrorTypeRead", "a00070.html#gga976257378236315429f87ad411d931d8a00c58a8f5153ff4f70b0510e3f446b39", null ],
      [ "kTRDC_ErrorTypeWrite", "a00070.html#gga976257378236315429f87ad411d931d8a1bc676c1dba2d9e314633b6f9a74d0da", null ]
    ] ],
    [ "_trdc_region_descriptor", "a00070.html#ga3d6507285a84f244537dcddedddfefee", [
      [ "kTRDC_RegionDescriptor0", "a00070.html#gga3d6507285a84f244537dcddedddfefeea48bbd9a9cc9f6d6524ab9227277a47c9", null ],
      [ "kTRDC_RegionDescriptor1", "a00070.html#gga3d6507285a84f244537dcddedddfefeeac09e9a220b72dd0b6b87dfad5fd68b07", null ],
      [ "kTRDC_RegionDescriptor2", "a00070.html#gga3d6507285a84f244537dcddedddfefeeabca95bdf03b9f9a91257d829a19565e0", null ],
      [ "kTRDC_RegionDescriptor3", "a00070.html#gga3d6507285a84f244537dcddedddfefeea7ad92f2ad587798a4938d13bfe49b084", null ],
      [ "kTRDC_RegionDescriptor4", "a00070.html#gga3d6507285a84f244537dcddedddfefeea595da1f5b467719b9ee5c25371074718", null ],
      [ "kTRDC_RegionDescriptor5", "a00070.html#gga3d6507285a84f244537dcddedddfefeea00e00f3375919bba92641facc80c2128", null ],
      [ "kTRDC_RegionDescriptor6", "a00070.html#gga3d6507285a84f244537dcddedddfefeeab7945853daad2e27852de197ce020cdf", null ],
      [ "kTRDC_RegionDescriptor7", "a00070.html#gga3d6507285a84f244537dcddedddfefeea5e1433559f8f94a88def2737703b008b", null ],
      [ "kTRDC_RegionDescriptor8", "a00070.html#gga3d6507285a84f244537dcddedddfefeea6f6e978b57a78f920243c10c7b517315", null ],
      [ "kTRDC_RegionDescriptor9", "a00070.html#gga3d6507285a84f244537dcddedddfefeeae682c83b15ae392739e73112b25e9aec", null ],
      [ "kTRDC_RegionDescriptor10", "a00070.html#gga3d6507285a84f244537dcddedddfefeea1dfb729447f059e4365817ba44194d8e", null ],
      [ "kTRDC_RegionDescriptor11", "a00070.html#gga3d6507285a84f244537dcddedddfefeeaa2ae46816624df35810c60a2cb7905ca", null ],
      [ "kTRDC_RegionDescriptor12", "a00070.html#gga3d6507285a84f244537dcddedddfefeea675207685b8bce5c92b9c6010ae1c75a", null ],
      [ "kTRDC_RegionDescriptor13", "a00070.html#gga3d6507285a84f244537dcddedddfefeead7deb0b8d8e65fb2ee915bcb9b110331", null ],
      [ "kTRDC_RegionDescriptor14", "a00070.html#gga3d6507285a84f244537dcddedddfefeeae77e14c3b2475dde96518dc650517b87", null ],
      [ "kTRDC_RegionDescriptor15", "a00070.html#gga3d6507285a84f244537dcddedddfefeeac0d252b40ac22716c093834952f84cda", null ]
    ] ],
    [ "_trdc_MRC_domain", "a00070.html#ga66c1733993b84b2731c046cc8a353961", [
      [ "kTRDC_MrcDomain0", "a00070.html#gga66c1733993b84b2731c046cc8a353961a15e820fc9f19d53a673b35bc0139156e", null ],
      [ "kTRDC_MrcDomain1", "a00070.html#gga66c1733993b84b2731c046cc8a353961a416eac0b7ec9726a2a6e5da8bf430414", null ],
      [ "kTRDC_MrcDomain2", "a00070.html#gga66c1733993b84b2731c046cc8a353961a6bcef4ed2e5ac3fb1235df3d2dc43ed9", null ],
      [ "kTRDC_MrcDomain3", "a00070.html#gga66c1733993b84b2731c046cc8a353961a9e29836e98258428a04e8b07a5f62a5c", null ],
      [ "kTRDC_MrcDomain4", "a00070.html#gga66c1733993b84b2731c046cc8a353961a5764e09106c35ba3639e9b7dce5b73a1", null ],
      [ "kTRDC_MrcDomain5", "a00070.html#gga66c1733993b84b2731c046cc8a353961ad97cbd4582ab2b5ae48bd4d17bc536f7", null ],
      [ "kTRDC_MrcDomain6", "a00070.html#gga66c1733993b84b2731c046cc8a353961ad05424dc4fce8fefb1d2aaa8976286a0", null ],
      [ "kTRDC_MrcDomain7", "a00070.html#gga66c1733993b84b2731c046cc8a353961a193cb8e1401581601f52b78f24a7cb89", null ],
      [ "kTRDC_MrcDomain8", "a00070.html#gga66c1733993b84b2731c046cc8a353961ab5159ddb414d56a6b1f931851b737f6a", null ],
      [ "kTRDC_MrcDomain9", "a00070.html#gga66c1733993b84b2731c046cc8a353961a6ccaba3c462eda737dff1cee9e27e411", null ],
      [ "kTRDC_MrcDomain10", "a00070.html#gga66c1733993b84b2731c046cc8a353961ac02fea2f845ac16aaee2f05202f4ac46", null ],
      [ "kTRDC_MrcDomain11", "a00070.html#gga66c1733993b84b2731c046cc8a353961abb02d9e76e7b9742a426c39b5ddb4e96", null ],
      [ "kTRDC_MrcDomain12", "a00070.html#gga66c1733993b84b2731c046cc8a353961a561e53da8981edd0728d2101ab3cdcf5", null ],
      [ "kTRDC_MrcDomain13", "a00070.html#gga66c1733993b84b2731c046cc8a353961a5c356418366083b7f6149e15dcd6bb44", null ],
      [ "kTRDC_MrcDomain14", "a00070.html#gga66c1733993b84b2731c046cc8a353961a2a481723d97361174a3956135ebe116d", null ],
      [ "kTRDC_MrcDomain15", "a00070.html#gga66c1733993b84b2731c046cc8a353961a23009a5c3106b78c86150a30db055ac9", null ]
    ] ],
    [ "_trdc_MBC_domain", "a00070.html#ga5b9b09766510fa74fce56983dff9de4f", [
      [ "kTRDC_MbcDomain0", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fad9f17c97423f833c6f1e4e5382242258", null ],
      [ "kTRDC_MbcDomain1", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa720d40079715723bc2bdde2d103bc321", null ],
      [ "kTRDC_MbcDomain2", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa304bbec8ad78264236fd3ba2f711bd68", null ],
      [ "kTRDC_MbcDomain3", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa235acc9b7c902fe999c69405196a4883", null ],
      [ "kTRDC_MbcDomain4", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fab8e37909cc065fead7117150241247eb", null ],
      [ "kTRDC_MbcDomain5", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa16f65ea87bd6df86d8b9822511af2f24", null ],
      [ "kTRDC_MbcDomain6", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa798d037c11dc28d821ee2f036bdf2013", null ],
      [ "kTRDC_MbcDomain7", "a00070.html#gga5b9b09766510fa74fce56983dff9de4fa6aca37171a1ffb29536fed6dd5097815", null ]
    ] ],
    [ "_trdc_MBC_memory", "a00070.html#gaa6a916b731c903f5314e4d42fdb217b2", [
      [ "kTRDC_MbcSlaveMemory0", "a00070.html#ggaa6a916b731c903f5314e4d42fdb217b2aafb78c1ec3ede012cc1fa385778c804e", null ],
      [ "kTRDC_MbcSlaveMemory1", "a00070.html#ggaa6a916b731c903f5314e4d42fdb217b2ad6945d6587c829f172f85b0e50099ce4", null ],
      [ "kTRDC_MbcSlaveMemory2", "a00070.html#ggaa6a916b731c903f5314e4d42fdb217b2a8b046ecca5a9840d7c4309dd9de06f9a", null ],
      [ "kTRDC_MbcSlaveMemory3", "a00070.html#ggaa6a916b731c903f5314e4d42fdb217b2a3e6d4a53fc282dca458f2d2282bcaba8", null ]
    ] ],
    [ "_trdc_MBC_bit", "a00070.html#ga0d5f8af1430b19de28eebc51381abe60", [
      [ "kTRDC_MbcBit0", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60aeb62413b3ac45ada22119cf0fe92193b", null ],
      [ "kTRDC_MbcBit1", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a82b6ee6cdfd711e46c3b6f71a555c37c", null ],
      [ "kTRDC_MbcBit2", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a09055d403dc84a6499af6424c24dfac3", null ],
      [ "kTRDC_MbcBit3", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a0505eb241811aa63844da820839a4152", null ],
      [ "kTRDC_MbcBit4", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60ae70e3488f6975771efe3f8b6dc20f135", null ],
      [ "kTRDC_MbcBit5", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60abd4dd6d3ebbf30a58ad773e709567861", null ],
      [ "kTRDC_MbcBit6", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a9f34552a004321a73842c8c774abaa14", null ],
      [ "kTRDC_MbcBit7", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a867e65f47d8a581ef88875200edb5e55", null ],
      [ "kTRDC_MbcBit8", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60aca59899e61bfe4febb9381e660e8b861", null ],
      [ "kTRDC_MbcBit9", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a8034894051c0eeda58dad0b34d8e5045", null ],
      [ "kTRDC_MbcBit10", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a3ce5baf77c5dba1127ce456559c1468e", null ],
      [ "kTRDC_MbcBit11", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60af95d51f2491cf07f749c176ec78822f5", null ],
      [ "kTRDC_MbcBit12", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60af24642f87591c515e6fc79fb5ea1d098", null ],
      [ "kTRDC_MbcBit13", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a7d7efb6470df7a0253ecdca6f5b0cc2d", null ],
      [ "kTRDC_MbcBit14", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a1cb3c2cd5c448e7eed3600d4daa9f910", null ],
      [ "kTRDC_MbcBit15", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a4a30119fae86fb76a8acc4bc25e77bc8", null ],
      [ "kTRDC_MbcBit16", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a6a8b5fcf4cda8b40aff9caf6ec972d21", null ],
      [ "kTRDC_MbcBit17", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a47f134ae9700db88e4ae2455d726eca3", null ],
      [ "kTRDC_MbcBit18", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60ac88ffaac0f3c3095e54d3662cbb30e9a", null ],
      [ "kTRDC_MbcBit19", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a5a0cc9f133f31724239ba5d7b5c027a1", null ],
      [ "kTRDC_MbcBit20", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60aaf0070bfc62ca208b198c3a1cf2c9ed7", null ],
      [ "kTRDC_MbcBit21", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a90e6fd0d89a7bce57e893d3d8025485f", null ],
      [ "kTRDC_MbcBit22", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a8fe1c2137323c33b4276903af4d524ac", null ],
      [ "kTRDC_MbcBit23", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60adb3d37754f3ff1bc748ebb42a5333029", null ],
      [ "kTRDC_MbcBit24", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a43f20a6a84c3dbaf15c3afee03f85a21", null ],
      [ "kTRDC_MbcBit25", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60aeb1d3cd5bd22436c3c50a062106dd9c7", null ],
      [ "kTRDC_MbcBit26", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a1681fcbae92f479090f2c44462124ed1", null ],
      [ "kTRDC_MbcBit27", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a43efb7d7956063362ae623ea40d6aacb", null ],
      [ "kTRDC_MbcBit28", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a2418686a7cd7fed13c5e2b540e4e30ea", null ],
      [ "kTRDC_MbcBit29", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a90f283fdf9ed84a59269e1c3c8060875", null ],
      [ "kTRDC_MbcBit30", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a4c4aee7ef3521427760c3d923c167879", null ],
      [ "kTRDC_MbcBit31", "a00070.html#gga0d5f8af1430b19de28eebc51381abe60a5efa2dbcba0a659e89125c17d4781627", null ]
    ] ],
    [ "TRDC_Init", "a00070.html#gaad1c144169295e3f148acbf79d51583f", null ],
    [ "TRDC_Deinit", "a00070.html#gafc87fbd4b2cfef01416651b5fc2e8c0a", null ],
    [ "TRDC_GetCurrentMasterDomainId", "a00070.html#gaed0f40078ef0c828eb7b46b2b361603c", null ],
    [ "TRDC_GetHardwareConfig", "a00070.html#gac3d7fd0ea1d31cfd2184009385b032b7", null ],
    [ "TRDC_SetDacGlobalValid", "a00070.html#gaa1ba6a02d4ea99b05598da60a9628b5f", null ],
    [ "TRDC_LockMasterDomainAssignment", "a00070.html#ga03655339e65c69d6c51f119c9371b2a0", null ],
    [ "TRDC_SetMasterDomainAssignmentValid", "a00070.html#ga52f293e7e10796dd1dd12ef7aa332ef4", null ],
    [ "TRDC_GetDefaultProcessorDomainAssignment", "a00070.html#ga8ad5de94bb2a316aec979f06cd7321c9", null ],
    [ "TRDC_GetDefaultNonProcessorDomainAssignment", "a00070.html#gaf192f669b9468288066eb980863dc3d2", null ],
    [ "TRDC_SetProcessorDomainAssignment", "a00070.html#ga0e6032924a0b374b495a43d652f4a9c3", null ],
    [ "TRDC_SetNonProcessorDomainAssignment", "a00070.html#gac8025d11bfd6e05c17d8ac5d5b15ec79", null ],
    [ "TRDC_GetActiveMasterPidMap", "a00070.html#gafa20908025056eef41915c0d654c018a", null ],
    [ "TRDC_SetPid", "a00070.html#ga7d9131722a272c2e788794d44f187bd9", null ],
    [ "TRDC_GetDefaultIDAUConfig", "a00070.html#ga3d4fad918015811b877c859e5453ded4", null ],
    [ "TRDC_SetIDAU", "a00070.html#ga992fe55e0455072ca212db0285d51f48", null ],
    [ "TRDC_EnableFlashLogicalWindow", "a00070.html#ga96bf4da50ee52e12f6b194f41e24989f", null ],
    [ "TRDC_LockFlashLogicalWindow", "a00070.html#ga3dbd9eeb05672de39612624bd3233ec4", null ],
    [ "TRDC_GetFlashLogicalWindowPbase", "a00070.html#ga65cf2acf889a31604b2d1ba0c86b50ce", null ],
    [ "TRDC_GetSetFlashLogicalWindowSize", "a00070.html#ga6a73ea4ef1e7aedcfb5be026a6f474d7", null ],
    [ "TRDC_GetDefaultFlashLogicalWindowConfig", "a00070.html#ga7f0c9758ce9b9750fb443900e590af6b", null ],
    [ "TRDC_SetFlashLogicalWindow", "a00070.html#gabc1f74e2c03f5694e14bc43a81701297", null ],
    [ "TRDC_GetAndClearFirstDomainError", "a00070.html#ga85b0a61614205ebe8c5d16d24310eb75", null ],
    [ "TRDC_GetAndClearFirstSpecificDomainError", "a00070.html#gafc9c40557b1a90db71d6f204b6e1dcfd", null ],
    [ "TRDC_SetMrcGlobalValid", "a00070.html#ga066174e503ddf0acfb9a3f1c6bf9276f", null ],
    [ "TRDC_GetMrcRegionNumber", "a00070.html#gaf624b101d27e7898c92fe0edf62cdb0c", null ],
    [ "TRDC_MrcSetMemoryAccessConfig", "a00070.html#ga8fc37dd1ec3fa27c7e159a12e69f8236", null ],
    [ "TRDC_MrcEnableDomainNseUpdate", "a00070.html#ga37688b0eebc3d17ea5df89eb959132e7", null ],
    [ "TRDC_MrcRegionNseSet", "a00070.html#gab2d22c26a3f6d5adce8c05b0e7594bdc", null ],
    [ "TRDC_MrcRegionNseClear", "a00070.html#ga7ebd7accac401ba7c752a92f712ff46f", null ],
    [ "TRDC_MrcDomainNseClear", "a00070.html#ga69b5b4781ff9e5ac7cd5f3e0ddf2251a", null ],
    [ "TRDC_MrcSetRegionDescriptorConfig", "a00070.html#ga65775efb5bd013231927c05306a6572c", null ],
    [ "TRDC_SetMbcGlobalValid", "a00070.html#ga658dc249f0d6cd87ac5ae3abe5f6d309", null ],
    [ "TRDC_GetMbcHardwareConfig", "a00070.html#ga3c1f23f6d739ce92b506a8810c20225b", null ],
    [ "TRDC_MbcSetNseUpdateConfig", "a00070.html#ga44906a0628d4082932a66b4425bebb4c", null ],
    [ "TRDC_MbcWordNseSet", "a00070.html#ga2435b3307133cd28b7b029bf3eb3dbd6", null ],
    [ "TRDC_MbcWordNseClear", "a00070.html#ga12bb9d1369b902c8dc149d7776e24b68", null ],
    [ "TRDC_MbcNseClearAll", "a00070.html#gaaaf0d126ff4151d1c630c908e6ccf371", null ],
    [ "TRDC_MbcSetMemoryAccessConfig", "a00070.html#ga19deccf56fb843c1dc174dba93da3650", null ],
    [ "TRDC_MbcSetMemoryBlockConfig", "a00070.html#gac4ea7d412097c18a4c653aaec6ff230b", null ]
];