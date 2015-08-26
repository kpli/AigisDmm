
#coding=utf-8
# -*- coding: utf-8 -*-

import webnet 
import json
import re
import sys

class Dmmjp:

    # 初始化
    def __init__(self):
        self.net = webnet.Webnet()
        self.mailAddr = ''
        self.mailUser = ''

    # 注册账号
    def _regist(self, mailAddr, namepwd):
        self.net.send_get_noread('https://www.dmm.co.jp/my/-/register/')
        postData = ''.join(['back_url=&client_id=&display=&email=', mailAddr, '&opt_mail_cd=adult&password=', namepwd, '&ref=&submit=認証メールを送信','','&token='])
        self.net.send_post_noread('https://www.dmm.co.jp/my/-/register/apply/', postData)
    
    # 验证邮箱
    def _validMail(self,valUrl):
        validResult = self.net.send_get(valUrl)
        jumpUrl = self._getJumpUrl(validResult)
        if jumpUrl:
            self.net.send_get_jump(jumpUrl)
            self.net.send_get_noread('http://www.dmm.co.jp/top/')
            self.net.send_get('http://www.dmm.co.jp/netgame_s/aigis/')
            self.net.send_get_jump('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=on/myapp=on/act=install/')
            #print jumpAigis
            #self.net._saveFile('jumpAigis.html',jumpAigis)
            
        

    # 登陆
    def _login(self, mailAddr, namepwd):
        self.mailAddr = mailAddr
        self.mailUser = namepwd
        pageres = self.net.send_get('https://www.dmm.co.jp/my/-/login/')
        tokenCode = self._getToken(pageres)
        if tokenCode:
            postData = ''.join(['token=',tokenCode,
                                '&login_id=',mailAddr,
                                '&save_login_id=0&password=',namepwd,
                                '&save_password=0&use_auto_login=0&','b7ee627973d48d92b837e5f9dd15da9e','=',mailAddr,
                                '&','e2b4c75aaceb8ca60b598ea687bacb31','=',namepwd,
                                '&path=&prompt=&client_id=&display='])
            loginRes = self.net.send_post('https://www.dmm.co.jp/my/-/login/auth/', postData)
            self.net._saveFile('loginRes.html',loginRes)
            resAigis = self.net.send_get('https://www.dmm.co.jp/netgame_s/aigis')
            self.net._saveFile('resAigis.html',resAigis)


    # 设置年龄
    def _setAge(self):
        resContent = self.net.send_get('https://www.nutaku.net/members/profile/username/reset/')
        pageCode = self._getPageCode(resContent)
        if pageCode:
            postData = ''.join(['about=&birth=&birthDay=7&birthdaydisplay=0&birthMonth=7&birthYear=1997&country=0&gender=male&genderdisplay=0&hobbies=&nickname=', self.mailUser, '&occupation=0&page=', pageCode])
            resConfirm = self.net.send_post('https://www.nutaku.net/members/profile/username/reset/confirm/', postData)
            pageCodeConfirm = self._getPageCode(resConfirm)
            if pageCodeConfirm:
                postDataConfirm = ''.join(['about=&birth=&birthDay=7&birthdaydisplay=0&birthMonth=7&birthYear=1997&country=0&gender=male&genderdisplay=0&hobbies=&nickname=', self.mailUser, '&occupation=0&page=', pageCodeConfirm])
                resConfirm = self.net.send_post('https://www.nutaku.net/members/profile/username/reset/complete/', postDataConfirm)

    # 提取游戏链接
    def _regGame(self):
        resContent = self.net.send_get('http://www.nutaku.net/games/millennium-war-aigis/')
        formToken = self._getToken(resContent)
        if formToken:
            registUrl = ''.join(['http://www.nutaku.net/games/millennium-war-aigis/register/?notification=1&token=', formToken, '&invite_id=&appParams='])
            self.net.send_get(registUrl)
            playUrl = ''.join(['http://www.nutaku.net/games/millennium-war-aigis/play/?notification=1&token=', formToken, '&invite_id=&appParams='])
            resContent = self.net.send_get(playUrl)
            validGameUrl = self._parseURL(resContent)
            return validGameUrl

    # 提取游戏链接
    def _parseURL(self,strPageText):
        p = re.compile(r'iframe src=.* width="970" style="height: 1200px;" id="game_frame"  name="game_frame"')
        search_ret = p.findall(strPageText)
        if search_ret:
            validUrl = search_ret[0]
            
            p2 = re.compile(r'src=.* width')
            search_ret2 = p2.findall(validUrl)
            validUrl2 = search_ret2[0]
            
            p3 = re.compile(r'\".*\"')
            search_ret3 = p3.findall(validUrl2)
            validUrl3 = search_ret3[0]
            validUrl3 = validUrl3.strip('"')
            
            return validUrl3

    # 获取页面编码
    def _getPageCode(self, strPageText):
        p = re.compile(r'type="hidden" name="page" value=.* dispName="none" id="page"')
        search_ret = p.findall(strPageText)
        if search_ret:
            pageCode = search_ret[0]
            
            p2 = re.compile(r'value=.* dispName')
            search_ret2 = p2.findall(pageCode)
            pageCode2 = search_ret2[0]
            
            p3 = re.compile(r'\".*\"')
            search_ret3 = p3.findall(pageCode2)
            pageCode3 = search_ret3[0]
            pageCode3 = pageCode3.strip('"')
            
            return pageCode3

    # 获取TOKEN编码
    def _getToken(self, strPageText):
        p = re.compile(r'type="hidden" name="token" value=.* id="id_token"')
        search_ret = p.findall(strPageText)
        if search_ret:
            formToken = search_ret[0]
            
            p2 = re.compile(r'value=.* id')
            search_ret2 = p2.findall(formToken)
            formToken2 = search_ret2[0]
            
            p3 = re.compile(r'\".*\"')
            search_ret3 = p3.findall(formToken2)
            formToken3 = search_ret3[0]
            formToken3 = formToken3.strip('"')
            return formToken3

    # 获取账号验证跳转链接
    def _getJumpUrl(self, strPageText):
        p = re.compile(r'a href=.* class="d-btn-xhi-st"')
        search_ret = p.findall(strPageText)
        if search_ret:
            jumpUrl = search_ret[0]
            
            p2 = re.compile(r'href=.* class')
            search_ret2 = p2.findall(jumpUrl)
            jumpUrl2 = search_ret2[0]
            
            p3 = re.compile(r'\".*\"')
            search_ret3 = p3.findall(jumpUrl2)
            jumpUrl3 = search_ret3[0]
            jumpUrl3 = jumpUrl3.strip('"')
            
            return jumpUrl3
