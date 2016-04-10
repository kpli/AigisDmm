
#coding=utf-8
# -*- coding: utf-8 -*-

import webreq
import time

def _auto():
    net = webreq.Webreq(False)
    counter = 0
    while True:
        time.sleep(1)
        counter+=1
        print counter
        net._get('http://kpli.webcrow.jp/dmm/ido.php?cmd=play&key=cancel&val=auto')
        cookie = net._getCookies()
        print cookie['aigis_title']
        if cookie['aigis_title'] == 'noid':
            net._get('http://kpli.webcrow.jp/dmm/ido.php?cmd=unlockall')

_auto()