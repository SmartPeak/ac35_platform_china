# 此文件为P90专属配置文件

# HAVE_CHARGING_FEATURE: 使用电池供电，支持充电功能
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

# 使用夏新标准的矩阵键盘
#STRING(APPEND CMAKE_C_FLAGS " -DHAVE_STD_MATRIX_KPD ")

# WIFI位于SP上
#STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_SP ")

# WIFI模块使用SPI接口
STRING(APPEND CMAKE_C_FLAGS " -DBWWLAN_SPI ")

# 键盘位于SP上
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# 支持SIM切换功能
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_SIMSWITCH ")

# 使用西文字库(ASCII + Latin1: wzk24s)
STRING(APPEND CMAKE_C_FLAGS " -DFEATURE_USE_OEM_WEST_FONTLIB ")

# 支持SDM模块
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_SDM ")

# 配置mbedtls符合PCI V5.x要求
#STRING(APPEND CMAKE_C_FLAGS " -DPCI_CERTIFICATION_TAG ")

# 指定文件系统实现方式
# 必须为3者之一
# 1 夏新在底包中实现的FAT文件系统
# 2 用户自己实现的LFS文件系统
# 3 夏新在底包中实现的LFS文件系统
SET(FILESYSTEM_IMPL_METHOD 2)

# 设置是否支持外置3G模块
# 0 不支持
# 1 支持
SET(OPTION_EXTERNAL_3G_MODEM 1)

MESSAGE("##############################################")
MESSAGE("# P90 config loaded!")
MESSAGE("##############################################")

