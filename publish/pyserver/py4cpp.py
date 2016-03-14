
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
    return contrustHTML(final_mail,gameURL)


def contrustHTML(mail,gamelink):
    html = ''.join(['<html><title>',mail,'</title><body><iframe src="',gamelink,'" width="960" height="640" pixelTop="200" scrolling="no" frameborder="0" border="0" style="position:absolute;left:0;top:0px;" /> </body></html>'])
    return html
