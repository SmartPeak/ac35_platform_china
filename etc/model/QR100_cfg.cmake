# ���ļ�ΪQR100ר�������ļ�

# HAVE_CHARGING_FEATURE: ʹ�õ�ع��磬֧�ֳ�繦��
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_STD_MATRIX_KPD ")
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_GPIO_SCAN_KEY ")

STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR100 config loaded!")
MESSAGE("##############################################")

