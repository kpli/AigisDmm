
#coding=utf-8
# -*- coding: utf-8 -*-

import time
import re
from splinter import Browser

class DJValid:

    # 初始化
    def __init__(self):
        pass

    # 进入游戏
    def _goIntoGame(self, mailurl):
        with Browser('chrome') as browser:
            self._validAccount(browser, mailurl)
            self._openGame(browser)
            self._confirmAge(browser)
            self._commitAge(browser)
            self._playGame(browser)
            return _parseGameLink()
        return ''

    # 验证邮箱
    def _validAccount(self, browser, mailurl):
        browser.visit(mailurl)
        browser.click_link_by_partial_href('auth')
        time.sleep(5)

    # 打开游戏
    def _openGame(self, browser):
        browser.visit('http://www.dmm.co.jp/netgame_s/aigis/')
        browser.click_link_by_partial_text('Game Start')
        time.sleep(5)

    # 确认年龄
    def _confirmAge(self, browser):
        button = browser.find_by_name('confirm')
        button.click()
        time.sleep(5)
        return ''
    
    # 提交年龄
    def _commitAge(self, browser):
        button = browser.find_by_id('commit_submit')
        button.click()
        time.sleep(5)
        return ''

    # 确认进入玩游戏
    def _playGame(self, browser):
        button = browser.find_by_id('gametop')
        button.click()
        time.sleep(5)
    
    # 获取链接
    def _parseGameLink(self):
        browser.visit('http://www.dmm.co.jp/netgame/social/-/gadgets/=/app_id=156462/')
        time.sleep(500)
        iframe = browser.find_by_name('btnG')
        if iframe:
            return iframe.src
        return ''
