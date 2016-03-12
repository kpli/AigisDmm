
#coding=utf-8
# -*- coding: utf-8 -*-

import logic

def regist_dmmjp():
    print 'regist_dmmjp.......................................'
    lg = logic.Logic()
    lg._autoRun()
    gameURL = lg._getGame()
    
    final_mail = 'empty'
    if not (gameURL == ''):
        final_mail = lg._getMail()
    return final_mail
