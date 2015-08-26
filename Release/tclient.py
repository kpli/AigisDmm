
#coding=utf-8
# -*- coding: utf-8 -*-

import tconfig
import json
from socket import * 

def request_info():

    tcfg = tconfig.Tconfig()
    
    client = socket(AF_INET,SOCK_STREAM)
    client.connect(tcfg.addr)
    client.send(tcfg.ptcl)
    data = client.recv(tcfg.bfsz)
    client.close()
    
    if data:
        info = json.loads(data)
        if info['rest'] == 1:
            return (info['mail'],info['link'])
    
    return ('','')

