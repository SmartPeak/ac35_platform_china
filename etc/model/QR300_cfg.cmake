# ���ļ�ΪQR300ר�������ļ�

# HAVE_CHARGING_FEATURE: ʹ�õ�ع��磬֧�ֳ�繦��
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

STRING(APPEND CMAKE_C_FLAGS " -DHAVE_STD_MATRIX_KPD ")

# WIFIģ��λ��AP_UART1�ӿ���
STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_AP_UART1 ")

MESSAGE("##############################################")
MESSAGE("# QR300 config loaded!")
MESSAGE("##############################################")
