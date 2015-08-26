
#coding=utf-8
# -*- coding: utf-8 -*-

import tconfig
import py4cpp
import SocketServer
from SocketServer import StreamRequestHandler as SRH
from time import ctime

tcfg = tconfig.Tconfig()
print tcfg.addr
print tcfg.ptcl
print tcfg.bfsz

class Servers(SRH):
    def handle(self):
        print 'got connection from ',self.client_address
        #self.wfile.write('connection %s:%s at %s succeed!' % (host,port,ctime()))
        while True:
            data = self.request.recv(tcfg.bfsz)
            if not data: 
                break
            
            print data, "RECV from ", self.client_address[0]
            if data != tcfg.ptcl:
                self.request.send('{"rest":0,"mail":"error","link":"error"}')
                break
            
            registInfo = py4cpp.regist_nutaku()
            if registInfo[0] == '':
                self.request.send('{"rest":0,"mail":"error","link":"error"}')
                break

            strRest = ''.join(['{"rest":1,"mail":"',registInfo[0],'","link":"',registInfo[1],'"}'])
            self.request.send(strRest)

print 'server is running....'
server = SocketServer.ThreadingTCPServer(tcfg.addr,Servers)
server.serve_forever()