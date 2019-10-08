# 此文件为QR200专属配置文件

# 键盘位于SP上
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# 在SP上有LCD
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_LCD_ON_SP ")

# WIFI模块位于AP_UART1接口上
STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR200 config loaded!")
MESSAGE("##############################################")
