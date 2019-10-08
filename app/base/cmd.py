# -*- coding: cp936 -*-
import sys,os

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

if __name__ == "__main__":
    appPath = os.path.split(os.getcwd())[1]

    if len(sys.argv) < 2:
        ErrMsg(None)
    elif sys.argv[1] in ["-c"]:
        os.chdir('../../')
        os.system("python configure.py -clean %s" %(appPath))
    elif sys.argv[1] in ["-b"]:
        os.chdir('../../')
        os.system("python configure.py -build %s" %(appPath))
    elif sys.argv[1] in ["-d"]:
        os.chdir('../../')
        os.system("python configure.py -down %s" %(appPath))
    elif sys.argv[1] in ["-t"]:
        os.chdir('../../')
        os.system("python configure.py -tools %s" %(appPath))
    else:
        ErrMsg(None)

