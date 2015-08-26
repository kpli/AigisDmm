
#coding=utf-8
# -*- coding: utf-8 -*-

import webnet 
import json
import time
import re

class Bccto:

    # 初始化
    def __init__(self):
        self.net = webnet.Webnet()
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
        self.net.send_get('http://www.bccto.me')
        # 构建邮件地址
        self.mailuser = username
        self.mailAddr = mailAddr
        # 构建请求
        applymailData = ''.join(['mail=',self.mailAddr])
        self.net.send_post('http://www.bccto.me/applymail', applymailData)


    def _waitMail(self):
        bLoopCounter = 0
        while bLoopCounter < 5: 
            time.sleep(5)
            bLoopCounter = bLoopCounter+1
            # 构建请求
            getmailData = ''.join(['mail=',self.mailAddr,"&time=0&_=0"])  
            newMail = self.net.send_post('http://www.bccto.me/getmail',getmailData)
            if newMail == 'NO NEW MAIL':
                print newMail
            elif newMail:
                # 解析json
                mailInfo = json.loads(newMail)
                if len(mailInfo['mail']) == 0:
                    print "waiting for valid mail ... "
                else:
                    mailFrom = mailInfo['mail'][0][0]
                    print mailFrom
                    if mailFrom=='Nutaku Mail':
                        self.mailFlag = mailInfo['mail'][0][4]
                        bLoopCounter = 999

    def _viewMail(self):
        viewmailData = ''.join(['mail=',self.mailFlag,'&to=',self.mailAddr,'&_=0']) 
        mailContent = self.net.send_post('http://www.bccto.me/viewmail',viewmailData)  
        mailInfo = json.loads(mailContent)
        mailText = mailInfo['mail']
        p = re.compile(r'http://www.nutaku.net/signup/activation/complete/id/.*')
        search_ret = p.findall(mailText)
        if search_ret:
            validUrl = search_ret[0]
            return validUrl



