# -*- coding: cp936 -*-
import sys,os
import shutil,subprocess

# cmd type
CMD_fastboot    = 0
CMD_sdmclient   = 1
CMD_7z          = 2

class cmdtools:
    def __init__(self, cmdType, cmd):
        if (cmdType == CMD_7z):
            self.ret = self.zip7z(cmd)
        elif (cmdType == CMD_fastboot):
            self.ret = self.fastboot(cmd)
        else:
            self.ret = self.sdmclient(cmd)

    def getRet(self):
        return self.ret

    def execEx(self, operation, cmd):
        try:
            subprocess.check_output('%s %s' %(operation,cmd))
            print('> %s %s' %(operation, cmd))
            return 0
        except:
            #print('>>%s %s' %(operation, cmd))
            return -1

    def fastboot(self, cmd):
        return self.execEx('sbin/fastboot.exe', cmd)

    def sdmclient(self, cmd):
        return self.execEx('sbin/sdmclient.exe', cmd)

    def zip7z(self, cmd):
        return self.execEx('sbin/7zip/7z.exe', cmd)

#fastboot
def fastboot(cmd):
    return cmdtools(CMD_fastboot, cmd).getRet()

#sdmclient
def sdmclient(cmd):
    return cmdtools(CMD_sdmclient, cmd).getRet()

#7-zip
def zip7z(cmd):
    return cmdtools(CMD_7z, cmd).getRet()

