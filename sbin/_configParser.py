# -*- coding: cp936 -*-
import sys,os
import ConfigParser

class config:
    def __init__(self, fileName):
        self.cfg = ConfigParser.ConfigParser()
        self.cfg.read(fileName)

    def getValue(self, root, key):
        return self.cfg.get(root, key)
