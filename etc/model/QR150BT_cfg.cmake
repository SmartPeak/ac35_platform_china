# 此文件为QR150BT专属配置文件

# 没有主显示器
STRING(APPEND CMAKE_C_FLAGS " -DBWLCD_NO_MAINLCD ")

# HAVE_CHARGING_FEATURE: 使用电池供电，支持充电功能
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_GPIO_SCAN_KEY ")

# BT模块位于AP_UART1接口上
STRING(APPEND CMAKE_C_FLAGS " -DBT_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR150BT config loaded!")
MESSAGE("##############################################")
