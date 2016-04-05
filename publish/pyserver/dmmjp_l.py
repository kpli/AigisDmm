
#coding=utf-8
# -*- coding: utf-8 -*-

import resetpwd  
import webreq  
import urllib
import json
import re
import sys
import time

class Dmmjp_Login:

    # 初始化
    def __init__(self):
        self.net = webreq.Webreq(True)
        self.pwd = resetpwd.Reset_Pwd()
    
    # 登陆
    def _login(self, mailAddr, namepwd):
        print '_login'

        gameRet = self.net._get('https://www.dmm.co.jp/my/-/login/')
        
        path = self._getPathValue(gameRet);
        print 'path:', path;
        
        xhrTokenHeader = self._getTagToken('"DMM_TOKEN", ',gameRet);
        if xhrTokenHeader=='':
            return ''
        xhrTokenContent = self._getTagToken('"token": ',gameRet);
        if xhrTokenContent == '':
            return ''
        postData = (('token',xhrTokenContent),)
        xhrReturn = self.net._post_xhr('https://www.dmm.co.jp/my/-/login/ajax-get-token/', postData, xhrTokenHeader)
        if xhrReturn == '':
            return ''
        xhr = json.loads(xhrReturn)

        postData = ((xhr['login_id'],mailAddr),
                    ('client_id',''),
                    ('display',''),
                    (xhr['password'],namepwd),
                    ('login_id',mailAddr),
                    ('password',namepwd),
                    ('path', path),
                    ('prompt', ''),
                    ('save_login_id','0'),
                    ('save_password','0'),
                    ('token',xhr['token']),
                    ('use_auto_login','0'))
        loginRet = self.net._post('https://www.dmm.co.jp/my/-/login/auth/', postData)
        if loginRet == '':
            return ''


        if self.pwd._needReset(loginRet,mailAddr):
            ret = self.net._get('https://www.dmm.co.jp/my/-/passwordreminder/')
            postData = (('email', mailAddr),)
            ret = self.net._post('https://www.dmm.co.jp/my/-/passwordreminder/sendmail/', postData)
            namepwd = self.pwd._doReset()
            if namepwd == '':
                return namepwd
            self.net = webreq.Webreq(True)
            return self._login(mailAddr,namepwd);
        
        
        gameRet = self._intoGame()
        if gameRet == '':
            return ''
        gameUrl = self._parseURL(gameRet)

        return gameUrl;

        
#################################################################################################################
    # 进入游戏
    def _intoGame(self):
        gameRet = self.net._get('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install')
        return gameRet

    # 根据tag获取token值
    def _getTagToken(self,strTag, strPage):
        p = re.compile(strTag+r'".*"')
        search_ret = p.findall(strPage)
        if search_ret:
            backurl = search_ret[0]
            
            p2 = re.compile(r' ".*"')
            search_ret2 = p2.findall(backurl)
            backurl2 = search_ret2[0]
            
            p3 = re.compile(r'".*"')
            search_ret3 = p3.findall(backurl2)
            backurl3 = search_ret3[0]
            
            backurl3 = backurl3.strip('"')
            return backurl3
        return ''
    
    # 获取PATH值
    def _getPathValue(self, strPage):
        p = re.compile(r'input type="hidden" name="path" value=".*"')
        search_ret = p.findall(strPage)
        if search_ret:
            backurl = search_ret[0]
            
            p2 = re.compile(r'value=".*"')
            search_ret2 = p2.findall(backurl)
            backurl2 = search_ret2[0]
            
            p3 = re.compile(r'".*"')
            search_ret3 = p3.findall(backurl2)
            backurl3 = search_ret3[0]
            
            backurl3 = backurl3.strip('"')
            return backurl3
        return ''

    # 提取游戏链接
    def _parseURL(self,strPageText):
        p = re.compile(r'"http://osapi.dmm.com/gadgets/ifr.*"')
        search_ret = p.findall(strPageText)
        if search_ret:
            validUrl = search_ret[0]
            validUrl = validUrl.strip('"')
            return validUrl
        return ''
