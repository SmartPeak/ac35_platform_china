# -*- coding: cp936 -*-
import sys,os,glob
import ConfigParser
import subprocess
import re
sys.path.append('sbin/')
from _device import device
from _cmdtool import zip7z

program_name    = "QR And P90 Product Configuration Tool"
version         = "V1.2"

cmakeFile       = "tmp_config.cmake"
buildFile       = "tmp_build.cmd"
updFile         = 'sbin/upd.tmp'

def usage():
    print '=============================================='
    print '= %s' %program_name
    print '= %s' %version
    print '=============================================='

def ErrMsg(value):
    print('================================')
    print(' mmmmmm   mm   mmmmm  m '  )
    print(' #        ##     #    # '   )
    print(' #mmmmm  #  #    #    # '  )
    print(' #       #mm#    #    # '  )
    print(' #      #    # mm#mm  #mmmmm')
    print('================================')
    if value != None:
        print value

def enum(**enums):
    return type('Enum', (), enums)

def API_Inut(str = None):
    try:
        if(str == None or len(str) <= 0):
            choice = input()
        else:
            choice = input(str)
    except Exception as e:
        choice = -1
    return choice

def API_Quit():
    sys.exit(0)
    return 0

def API_Mkdir(path):
    path = path.strip()
    path = path.replace('/','\\')
    path = path.rstrip("\\")

    if not os.path.exists(path):
        os.makedirs(path)
    if not os.path.exists(path):
        return -1
    return 0

def API_ChooseFile(files = '*.*', path = ''):
    fileName = ''
    fileList = glob.glob('%s%s' %(path, files))
    if(len(fileList) <= 0):
        return fileName

    for i,fileName in enumerate(fileList):
        print("[%3d ] %s" %(i+1, os.path.split(fileName)[1]))
    while True:
        fileName = ''
        choice = API_Inut("please choose(0-Exit): ")
        if(choice == 0):
            break
        elif(0 < choice <= len(fileList)):
            fileName = fileList[choice-1]
            break
    return fileName

#funFlag: [0]=onlyOne value return
#funFlag: [1]=select all/format:keyValue|display msg
def API_Choose(funFlag = [], caption = 'please choose', listData = '', splitStr = ','):
    fileName = ''
    fileList = re.split('[%s]' %splitStr, listData)
    if(len(fileList) <= 0):
        return fileName
    if(funFlag[0] == 1 and len(fileList) == 1):
        return fileList[0]

    print("\n=====================================================")
    print("%s:\n" %caption)
    for i,fileName in enumerate(fileList):
        print("[%3d] %s" %(i+1, fileName))
    print("----------------------------------------"),
    print("\n 0-Exit    "),
    if(len(funFlag) == 3):
        print("%s-%s" %(funFlag[1], funFlag[2])),
    print("\n----------------------------------------")
    while True:
        fileName = ''
        choice = API_Inut("  ")
        if(choice == 0):
            break
        elif(len(funFlag) == 3 and choice == funFlag[1]):
            fileName = funFlag[2]
            print("choose: %s\n" %funFlag[2])
            break;
        elif(0 < choice <= len(fileList)):
            fileName = fileList[choice-1]
            print("choose: %s\n" %fileName)
            break
    return fileName

