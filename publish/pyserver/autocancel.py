
#coding=utf-8
# -*- coding: utf-8 -*-

import webreq
import time

def _auto():
    net = webreq.Webreq(False)
    addr = 'http://kpli.webcrow.jp/dmm/ido.php?cmd=play&key=cancel&val=auto'
    counter = 0
    while True:
        time.sleep(1)
        counter+=1
        print counter
        net._get(addr)

_auto()