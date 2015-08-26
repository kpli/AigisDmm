
#coding=utf-8
# -*- coding: utf-8 -*-

import logic 

def regist_dmmjp():
    
    lg = logic.Logic()
    lg._autoRun()
    
    mail = lg._getMail()
    url = lg._getGame()
    
    #print mail
    #print url
    
    if url:
        return (mail,url)
    
    return ('','')

    
st = regist_dmmjp()
print st

#import webnet 
#net = webnet.Webnet()
#net.send_get_jump('https://www.baidu.com/')