# 产生指定配置的编译命令
# 返回: 编译命令文件名
def GenBuildCmd(modelname, buildtype, custName, custSubName, target="APP", ver=None, needpause=None, path=''):
    appInfoFile = 'appInfo.ini'
    config = []
    config.append("@echo off")
    config.append("::==============================")
    config.append("::Auto Generated By configure.py")
    config.append("::DO NOT EDIT THIS FILE")
    config.append("::==============================")
    config.append("@set BUILD_DEST_PATH=%s" %(path.replace('/','\\')))
    config.append("@set BUILD_APP_INFO_FILE=%s%s" %(path.replace('/','\\'), appInfoFile))
    config.append("@set QR_PRODUCT_MODEL=%s" % (modelname))
    config.append("@set QR_BUILD_TYPE=%s" % (buildtype))
    config.append("@set QR_BUILD_TARGET=%s" % (target))
    config.append("@set QR_CUSTOMER_NAME=%s" % (custName))
    config.append("@set QR_CUSTOMER_SUBNAME=%s" % (custSubName))
    if ver != None:
        config.append("@call build.cmd %s" % (ver))
    else:
        config.append("@call build.cmd")

    #_%APP_BUILD_DATE%
    fileName = '%QR_PRODUCT_MODEL%_%QR_CUSTOMER_NAME%.%QR_CUSTOMER_SUBNAME%_%QR_BUILD_TYPE%_%APP_VERSION%'
    if (custSubName == None or custSubName == ''):
        fileName = '%QR_PRODUCT_MODEL%_%QR_CUSTOMER_NAME%_%QR_BUILD_TYPE%_%APP_VERSION%'
    config.append("@set OUTPUT_APPNAME=%s.img" %(fileName))
    config.append("@set OUTPUT_SIGNED_APPNAME=%s_signed.img" %(fileName))
    #----
    config.append("@IF EXIST %BUILD_DEST_PATH%%OUTPUT_APPNAME% @del /F %BUILD_DEST_PATH%%OUTPUT_APPNAME%")
    config.append("@IF EXIST %BUILD_DEST_PATH%%OUTPUT_SIGNED_APPNAME% @del /F %BUILD_DEST_PATH%%OUTPUT_SIGNED_APPNAME%")
    config.append("@IF EXIST %BUILD_APP_INFO_FILE% @del /F %BUILD_APP_INFO_FILE%")
    #----
    config.append("@IF NOT EXIST out\showAPP.img goto fail")
    config.append("@copy out\showAPP.img %BUILD_DEST_PATH%%OUTPUT_APPNAME%")
    config.append("@IF NOT EXIST out\showAPP_signed.img goto fail")
    config.append("@copy out\showAPP_signed.img %BUILD_DEST_PATH%%OUTPUT_SIGNED_APPNAME%")
    #----
    config.append("@echo [appInfo] > %BUILD_APP_INFO_FILE%")
    config.append("@echo model = %QR_PRODUCT_MODEL% >> %BUILD_APP_INFO_FILE%")
    config.append("@echo appFile = %OUTPUT_SIGNED_APPNAME% >> %BUILD_APP_INFO_FILE%")
    #----
    config.append(":success")
    config.append('@ECHO ================================')
    config.append('@ECHO.')
    config.append('@ECHO  mmmmm    mm    mmmm   mmmm ')
    config.append('@ECHO  #   "#   ##   #"   " #"   "')
    config.append('@ECHO  #mmm#"  #  #  "#mmm  "#mmm')
    config.append('@ECHO  #       #mm#      "#     "#')
    config.append('@ECHO  #      #    # "mmm#" "mmm#"')
    config.append('@ECHO.')
    config.append('@ECHO ================================')
    config.append("@goto end")
    config.append(":fail")
    config.append('@ECHO ================================')
    config.append('@ECHO.')
    config.append('@ECHO  mmmmmm   mm   mmmmm  m '  )
    config.append('@ECHO  #        ##     #    # '   )
    config.append('@ECHO  #mmmmm  #  #    #    # '  )
    config.append('@ECHO  #       #mm#    #    # '  )
    config.append('@ECHO  #      #    # mm#mm  #mmmmm')
    config.append('@ECHO.')
    config.append('@ECHO ================================')
    config.append(":end")

    if needpause == True:
        config.append("@pause")
    try:
        fd = open(buildFile, mode='w+')
        for line in config:
            fd.write("%s\n" % line)
        fd.close()

        API_Mkdir(path)
        os.system(buildFile)
        return 0
    except:
        return -1

