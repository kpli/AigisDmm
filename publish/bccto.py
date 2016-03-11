
#coding=utf-8
# -*- coding: utf-8 -*-

import webnet 
import urllib
import json
import time
import re

class Bccto:

    # 初始化
    def __init__(self):
        self.net = webnet.Webnet(False)
        self.mailUser = ''
        self.mailAddr = ''
        self.mailFlag = ''

    # 获取邮件地址
    def _getMailAddr(self):
        return self.mailAddr

    # 获取密码
    def _getMailPwd(self):
        return self.mailuser

    # 请求cookie
    def _applyMail(self, mailAddr, username):
        # 请求主页记录cookie
        self.net.send_get_noread('http://www.bccto.me')
        # 构建邮件地址
        self.mailuser = username
        self.mailAddr = mailAddr
        # 构建请求
        applymailData = (('mail', self.mailAddr),)
        print urllib.urlencode(applymailData)
        result = self.net.send_post('http://www.bccto.me/applymail', urllib.urlencode(applymailData))
        print result
        resultInfo = json.loads(result)
        if resultInfo['success'] != 'true':
            print '_applyMail failed'
            return False
        return True


    def _waitMail(self):
        bLoopCounter = 0
        while bLoopCounter < 10: 
            time.sleep(1)
            bLoopCounter = bLoopCounter+1
            # 构建请求
            getmailData = (('mail', self.mailAddr)
                            ,('time', '0')
                            ,('_', '0'))
            print urllib.urlencode(getmailData)
            newMail = self.net.send_post('http://www.bccto.me/getmail',urllib.urlencode(getmailData))
            if newMail == 'NO NEW MAIL':
                print newMail
            elif newMail:
                # 解析json
                mailInfo = json.loads(newMail)
                if not mailInfo['mail']:
                    print "waiting mail ... no mail "
                elif len(mailInfo['mail']) == 0:
                    print "waiting mail ... mail empty"
                else:
                    mailFrom = mailInfo['mail'][0][1]
                    print mailFrom
                    if mailFrom=='info@mail.dmm.com':
                        self.mailFlag = mailInfo['mail'][0][4]
                        print self.mailFlag
                        bLoopCounter = 999

    def _viewMail(self):
        print '_viewMail'
        if self.mailFlag == '':
            print 'self.mailFlag empty'
            return ''
        viewmailData = (('mail', self.mailFlag)
                        ,('to', self.mailAddr)
                        ,('_', '0'))
        print urllib.urlencode(viewmailData)
        mailContent = self.net.send_post('http://www.bccto.me/viewmail',urllib.urlencode(viewmailData))
        mailInfo = json.loads(mailContent)
        mailText = mailInfo['mail']
        p = re.compile(r'https://www.dmm.co.jp/my/-/register/complete/.*')
        search_ret = p.findall(mailText)
        if search_ret:
            validUrl = search_ret[0]
            self.net._saveFile('validUrl.txt',validUrl)
            return validUrl
        return ''



