
#coding=utf-8
# -*- coding: utf-8 -*-

import bccto 
import dmmjp
import dmmjp_l
import random
import string
import time

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

    def _autoLogin(self, mail, pswd):
        obj_dmm = dmmjp_l.Dmmjp_Login()
        game_url = obj_dmm._login(mail,pswd)
        if game_url == '':
            return ('empty','')
        return (mail,game_url);
        

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
        confirmret = mail_dmmjp._validMail(validAccountUrl)
        if confirmret == '':
            return
        
        # 确认姓名和年龄
        time.sleep(1)
        pageRet = mail_dmmjp._confirmAge(confirmret)
        if pageRet == '':
            return
        
        # 提交姓名和年龄
        time.sleep(1)
        pageRet = mail_dmmjp._commitAge(pageRet)
        if pageRet == '':
            return
        
        pageRet = mail_dmmjp._intoGame();
        if pageRet == '':
            return

        # 返回登陆链接
        self.gameUrl = mail_dmmjp._parseURL(pageRet)

        return