#==================================================
class configure:
    E_cfgType = enum(CFG_PDK=0, CFG_APP=1, CFG_APP_INF0=2)
    def __init__(self):
        self.cfgType = self.E_cfgType.CFG_PDK
        self.sCfg = {}

    def delFile(self, fileName):
        if (os.path.isfile(fileName)):
            os.remove(fileName)

    def getConfigValue(self, node, key):
        value = None
        print('[%18s]%-22s= ' %(node,key)),
        try:
            value = self.config.get(node, key)
            if (value == "" or value == None):
                print("")
                return -1
            else:
                if(self.cfgType == self.E_cfgType.CFG_PDK):
                    key = '[pdk]%s->%s' %(node,key)
                elif(self.cfgType == self.E_cfgType.CFG_APP_INF0):
                    key = '[appInfo]%s->%s' %(node,key)
                elif(node == 'model_config'):
                    key = 'dev_%s' %key

                self.sCfg[key] = value
                print("%s" %value)
            return 0
        except:
            print(' err!!!')
            return -1

    def readIniFile(self, fileName = '', path = ''):
        if (len(fileName) <= 0):
            return -1

        if(len(path) > 0):
            fileName = "%s%s" %(path, fileName)

        print('load config file [%s]\n' %fileName)
        if (os.path.isfile(fileName) == False):
            return -1
        self.config = ConfigParser.ConfigParser()
        self.config.read(fileName)
        return 0

    def delAppCfgFile(self):
        self.delFile(cmakeFile)
        self.delFile(buildFile)

    def loadPDKConfig(self, path = ''):
        print("__________________ load pdk config __________________")
        self.cfgType = self.E_cfgType.CFG_PDK
        ret = self.readIniFile('pdk.ini', path)
        #-------------------------------------------------------------------------------------------
        if(ret == 0):
            ret = self.getConfigValue('config', 'model_list')
        if(ret == 0):
            ret = self.getConfigValue('config', 'app_path')
        if(ret == 0):
            ret = self.getConfigValue('config', 'dest_dir')
        if(ret == 0):
            ret = self.getConfigValue('config', 'font_list')
        if(ret == 0):
            ret = self.getConfigValue('mainapp', 'localpath')
        if(ret == 0):
            ret = self.getConfigValue('font', 'localpath')
        if(ret == 0):
            ret = self.getConfigValue('logo', 'localpath')
        #-------------------------------------------------------------------------------------------
        print("\nload pdk config"),
        if(ret != 0):
            print("err!!!\n")
        else:
            print("success\n")
        return ret

    def loadAppInfo(self):
        print("__________________ load app info __________________")
        self.cfgType = self.E_cfgType.CFG_APP_INF0
        ret = self.readIniFile('appInfo.ini', self.sCfg['bin_path'])
        #-------------------------------------------------------------------------------------------
        if(ret == 0):
            ret = self.getConfigValue('appInfo', 'model')
        if(ret == 0):
            ret = self.getConfigValue('appInfo', 'appFile')
        #-------------------------------------------------------------------------------------------
        print("\nload app info"),
        if(ret != 0):
            print("err!!!\n")
        else:
            print("success\n")
        return ret

    def loadAppConfig(self, buildEnable, path = None):
        print("__________________ load app config __________________")
        self.cfgType = self.E_cfgType.CFG_APP
        self.sCfg['app_path'] = '%s/%s/' %(self.sCfg['[pdk]config->app_path'], path)
        self.sCfg['bin_path'] = '%s/%s/' %(self.sCfg['app_path'], self.sCfg['[pdk]config->dest_dir'])
        ret = self.readIniFile('config.ini', self.sCfg['app_path'])
        #-------------------------------------------------------------------------------------------
        if(ret == 0):
            ret = self.getConfigValue('app_config', 'app_customer_name')
        if(ret == 0):    
            self.sCfg['app_customer_name'] = API_Choose([1], 'Choose customer name', self.sCfg['app_customer_name'], '/\|')
            if(len(self.sCfg['app_customer_name']) <= 0):
                ret = -1
        if(ret == 0):
            ret = self.getConfigValue('app_config', 'app_ver')
        if(ret == 0):
            ret = self.getConfigValue('app_config', 'enable_svn_revision')
        if(ret == 0):
            if(self.getConfigValue('app_config', 'model_name') != 0):
                self.sCfg['model_name'] = API_Choose([0], 'Choose Model', self.sCfg['[pdk]config->model_list'], ',/\|')
            else:
                self.sCfg['model_name'] = API_Choose([1], 'Choose Model', self.sCfg['model_name'], ',/\|')
            if(len(self.sCfg['model_name']) <= 0):
                ret = -1
        if(ret == 0 and buildEnable == 1):
            if(self.getConfigValue('app_config', 'build_type') != 0):
                self.sCfg['build_type'] = API_Choose([0], 'Choose Build Type', 'Release|Debug', '|')
            if(len(self.sCfg['build_type']) <= 0):
                ret = -1
        if(ret == 0):
            ret = self.getConfigValue('model_config', self.sCfg['model_name'])
        if(ret == 0):
            node = self.sCfg['dev_%s' %self.sCfg['model_name']]
        if(ret == 0):
            ret = self.getConfigValue(node, 'platform_ver')
        if(ret == 0):
            ret = self.getConfigValue(node, 'sdk_ver')
        if(ret == 0):
            ret = self.getConfigValue(node, 'applib_ver')
        if(ret == 0):
            self.getConfigValue(node, 'emv_ver')
            self.getConfigValue(node, 'user_libs')
        if(ret == 0):
            ret = self.getConfigValue(node, 'sdm_enable')
        if(ret == 0):
            self.getConfigValue(node, 'logo_img')
            self.getConfigValue(node, 'main_app')
            self.getConfigValue(node, 'font_file')
            self.getConfigValue(node, 'param_file')
        #-------------------------------------------------------------------------------------------
        print("\nload app config"),
        if(ret != 0):
            print("err!!!\n")
        else:
            print("success\n")
        return ret

    def loadConfig(self, buildEnable, path = None):
        print("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> load config(B) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
        ret = self.loadPDKConfig()
        if(ret == 0 and path != None):
            ret = self.loadAppConfig(buildEnable, path)
        print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>> load config(E) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n")
        return ret

    # generate make config file
    def GenCmakeConfigCmd(self):
        cmake = []
        #-------------------------------------------------------------------------------------------
        # AC35 platform version
        cmake.append("SET(PLATFORM_VER %s)\n" %self.sCfg['platform_ver'])

        # SDK version
        cmake.append("SET(SDK_VER %s)\n" %self.sCfg['sdk_ver'])

        # applib version
        cmake.append("SET(APPLIB_VER %s)\n" %self.sCfg['applib_ver'])

        # emv version
        if 'emv_ver' in self.sCfg:
            cmake.append("SET(EMV_VER %s)\n" %self.sCfg['emv_ver'])

        # third lib
        if 'user_libs' in self.sCfg:
            cmake.append("SET(USER_LIBS %s)\n" %self.sCfg['user_libs'])

        # app path
        cmake.append("SET(APP_PATH %s)\n" %self.sCfg['app_path'])
        #-------------------------------------------------------------------------------------------

        # 需要AliyunIOT时开启，注释掉即关闭
        #cmake.append("SET(ALIYUN_IOT_TARGET YES)")

        # 需要MQ时开启，注释掉即关闭
        cmake.append("SET(ALIYUN_MQ_TARGET YES)")

        # 需要开启Sensor触发远程解锁时开启，注释掉关闭
        #cmake.append("SET(SECURITY_WITH_AR YES)")

        #-------------------------------------------------------------------------------------------
        #write config.cmake
        try:
            fd = open(cmakeFile, mode='w+')
            for line in cmake:
                fd.write("%s\n" % line)
            fd.close()
            return 0
        except:
            return -1

    # get svn info revision
    def slot_getSvnRevision(self):
        subVer = None
        if (self.sCfg['enable_svn_revision'] == "true"):
            t = os.popen('svn info %s' %self.sCfg['app_path'])
            list = t.read().splitlines()
            for str in list:
                if str.find('Revision:') >= 0:
                    version = re.findall("\d+", str)
                    subVer = version[0]
        return subVer

class Menu():
    def __init__(self, path=None):
        self.enableInput    = 1
        self.path           = path
        self.E_MenuType     = enum(MT_MainMenu=0, MT_ToolMenu=1)

        self.signals_home = {
            "1": device().formatFilesSystem,
            "2": device().setAutoRun,
            "3": device().setDontAutoRun,
            "4": self.slot_setLogo,
            "5": self.noSupport,
            "6": self.slot_downloadMainApp,
            "7": self.slot_downloadFont,

            "r": self.slot_rebootPOS,
            "q": API_Quit
        }

        self.signals_tool = {
            "1": self.slot_buildClean,
            "2": self.slot_build,
            "3": self.slot_downloadApp,

            "11": device().formatFilesSystem,
            "12": device().setAutoRun,
            "13": device().setDontAutoRun,
            "14": self.slot_setLogo,

            "21": self.noSupport,
            "22": self.slot_downloadMainApp,
            "23": self.slot_downloadFont,
            "24": self.slot_downloadResource,

            "r": self.slot_rebootPOS,
            "q": API_Quit
        }

    def getInput(self):
        if (self.enableInput == 1):
            return 1
        raw_input("[ Press Enter To Back Menu ]")
        return 0

    def clean(self):
        subprocess.call("cls", shell=True)

    def usage(self):
        str = '%s application' %self.path
        print ("__________________________________________________")
        print ('\n %s %s\n' %(program_name,version))
        print ('%32s' %str)
        print ("__________________________________________________")

    def noSupport(self):
        print ("\n    该功能暂不支持!!!")
        self.getInput()

    def click(self, _menuType):
        print ("__________________________________________________\n")
        print (" [ R ]Reboot Device                    [ Q ]Quit")
        print ("__________________________________________________")

        try:
            choice = raw_input()
            if (_menuType == self.E_MenuType.MT_ToolMenu):
                action = self.signals_tool.get(choice.lower())
            else:
                action = self.signals_home.get(choice.lower())

            if action:
                self.clean()
                return action()
            return -1
        except Exception as e:
            return -1

    def slot_back(self):
        return 1

    def slot_buildClean(self):
        print "clean build..."
        os.system("000_clean.cmd")
        self.getInput()
        return 0

    def slot_build(self):
        print "build app..."
        print('path:%s' %self.path)

        sConfigure = configure()
        # delete temp file
        sConfigure.delAppCfgFile()
        # read app config.ini
        ret = sConfigure.loadConfig(1, self.path)
        # generate make config file
        if(ret == 0):
            ret = sConfigure.GenCmakeConfigCmd()
        # set version
        if(ret == 0):
            ver = sConfigure.sCfg['app_ver']
        # set sub version
        if(ret == 0):
            subVer = sConfigure.slot_getSvnRevision()
        if (ret == 0 and subVer == None):
            subVer = raw_input("input sub version([enter]no sub version):")
        if (ret == 0 and len(subVer) > 0):
            ver = '%s.%s' %(ver, subVer)
        # generate build script file
        if(ret == 0):
            localpath = sConfigure.sCfg['bin_path']
            print('localpath:%s' %localpath)
            
            custName = sConfigure.sCfg['app_customer_name']
            custSubName = ''
            fileList = re.split(',', custName)
            if(len(fileList) > 1):
                custName = fileList[0]
                custSubName = fileList[1]
            elif(len(fileList) > 0):
                custName = fileList[0]
            GenBuildCmd(sConfigure.sCfg['model_name'], sConfigure.sCfg['build_type'], custName, custSubName, 'APP', ver, False, localpath)
        sConfigure.delAppCfgFile()
        self.getInput()
        return ret

    def slot_rebootPOS(self):
        ret = device().reboot()
        if(ret == 0):
            device().runApp()
        if(ret != 0):
            ErrMsg("download main app err!!!")
        self.getInput()

    def slot_setLogo(self):
        print "set logo..."
        print('path:%s' %self.path)

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        if(ret == 0):
            if 'logo_img' not in sConfigure.sCfg:
                fileName = API_ChooseFile('*.bmp', sConfigure.sCfg['[pdk]logo->localpath'])
            else:
                fileName = '%s/%s' %(sConfigure.sCfg['app_path'], sConfigure.sCfg['logo_img'])
            if(fileName == None or len(fileName) <= 0):
                ret = -1
        if(ret == 0):
            ret = device().setLogo(fileName)
        if(ret != 0):
            ErrMsg("set logo err!!!")
        self.getInput()

    def slot_downloadApp(self):
        print "download app..."
        print('path:%s' %self.path)
        fileName = ''
        sdm_enable = 0

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        if(ret == 0):
            localpath = sConfigure.sCfg['bin_path']
            ret = sConfigure.loadAppInfo()
            # not find appInfo.ini
            if(ret == 0):
                fileName = sConfigure.sCfg['[appInfo]appInfo->appFile']
            else:
                fileName = API_ChooseFile('*.img', localpath)
        # choose app file
        if(ret == 0 and len(fileName) <= 0):
            ret = -1
            print('>>> error: could not find app file')
        if(ret == 0 and sConfigure.sCfg['sdm_enable'] == 'true'):
            sdm_enable = 1
        if(ret == 0):
            ret = device().downloadApp(sdm_enable, '%s%s' %(localpath, fileName), updFile)
        if(ret != 0):
            ErrMsg("down app err!!!")
        self.getInput()

    def slot_downloadMainApp(self):
        print "download main app..."
        print('path:%s' %self.path)

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        if(ret == 0):
            if 'main_app' not in sConfigure.sCfg:
                fileName = API_ChooseFile('*.img', sConfigure.sCfg['[pdk]mainapp->localpath'])
            else:
                fileName = '%s%s' %(sConfigure.sCfg['[pdk]mainapp->localpath'], sConfigure.sCfg['main_app'])
            if(fileName == None or len(fileName) <= 0):
                ret = -1
        if(ret == 0):
            ret = device().downloadMainApp(fileName)
        if(ret == 0):
            self.slot_rebootPOS()
        if(ret != 0):
            ErrMsg("download main app err!!!")
            self.getInput()

    def slot_downloadSP(self):
        print "download sp..."
        print('path:%s' %self.path)

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        # 检索文件
        #if(ret == 0):

        if(ret == 0):
            sdm_enable = 0
            if(sConfigure.sCfg['sdm_enable'] == 'true'):
                sdm_enable = 1

            #sp_file = sConfigure.sCfg['sp_file']
            sp_file = "sp_p90.bin"
            localpath = 'tools/%s' %(sp_file)
            ret = device().pushFile(sdm_enable, localpath, "sp.bin")
        if(ret == 0):
            self.slot_rebootPOS()
        if(ret != 0):
            ErrMsg("download sp err!!!")
            self.getInput()

    def slot_downloadFont(self):
        print "download font..."
        print('path:%s' %self.path)

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        if(ret == 0):
            localpath = '%s/' %sConfigure.sCfg['[pdk]font->localpath']
            sdm_enable = 0
            if 'sdm_enable' in sConfigure.sCfg:
                if(sConfigure.sCfg['sdm_enable'] == 'true'):
                    sdm_enable = 1
            else:
                sysFile = API_Choose([0], 'Choose File System', 'LFS System|FAT System', '|')
                if(len(sysFile) <= 0):
                    ret = -1
                elif(sysFile == 'LFS System'):
                    sdm_enable = 1
        #----
        if(ret == 0):
            while True:
                if 'font_file' in sConfigure.sCfg:
                    font_list = sConfigure.sCfg['font_file']
                else:
                    font_list = sConfigure.sCfg['[pdk]config->font_list']
                if(len(font_list) <= 0):
                    ret = -1
                    break

                fontFile = API_Choose([0, 99, 'Select all'], 'Choose font file', font_list, ',\/')
                font_list = font_list.split(',')
                if(len(fontFile) <= 0):
                    break
                elif(fontFile != 'Select all'):
                    font_list = []
                    font_list.append(fontFile)

                for i,fileName in enumerate(font_list):
                    ret = device().pushFile(sdm_enable, '%s%s'%(localpath, fileName), fileName)
                if(fontFile == 'Select all'):
                    break

        if(ret != 0):
            ErrMsg("download font err!!!")
        self.getInput()

    def slot_downloadResource(self):
        print "download resource..."
        print('path:%s' %self.path)

        # read app config.ini
        sConfigure = configure()
        ret = sConfigure.loadConfig(0, self.path)
        if(ret == 0):
            if 'param_file' not in sConfigure.sCfg:
                ret = -1
        if(ret == 0):
            sdm_enable = 0
            if(sConfigure.sCfg['sdm_enable'] == 'true'):
                sdm_enable = 1

            param_list = sConfigure.sCfg['param_file'].split(',')
            for i,fileName in enumerate(param_list):
                localpath = '%s/resource/%s' %(sConfigure.sCfg['app_path'], fileName)
                ret = device().pushFile(sdm_enable, localpath, fileName)

        if(ret != 0):
            ErrMsg("download param file err!!!")
        self.getInput()

    #-------------------------------------------------------------------------------------
    def menuList_tools(self):
        self.enableInput = 0
        while True:
            self.clean()
            self.usage()
            print("""
         1. Clean Project
         2. Build Project
         3. Download App
     ============================
        11. Format Files System
        12. Set Auto Run
        13. Set Dont Auto Run
        14. Set Logo
     ============================
        21. Download SP
        22. Download MainApp
        23. Download Font
        24. Download Resource""")

            if (self.click(self.E_MenuType.MT_ToolMenu) == 1):
                break

    def menuList_home(self):
        self.enableInput = 0
        while True:
            self.clean()
            self.usage()
            print(">>> Home")
            print("""

         1. Format Files System
         2. Set AutoRun
         3. Set Dont Auto Run
         4. Set Logo
         5. Download SP
         6. Download MainApp
         7. Download Font""")
            if (self.click(self.E_MenuType.MT_MainMenu) == 1):
                break

#==========================================================
def CMD_Help():
    usage();
    print "usage: configure [ <option> ] <parameter>"
    print "commands:"
    print "-build <app src path>        build application"
    print "-clean                       clear application"
    print "-down <type>"
    print "      app                    down app"

if __name__ == "__main__":
    path = None
    if len(sys.argv) > 1:
        path = sys.argv[2]
    pak = Menu(path)

    if len(sys.argv) < 2:
        pak.menuList_home()
    elif sys.argv[1] in ["-clean"]:
        pak.slot_buildClean()
    elif sys.argv[1] in ["-build"]:
        pak.slot_build()
    elif sys.argv[1] in ["-down"]:
        pak.slot_downloadApp()
    elif sys.argv[1] in ["-tools"]:
        pak.menuList_tools()
    else:
        CMD_Help()

