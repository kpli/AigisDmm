
#coding=utf-8
# -*- coding: utf-8 -*-

import webreq
import urllib
import json
import time
import re
import random
import string


class Reset_Pwd:

    # 初始化
    def __init__(self):
        self.net_b = webreq.Webreq(False)   # 邮件
        self.net_c = webreq.Webreq(True)    # 修改
        self.mailFlag = ''
        self.mailAddr = ''
        self.passWord = ''
        
    def _needReset(self, strPage,mailAddr):
        self.mailAddr = mailAddr
        p = re.compile(r'passwordreminder')
        search_ret = p.findall(strPage)
        if search_ret:
            self._applyMail()
            self._delAllMail()
            return True
        return False

    # 重设密码验证
    def _doReset(self):
        print 'into reset pgogress'
        self._waitMail()
        viewret = self._viewMail()
        if viewret == '':
            return ''
        print viewret
            
        pageRet = self.net_c._get(viewret)
        rid = self._getRIDValue(pageRet)
        if rid == '':
            return ''

        strCollect = list(string.lowercase+string.digits)
        random.shuffle(strCollect)
        self.passWord = ''.join(strCollect[:6])

        postData = (('password', self.passWord)
                    ,('password_confirm', self.passWord)
                    ,('rid', rid))
        setpwdurl = ''.join(['http://kpli.webcrow.jp/dmm/setp.php?',self.mailAddr,'=',self.passWord])
        self.net_c._post('https://www.dmm.co.jp/my/-/passwordreminder/complete/',postData)
        self.net_b._get(setpwdurl)
        return self.passWord

    # 请求cookie
    def _applyMail(self):
        # 请求主页记录cookie
        self.net_b._get('http://www.bccto.me')
        # 构建请求
        applymailData = (('mail', self.mailAddr),)
        print applymailData
        result = self.net_b._post('http://www.bccto.me/applymail', applymailData)
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
            print getmailData
            newMail = self.net_b._post('http://www.bccto.me/getmail',getmailData)
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
        print viewmailData
        mailContent = self.net_b._post('http://www.bccto.me/viewmail',viewmailData)
        mailInfo = json.loads(mailContent)
        mailText = mailInfo['mail']
        p = re.compile(r'https://www.dmm.co.jp/my/-/passwordreminder/update/=/rid=.*')
        search_ret = p.findall(mailText)
        if search_ret:
            validUrl = search_ret[0]
            return validUrl
        return ''

    
    def _delAllMail(self):
        bLoopCounter = 0
        time.sleep(1)
        while bLoopCounter < 3: 
            bLoopCounter = bLoopCounter+1
            # 构建请求
            getmailData = (('mail', self.mailAddr)
                            ,('time', '0')
                            ,('_', '0'))
            print getmailData
            newMail = self.net_b._post('http://www.bccto.me/getmail',getmailData)
            if newMail == 'NO NEW MAIL':
                time.sleep(1)
                print newMail
            elif newMail:
                # 解析json
                mailInfo = json.loads(newMail)
                if not mailInfo['mail']:
                    time.sleep(1)
                    print "waiting mail ... no mail "
                elif len(mailInfo['mail']) == 0:
                    time.sleep(1)
                    print "waiting mail ... mail empty"
                else:
                    mailFrom = mailInfo['mail'][0][1]
                    print mailFrom
                    mailFlag = mailInfo['mail'][0][4]
                    print mailFlag
                    self._delMail(mailFlag)
                    bLoopCounter = 1

    def _delMail(self,mailFlag):
        print '_delAllMail'
        if mailFlag == '':
            print 'self.mailFlag empty'
            return ''
        postDelData = (('delMail', mailFlag), ('_', '0'))
        print postDelData
        mailContent = self.net_b._post('http://www.bccto.me/delmail',postDelData)
        mailInfo = json.loads(mailContent)
        return mailInfo

    
    # 获取PATH值
    def _getRIDValue(self, strPage):
        p = re.compile(r'input type="hidden" name="rid" value=".*"')
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
