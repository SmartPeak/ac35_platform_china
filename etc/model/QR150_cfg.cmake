# 此文件为QR150专属配置文件

# 没有主显示器
STRING(APPEND CMAKE_C_FLAGS " -DBWLCD_NO_MAINLCD ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_GPIO_SCAN_KEY ")

MESSAGE("##############################################")
MESSAGE("# QR150 config loaded!")
MESSAGE("##############################################")
