# ���ļ�ΪQR150BTר�������ļ�

# û������ʾ��
STRING(APPEND CMAKE_C_FLAGS " -DBWLCD_NO_MAINLCD ")

# HAVE_CHARGING_FEATURE: ʹ�õ�ع��磬֧�ֳ�繦��
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_GPIO_SCAN_KEY ")

# BTģ��λ��AP_UART1�ӿ���
STRING(APPEND CMAKE_C_FLAGS " -DBT_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR150BT config loaded!")
MESSAGE("##############################################")
