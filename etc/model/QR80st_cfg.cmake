# 此文件为QR80ST专属配置文件

# 没有主显示器
STRING(APPEND CMAKE_C_FLAGS " -DBWLCD_NO_MAINLCD ")

# P1之后，键盘位于SP上
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# P1之后，在SP上有LCD
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_LCD_ON_SP ")

# P1之后，WIFI模块位于AP_UART1接口上
STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR80ST config loaded!")
MESSAGE("##############################################")
