# ���ļ�ΪP90ר�������ļ�

# HAVE_CHARGING_FEATURE: ʹ�õ�ع��磬֧�ֳ�繦��
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_CHARGING_FEATURE ")

# ʹ�����±�׼�ľ������
#STRING(APPEND CMAKE_C_FLAGS " -DHAVE_STD_MATRIX_KPD ")

# WIFIλ��SP��
#STRING(APPEND CMAKE_C_FLAGS " -DWLAN_ON_SP ")

# WIFIģ��ʹ��SPI�ӿ�
STRING(APPEND CMAKE_C_FLAGS " -DBWWLAN_SPI ")

# ����λ��SP��
STRING(APPEND CMAKE_C_FLAGS " -DKEYPAD_ON_SP ")

# ֧��SIM�л�����
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_SIMSWITCH ")

# ʹ�������ֿ�(ASCII + Latin1: wzk24s)
STRING(APPEND CMAKE_C_FLAGS " -DFEATURE_USE_OEM_WEST_FONTLIB ")

# ֧��SDMģ��
STRING(APPEND CMAKE_C_FLAGS " -DHAVE_SDM ")

# ����mbedtls����PCI V5.xҪ��
#STRING(APPEND CMAKE_C_FLAGS " -DPCI_CERTIFICATION_TAG ")

# ָ���ļ�ϵͳʵ�ַ�ʽ
# ����Ϊ3��֮һ
# 1 �����ڵװ���ʵ�ֵ�FAT�ļ�ϵͳ
# 2 �û��Լ�ʵ�ֵ�LFS�ļ�ϵͳ
# 3 �����ڵװ���ʵ�ֵ�LFS�ļ�ϵͳ
SET(FILESYSTEM_IMPL_METHOD 2)

# �����Ƿ�֧������3Gģ��
# 0 ��֧��
# 1 ֧��
SET(OPTION_EXTERNAL_3G_MODEM 1)

MESSAGE("##############################################")
MESSAGE("# P90 config loaded!")
MESSAGE("##############################################")

