
#coding=utf-8
# -*- coding: utf-8 -*-

import bccto 
import dmmjp
import djvalid
import re
import random
import string

class Logic:

    # 初始化
    def __init__(self):
        self.mailUser = ''
        self.mailAddr = ''
        self.gameUrl = ''

    def _getName(self):
        return self.mailUser

    def _getMail(self):
        return self.mailAddr

    def _getGame(self):
        return self.gameUrl

    def _randName(self):
            strCollect = list(string.lowercase+string.digits)
            random.shuffle(strCollect)
            return ''.join(strCollect[:8])

    def _autoRun(self):
        
        # 随机账号
        self.mailUser = self._randName()
        self.mailAddr  = ''.join([self.mailUser , '@', "bccto.me"])
        
        # 申请邮箱
        mail_bccto = bccto.Bccto()
        ret = mail_bccto._applyMail(self.mailAddr, self.mailUser)
        if not ret:
            return
        
        # 注册账号
        mail_dmmjp = dmmjp.Dmmjp()
        mail_dmmjp._regist(self.mailAddr,self.mailUser)
        
        # 等待邮件
        mail_bccto._waitMail()
        validAccountUrl = mail_bccto._viewMail()
        print(validAccountUrl)
        if validAccountUrl == '':
            return
        
        # 验证
        valid_account = djvalid.DJValid()
        confirmret = valid_account._goIntoGame(validAccountUrl)
        if confirmret == '':
            return
        
        self.gameUrl = confirmret.replace('&amp;','&')




