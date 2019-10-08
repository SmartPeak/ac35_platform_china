# 此文件为QR100专属配置文件

# HAVE_CHARGING_FEATURE: 使用电池供电，支持充电功能
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_STD_MATRIX_KPD ")
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_GPIO_SCAN_KEY ")

STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR100 config loaded!")
MESSAGE("##############################################")

