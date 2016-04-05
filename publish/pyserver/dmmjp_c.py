
#coding=utf-8
# -*- coding: utf-8 -*-

import resetpwd  
import webreq  
import urllib
import json
import re
import sys
import time

class Dmmjp_Cancel:

    # 初始化
    def __init__(self):
        self.net = webreq.Webreq(True)
        self.pwd = resetpwd.Reset_Pwd()
    
    # 登陆
    def _cancel(self, mailAddr, namepwd):
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
            return self._cancel(mailAddr,namepwd);
        
        # 进入设置页面
        gameRet = self.net._get('http://www.dmm.co.jp/my/-/top/')
        if gameRet == '':
            return ''
        
        postData = (('mytop', 'true'),)
        gameRet = self.net._post_xhr('https://www.dmm.co.jp/digital/-/mypage/ajax-index/',postData,'')
        if gameRet == '':
            return ''

        gameRet = self.net._get('https://www.dmm.co.jp/my/-/inactivate/payment/')
        if gameRet == '':
            return ''

        gameRet = self.net._get('https://www.dmm.co.jp/digital/-/inactivate/ajax-index/')
        if gameRet == '':
            return ''


        gameRet = self.net._get('https://www.dmm.co.jp/my/-/inactivate/r18com/')
        if gameRet == '':
            return ''

        gameRet = self.net._get('https://www.dmm.co.jp/my/-/inactivate/reason/')
        if gameRet == '':
            return ''
        
        tokenvalue = self._getTokenValue(gameRet)
        print tokenvalue
        postData = (('token',tokenvalue),('reason', ''))
        gameRet = self.net._post('https://www.dmm.co.jp/my/-/inactivate/complete/', postData)
        if gameRet == '':
            return ''
        return gameRet;

        
#################################################################################################################

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

    
    # 获取token值
    def _getTokenValue(self, strPage):
        p = re.compile(r'input type="hidden" name="token" value=".*" id=')
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


    
#obj_dmm = Dmmjp_Cancel()
#game_url = obj_dmm._cancel('qujm0c21z@bccto.me','pwd123')
