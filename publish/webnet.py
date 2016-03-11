
#coding=utf-8
# -*- coding: utf-8 -*-

import zlib
import urllib  
import urllib2
import cookielib
import string

class Webnet:
    
    # 初始化
    def __init__(self, bUseProxy):
        self.proxy = urllib2.ProxyHandler({'http':'127.0.0.1:8088','https':'127.0.0.1:8088'})
        self.cookie_jar = urllib2.HTTPCookieProcessor(cookielib.CookieJar())
        if bUseProxy:
            self.opener = urllib2.build_opener(self.cookie_jar,self.proxy)
        else:
            self.opener = urllib2.build_opener(self.cookie_jar)
        self.headers = {'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0',
                        'Accept-Encoding' : 'gzip, deflate'}

    # 发送GET请求
    def send_get(self,get_url,):
        result = ""
        try:
            my_request = urllib2.Request(url = get_url, headers = self.headers)
            response = self.opener.open(my_request, timeout=30)
            print ''.join(['Code:',str(response.getcode()),' Url:',get_url])
            result = self._unlibResponse(response)
        except Exception,e:
            print "Exception : ",e
        return result 

    # 发送GET请求
    def send_get_noread(self,get_url):
        try:
            my_request = urllib2.Request(url = get_url, headers = self.headers)
            response = self.opener.open(my_request, timeout=30)
            print ''.join(['Code:',str(response.getcode()),' Url:',get_url])
        except Exception,e:
            print "Exception : ",e

    # 发送POST请求
    def send_post(self,post_url,post_data):
        result = ""
        try:
            my_request = urllib2.Request(url = post_url,data = post_data, headers = self.headers)
            response = self.opener.open(my_request, timeout=30)
            print ''.join(['Code:',str(response.getcode()),' Url:',post_url])
            result = self._unlibResponse(response)
        except Exception,e:
            print "Exception : ",e
        return result
    
    # 发送POST请求
    def send_post_noread(self,post_url,post_data):
        try:
            my_request = urllib2.Request(url = post_url,data = post_data, headers = self.headers)
            response = self.opener.open(my_request, timeout=30)
            print ''.join(['Code:',str(response.getcode()),' Url:',post_url])
        except Exception,e:
            print "Exception : ",e

    # 模拟电脑
    def set_computer(self):
        user_agent = 'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:28.0) Gecko/20100101 Firefox/28.0'
        self.headers = { 'User-Agent' : user_agent }    
        
    # 模拟手机
    def set_mobile(self):
        user_agent = 'Mozilla/5.0 (iPhone; CPU iPhone OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/6.0 Mobile/10A403 Safari/8536.25'
        self.headers = { 'User-Agent' : user_agent }    

    # 保存文件
    def _saveFile(self,file,content):
        file_object = open(file, 'w')
        file_object.write(content)
        file_object.close( )

    def _unlibResponse(self, response):
        content = response.read()
        gzipped = response.headers.get('Content-Encoding')
        if gzipped:
            result = zlib.decompress(content, 16+zlib.MAX_WBITS)
            return result
        return content

