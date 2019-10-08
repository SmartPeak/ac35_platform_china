import os,sys
import re

# Check if a file is GBK code
def isFileGB2312(path):
    line = ""
    linenum = 0
    rawnum = 0
    fd = open(path, 'r')
    
    isHanChar = 0;
    for line in fd:
        linenum = linenum + 1
        rawnum = 0
        isHanChar = 0;
        for c in line:
            rawnum = rawnum + 1
            if ord(c) < 0x80:
                isHanChar = 0; # Not GB2312
            elif isHanChar == 0 and ord(c) >= 0xA1 and ord(c) <= 0xF7:
                isHanChar = 1; # GB2312 Hi
            elif isHanChar == 1 and ord(c) >= 0xA1 and ord(c) <= 0xFE:
                isHanChar = 0; # GB2312 Low
            else:
                print 'Char [%c], line:%d, raw:%d' % (c, linenum, rawnum)
                return (None, line)
    return (True, "GB2312")

def main():
    if len(sys.argv) != 2:
        print "Usage: %s file" % sys.argv[0]
        return -1

    path = sys.argv[1]
    allfilelist = []
    for fpathe,dirs,fs in os.walk(path):  
        for f in fs:  
            #print(os.path.join(fpathe,f))
            allfilelist.append(os.path.join(fpathe,f))
    filterx = re.compile('.*\.[cChH]$')
    for f in allfilelist:
        if filterx.match(f):
            res = isFileGB2312(f)
            if res[0] == None:
                print "%s is not GBK" % f
            else:
                #print "%s is GBK" % f
                pass
        else:
            #print '%s is not Source Code' % f
            pass
    return 0;

if __name__ == "__main__":
    sys.exit(main())

