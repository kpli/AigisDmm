
#coding=utf-8
# -*- coding: utf-8 -*-

import webnet 
import json
import re
import sys

class Nutaku:

    # 初始化
    def __init__(self):
        self.net = webnet.Webnet()
        self.mailAddr = ''
        self.mailUser = ''

    # 注册账号
    def _regist(self, mailAddr, namepwd):
        pageres = self.net.send_get('https://www.nutaku.net/signup/')
        pageCode = self._getPageCode(pageres)
        if pageCode:
            postData = ''.join(['agreeTerms=&agreeTerms=1&mailAddress=', mailAddr, '&newsletter=0&newsletter=1&nickname=', namepwd, '&page=',pageCode,'&password=', namepwd])
            resContent = self.net.send_post('https://www.nutaku.net/signup/activation/', postData)
    
    # 验证邮箱
    def _validMail(self,valUrl):
        self.net.send_get(valUrl)

    # 登陆
    def _login(self, mailAddr, namepwd):
        self.mailAddr = mailAddr
        self.mailUser = namepwd
        pageres = self.net.send_get('https://www.nutaku.net/login/')
        pageCode = self._getPageCode(pageres)
        if pageCode:
            postData = ''.join(['autoLogin=0&mailAddress=', mailAddr, '&page=', pageCode, '&password=', namepwd, '&url='])
            self.net.send_post('https://www.nutaku.net/login/failed/', postData)
            resContent = self.net.send_get('http://www.nutaku.net/home/')


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

    # 获取页面编码
    def _getToken(self, strPageText):
        p = re.compile(r'type="hidden" name="token" value=.* id="token"')
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


