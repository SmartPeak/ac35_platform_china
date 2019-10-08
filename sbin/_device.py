# -*- coding: cp936 -*-
import sys,os,time
from _cmdtool import fastboot,sdmclient
from _timer import timer

SDMDisabled = 0
SDMEnabled  = 1

class device:
    def displayTitle(self, msg):
        print('\n-------------------------------------------------')
        print(' %s' %(msg))
        print('-------------------------------------------------')

    def shakeHands(self, sdmEnable):
        count = 0
        while(count < 3):
            if(sdmEnable == SDMEnabled):
                ret = sdmclient('version')
            else:
                ret = fastboot('mercuryVersion')
            
            if(ret == 0):
                break
            count = count + 1
        return ret

    def waitDeviceConnect(self, timeout):
        self.displayTitle('wait device connect (about %s seconds)' %(timeout))
        sTimer = timer(timeout*1000)
        while(sTimer.check() > 0):
            if (self.shakeHands(SDMDisabled) == 0):
                return 0
            if (self.shakeHands(SDMEnabled) == 0):
                return 0
            time.sleep(2)
        print("please check device connected!!!")
        return -1

    def runApp(self):
        self.displayTitle('runing app, plz waiting...')
        return fastboot('run app')

    def reboot(self):
        self.displayTitle('device reboot, plz waiting...')
        ret = sdmclient('reset')
        if (ret != 0):
            ret = fastboot('reset')
        if (ret == 0):
            ret = self.waitDeviceConnect(40)
        return ret

    def readFileList(self, sdmEnable, path = None):
        self.displayTitle('read file list %s, plz waiting...' %(path))
        if (os.path.isfile(localpath) == False):
            return -1

        ret = self.shakeHands(sdmEnable)
        if(ret != 0):
            ret = self.reboot()
            if (ret == 0):
                self.runApp()
        if(ret == 0):
            if(sdmEnable == SDMEnabled):
                ret = sdmclient('push %s %s' %(localpath, fileName))
            else:
                ret = fastboot('push %s e:\%s' %(localpath, fileName))
        return ret

    def setAutoRun(self):
        self.displayTitle('set device auto run...')
        ret = self.shakeHands(SDMEnabled)
        if(ret == 0):
            ret = sdmclient('stop')
        if(ret != 0):
            ret = self.shakeHands(SDMDisabled)
        if(ret == 0):
            ret = fastboot('autoRun')
        if(ret == 0):
            ret = self.reboot()
        return ret

    def setDontAutoRun(self):
        self.displayTitle('set device dont auto run...')
        ret = self.shakeHands(SDMEnabled)
        if(ret == 0):
            ret = sdmclient('stop')
        if(ret != 0):
            ret = self.shakeHands(SDMDisabled)
        if(ret == 0):
            ret = fastboot('DontAutoRun')
        if(ret == 0):
            ret = self.reboot()
        return ret

    def setLogo(self, fileName):
        self.displayTitle('set logo %s, plz waiting...' %(fileName))
        if (os.path.isfile(fileName) == False):
            return -1
        ret = self.shakeHands(SDMEnabled)
        if(ret == 0):
            ret = sdmclient('stop')
        if(ret != 0):
            ret = self.shakeHands(SDMDisabled)
        if(ret == 0):
            ret = fastboot('DontAutoRun')

        ret = self.reboot()
        if(ret == 0):
            ret = fastboot('setLogo %s 0 0 0' %(fileName))
        if(ret == 0):
            ret = fastboot('autoRun')
        if(ret == 0 or ret == 99):
            ret = self.runApp()
        return ret

    def pushFile(self, sdmEnable, localpath, fileName):
        self.displayTitle('download file %s, plz waiting...' %(fileName))
        if (os.path.isfile(localpath) == False):
            return -1

        ret = self.shakeHands(sdmEnable)
        if(ret != 0):
            ret = self.reboot()
            if (ret == 0):
                ret = self.runApp()
            if (ret == 0):
                sTimer = timer(5*1000)
                while(sTimer.check() > 0):
                    ret = self.shakeHands(sdmEnable)
                    if (ret == 0):
                        break

        if(ret == 0):
            if(sdmEnable == SDMEnabled):
                ret = sdmclient('push %s %s' %(localpath, fileName))
            else:
                ret = fastboot('fileSystem push %s e:\%s' %(localpath, fileName))
        return ret

    def downloadMainApp(self, fileName):
        self.displayTitle('download main app, plz waiting...')
        if (os.path.isfile(fileName) == False):
            return -1

        ret = self.shakeHands(SDMEnabled)
        if(ret == 0):
            ret = sdmclient('stop')
        if(ret != 0):
            ret = self.shakeHands(SDMDisabled)
        if(ret == 0):
            ret = fastboot('DontAutoRun')

        ret = self.reboot()
        if(ret == 0):
            ret = fastboot('flash app %s' %(fileName))
        if(ret == 99):
            ret = self.runApp()
        return ret

    def downloadApp(self, sdmEnable, appFilePath, updFilePath):
        self.displayTitle('download app, plz waiting...')
        if (os.path.isfile(appFilePath) == False):
            return -1
        if (os.path.isfile(updFilePath) == False):
            return -1
        ret = self.shakeHands(sdmEnable)
        if (ret != 0):
            ret = self.reboot()
            if (ret == 0):
                ret = fastboot('DontAutoRun')
            if (ret == 0):
                ret = self.runApp()
            if (ret == 0):
                sTimer = timer(5*1000)
                while(sTimer.check() > 0):
                    ret = self.shakeHands(sdmEnable)
                    if (ret == 0):
                        break
        if (ret != 0 and sdmEnable == SDMEnabled):
            self.displayTitle('err: incorrect main app')
        if (ret == 0):
            ret = self.pushFile(sdmEnable, appFilePath, 'secapp.img')
        if (ret == 0):
            ret = self.pushFile(sdmEnable, updFilePath, 'upd.tmp')
        if (ret == 0):
            self.setAutoRun()
        return ret

    def formatFilesSystem(self, sdmEnable):
        self.displayTitle('Initializes the file system...')
        bDontAutoRun = 0
        ret = self.shakeHands(sdmEnable)
        if (ret != 0):
            ret = self.reboot()
            if (ret == 0):
                bDontAutoRun = 1
                ret = fastboot('DontAutoRun')
            if (ret == 0):
                ret = self.runApp()
            if (ret == 0):
                sTimer = timer(5*1000)
                while(sTimer.check() > 0):
                    ret = self.shakeHands(sdmEnable)
                    if (ret == 0):
                        break

        if(ret == 0 and sdmEnable == SDMEnabled):
            ret = sdmclient('fsformat')
        if(ret == 0 and sdmEnable == SDMDisabled):
            ret = fastboot('fileSystem init 0 4M')
        if(ret == 0 and sdmEnable == SDMDisabled):
            ret = fastboot('fileSystem format 123456')
        if (ret == 0 and bDontAutoRun == 1):
            self.setAutoRun()
        return ret

