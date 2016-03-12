
#coding=utf-8
# -*- coding: utf-8 -*-

import tconfig
import py4cpp
import io
import shutil
import urlparse
from BaseHTTPServer import HTTPServer
from BaseHTTPServer import BaseHTTPRequestHandler


class MyRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urlparse.urlparse(self.path) 
        if (parsed_path.path == '/regist_aigis_dmm'):
            self.process()
    
    def do_POST(self):
        print 'do_POST pass'
    
    def process(self):
        content = py4cpp.regist_dmmjp()
        enc="UTF-8"
        content=content.encode(enc)
        f=io.BytesIO()
        f.write(content)
        f.seek(0)
        self.send_response(200)
        self.send_header("Content-type","text/html;charset=%s" % enc)
        self.send_header("Content-Length",str(len(content)))
        self.end_headers()
        shutil.copyfileobj(f,self.wfile)

server=HTTPServer(('127.0.0.1',8000),MyRequestHandler)
print'started httpserver...'
server.serve_forever()
