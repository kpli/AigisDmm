
#coding=utf-8
# -*- coding: utf-8 -*-

import logic 

def regist_nutaku():
    
    lg = logic.Logic()
    lg._autoRun()
    
    mail = lg._getMail()
    url = lg._getGame()
    
    #print mail
    #print url
    
    if url:
        return (mail,url)
    
    return ('','')
