
#coding=utf-8
# -*- coding: utf-8 -*-

import webnet  
import urllib
import json
import re
import sys
import time

class Dmmjp:

    # 初始化
    def __init__(self):
        self.net = webnet.Webnet(True)
        self.mailAddr = ''
        self.mailUser = ''
        self.backURL = ''
        
    # 注册账号
    def _regist(self, mailAddr, namepwd):
        self.mailAddr = mailAddr
        self.mailUser = namepwd
        self.net.send_get_noread('https://www.dmm.co.jp/my/-/register/')
        postData = (('back_url',''),
                    ('client_id',''),
                    ('display',''),
                    ('email', mailAddr),
                    ('opt_mail_cd','adult'),
                    ('password', namepwd),
                    ('ref','',),
                    ('submit','認証メールを送信'),
                    ('token',''))
        print urllib.urlencode(postData)
        self.net.send_post_noread('https://www.dmm.co.jp/my/-/register/apply/', urllib.urlencode(postData))
        
    # 验证邮箱
    def _validMail(self,valUrl):
        validResult = self.net.send_get(valUrl)
        jumpUrl = self._getJumpUrl(validResult)
        print ''.join(['jumpUrl: ',jumpUrl])
        if jumpUrl == '':
            return ''
        self.net.send_get_noread(jumpUrl)
        #self.net.send_get_noread('http://www.dmm.co.jp/top/')
        #self.net.send_get_noread('http://www.dmm.co.jp/netgame_s/aigis/')
        jumpGame = self.net.send_get('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install/')
        return jumpGame

    # 认证年龄
    def _confirmAge(self, comfirmPage):
        print '_confirmAge'
        backurl = self._getBackUrl(comfirmPage)
        print ''.join(['backurl: ',backurl])
        if backurl == '':
            return ''
        postData = (('nickname', self.mailUser),
                    ('gender','male'),
                    ('year','1997'),
                    ('month','01'),
                    ('day','01'),
                    ('confirm','入力内容を確認する'),
                    ('paytype','free'),
                    ('opt_mail_cd','netgame'),
                    ('ch',''),
                    ('back_url', backurl),
                    ('redirect_url',''),
                    ('invite',''))
        print urllib.urlencode(postData)
        confirmReturn = self.net.send_post('http://www.dmm.co.jp/netgame/profile/-/regist/confirm/', urllib.urlencode(postData))
        return confirmReturn

    # 提交年龄确认
    def _commitAge(self, commitPage):
        print '_commitAge'
        backurl = self._getBackUrl(commitPage)
        print ''.join(['backurl: ',backurl])
        if backurl == '':
            return ''
        htoken = self._getToken(commitPage)
        print ''.join(['htoken: ',htoken])
        if htoken == '':
            return ''
        postData = (('act', 'commit'),
                    ('nickname', self.mailUser),
                    ('gender', 'male'),
                    ('year', '1997'),
                    ('month', '01'),
                    ('day', '01'),
                    ('back_url', backurl),
                    ('redirect_url', 'http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install'),
                    ('opt_mail_cd','netgame'),
                    ('invite', ''),
                    ('game_type', ''),
                    ('encode_hint', '◇'),
                    ('token', htoken))
        print urllib.urlencode(postData)
        commitReturn = self.net.send_post('http://www.dmm.co.jp/netgame/profile/-/regist/commit/', urllib.urlencode(postData))
        self.net._saveFile('commitReturn.html',commitReturn)
        return commitReturn

#################################################################################################################

    # 提取游戏链接
    #def _parseURL(self,strPageText):
    #    p = re.compile(r'iframe id="game_frame".*src=".*"')
    #    search_ret = p.findall(strPageText)
    #    if search_ret:
    #        validUrl = search_ret[0]
    #        
    #        p2 = re.compile(r'src=."*"')
    #        search_ret2 = p2.findall(validUrl)
    #        validUrl2 = search_ret2[0]
    #        
    #        p3 = re.compile(r'".*"')
    #        search_ret3 = p3.findall(validUrl2)
    #        validUrl3 = search_ret3[0]
    #        
    #        validUrl3 = validUrl3.strip('"')
    #        return validUrl3
    #    return ''

    # 获取表单默认信息
    def _getBackUrl(self, strPageText):
        p = re.compile(r'type="hidden" name="back_url" value=.*"')
        search_ret = p.findall(strPageText)
        if search_ret:
            backurl = search_ret[0]
            
            p2 = re.compile(r'value=.*"')
            search_ret2 = p2.findall(backurl)
            backurl2 = search_ret2[0]
            
            p3 = re.compile(r'".*"')
            search_ret3 = p3.findall(backurl2)
            backurl3 = search_ret3[0]
            
            backurl3 = backurl3.strip('"')
            return backurl3
        return ''

    # 获取TOKEN编码
    def _getToken(self, strPageText):
        p = re.compile(r'type="hidden" name="token" value=.* id')
        search_ret = p.findall(strPageText)
        if search_ret:
            formToken = search_ret[0]
            
            p2 = re.compile(r'value=.* id')
            search_ret2 = p2.findall(formToken)
            formToken2 = search_ret2[0]
            
            p3 = re.compile(r'".*"')
            search_ret3 = p3.findall(formToken2)
            formToken3 = search_ret3[0]
            
            formToken3 = formToken3.strip('"')
            return formToken3
        return ''


    # 获取账号验证跳转链接
    def _getJumpUrl(self, strPageText):
        p = re.compile(r'a href=.*direct_login=1/">')
        search_ret = p.findall(strPageText)
        if search_ret:
            jumpUrl = search_ret[0]
            
            #p2 = re.compile(r'href=.* class')
            #search_ret2 = p2.findall(jumpUrl)
            #jumpUrl2 = search_ret2[0]
            
            p3 = re.compile(r'".*"')
            search_ret3 = p3.findall(jumpUrl)
            jumpUrl3 = search_ret3[0]
            
            jumpUrl3 = jumpUrl3.strip('"')
            
            return jumpUrl3
        return ''
    