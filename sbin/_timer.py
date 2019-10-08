# -*- coding: cp936 -*-
import sys,os
import time

class timer:
    def __init__(self, timeout):
        self.timeout = timeout
        self.time_start = time.time()*1000

    def check(self):
        self.time_end = time.time()*1000
        if ((self.time_end - self.time_start) > self.timeout):
            return 0;
        else:
            return self.timeout - (self.time_end - self.time_start)

