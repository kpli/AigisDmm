
#coding=utf-8
# -*- coding: utf-8 -*-

import zlib
import cookielib
import string
import requests

class Webreq:
    
    # 初始化
    def __init__(self, bUseProxy):
        requests.packages.urllib3.disable_warnings()
        self.session = requests.session()
        self.bUseProxy = bUseProxy
        self.cookies = cookielib.CookieJar()
        self.proxies = {'http':'127.0.0.1:8088','https':'127.0.0.1:8088'}
        self.headers = {'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0',
                        'Accept-Encoding' : 'gzip, deflate'}

    # 发送GET请求
    def _get(self,get_url):
        response = requests.Response()
        try:
            if self.bUseProxy:
                response = self.session.get(url = get_url,headers =self.headers,cookies = self.cookies,proxies = self.proxies,verify = False)
            else:
                response = self.session.get(url = get_url,headers =self.headers,cookies = self.cookies)
        except Exception,e:
            print "Exception : ",e
        return response.text 

    # 发送POST请求
    def _post(self,post_url,post_data):
        response = requests.Response()
        try:
            if self.bUseProxy:
                response = self.session.post(url = post_url,headers =self.headers,cookies = self.cookies,data = post_data, proxies = self.proxies,verify = False)
            else:
                response = self.session.post(url = post_url,headers =self.headers,cookies = self.cookies,data = post_data)
        except Exception,e:
            print "Exception : ",e
        return response.text
    
    # 模拟电脑
    def _computer(self):
        user_agent = 'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:28.0) Gecko/20100101 Firefox/28.0'
        self.headers = { 'User-Agent' : user_agent }    
        
    # 模拟手机
    def _mobile(self):
        user_agent = 'Mozilla/5.0 (iPhone; CPU iPhone OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/6.0 Mobile/10A403 Safari/8536.25'
        self.headers = { 'User-Agent' : user_agent }    

    def _unlibResponse(self, response):
        content = response.read()
        gzipped = response.headers.get('Content-Encoding')
        if gzipped:
            result = zlib.decompress(content, 16+zlib.MAX_WBITS)
            return result
        return content
