# ���ļ�ΪQR80STר�������ļ�

# û������ʾ��
STRING(APPEND CMAKE_C_FLAGS " -DBWLCD_NO_MAINLCD ")

# P1֮�󣬼���λ��SP��
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# P1֮����SP����LCD
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_LCD_ON_SP ")

# P1֮��WIFIģ��λ��AP_UART1�ӿ���
STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR80ST config loaded!")
MESSAGE("##############################################")
