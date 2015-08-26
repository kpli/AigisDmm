
#coding=utf-8
# -*- coding: utf-8 -*-

import bccto 
import dmmjp
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
        #self.mailUser = 'fuckjjan'
        self.mailAddr  = ''.join([self.mailUser , '@', "bccto.me"])
        
        # 申请邮箱
        mail_bccto = bccto.Bccto()
        mail_bccto._applyMail(self.mailAddr, self.mailUser)
        
        # 注册账号
        mail_dmmjp = dmmjp.Dmmjp()
        mail_dmmjp._regist(self.mailAddr,self.mailUser)
        
        # 等待邮件
        mail_bccto._waitMail()
        validAccountUrl = mail_bccto._viewMail()
        
        # 验证
        mail_dmmjp._validMail(validAccountUrl)
        return
        
        # 登陆
        mail_dmmjp._login(self.mailAddr,self.mailUser)
        
        # 设置年龄
        mail_dmmjp._setAge()
        
        # 注册aigis游戏，得到有效游戏链接
        validUrl = mail_dmmjp._regGame()
        if validUrl:
            self.gameUrl = validUrl.replace('&amp;','&')
        
