
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
        self.net = webnet.Webnet()
        self.mailAddr = ''
        self.mailUser = ''

    # 注册账号
    def _regist(self, mailAddr, namepwd):
        self.mailAddr = mailAddr
        self.mailUser = namepwd
        self.net.send_get('https://www.dmm.co.jp/my/-/register/')
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

#
#
#from splinter import Browser
#import time
#
#class Dmmjp:
#
#    # 初始化
#    def __init__(self):
#        pass
#
#    # 注册账号
#    def _regist(self, mailAddr, namepwd):
#        with Browser('chrome') as browser:
#            browser.visit('https://www.dmm.co.jp/my/-/register/')
#            
#            browser.fill('email',mailAddr)
#            browser.fill('password',namepwd)
#            
#            button = browser.find_by_name('submit')
#            button.click()
#            
#            time.sleep(5)
#
#