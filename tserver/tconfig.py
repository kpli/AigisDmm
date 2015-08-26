
#coding=utf-8
# -*- coding: utf-8 -*-

import json

class Tconfig:

    def __init__(self):
        self._readCfg()

    def _readCfg(self):
        fp = open('tconfig.json', 'r')
        dict = json.loads(fp.read())
        fp.close()
        self.host = dict['host']
        self.port = dict['port']
        self.ptcl = dict['ptcl']
        self.bfsz = dict['bfsz']
        self.addr = (self.host, self.port)
