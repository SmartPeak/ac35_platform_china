# ���ļ�ΪQR200ר�������ļ�

# ����λ��SP��
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# ��SP����LCD
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_LCD_ON_SP ")

# WIFIģ��λ��AP_UART1�ӿ���
STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR200 config loaded!")
MESSAGE("##############################################")
