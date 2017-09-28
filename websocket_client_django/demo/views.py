# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render
from dwebsocket import require_websocket
from dwebsocket.decorators import accept_websocket
from django.shortcuts import render_to_response
from django.template import RequestContext
from django.http import HttpResponse


def index(request):
    return render(request, 'index.html')

@require_websocket
def echo_once(request):
    message = request.websocket.wait()
    print message
    request.websocket.send(message)


@accept_websocket
def echo(request):
    # if not request.is_websocket():#判断是不是websocket连接
    #     try:#如果是普通的http方法
    #         message = request.GET['message']
    #         return HttpResponse(message)
    #     except:
    #         return render(request,'index.html')
    # else:
    #     for message in request.websocket:
    #         request.websocket.send(message)#发送消息到客户端
    print "in echo"
    if not request.is_websocket():  # 判断是不是websocket连接
        try:  # 如果是普通的http方法
            message = request.GET['message']
            return HttpResponse(message)
        except:
            return HttpResponse("no websocket!")
    else:
        for message in request.websocket:
            message = message.decode('utf-8')
            print message
            if message !="":
                request.websocket.send(message)  # 发送消息到客户端
            else:
                request.websocket.send('小样儿，没权限!!!'.encode('utf-8'))