import socket
import threading
import os
import base64


def reverseIns(action_list):
    while len(action_list) > 0:
        list_pop = action_list.pop()
        if list_pop == 1:
            os.system(r'sh ~/catkin_ws/src/team_108/bash/move_down.sh')
            continue
        if list_pop == 2:
            os.system(r'sh ~/catkin_ws/src/team_108/bash/move_up.sh')
            continue
        if list_pop == 3:
            os.system(r'sh ~/catkin_ws/src/team_108/bash/move_right.sh')
            continue
        if list_pop == 4:
            os.system(r'sh ~/catkin_ws/src/team_108/bash/move_left.sh')
            continue

def str2shell(str):
    action_list = []
    if (str == 'map_start'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/map_start.sh')
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_base.sh')
    if (str == 'map_finish'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/map_finish.sh')
        reverseIns(action_list)
    if (str == 'move_up'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_up.sh')
        action_list.append(1)
    if (str == 'move_down'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_down.sh')
        action_list.append(2)
    if (str == 'move_left'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_left.sh')
        action_list.append(3)
    if (str == 'move_right'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_right.sh')
        action_list.append(4)

def sendImg(sock):
    path = r'C:\Users\94808\Desktop\jqb.jpg'
    img = open(path, 'rb')
    while 1:
        data = img.read(1024)
        if not data:
            print(path+' send over')
            break
        sock.send(data)


def tcplink():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    s.bind(('192.168.43.6', 9999))
    s.listen(1)
    while True:
        #print('waiting for connection.....')
        sock, addr = s.accept()
        #print('Accept new connection from %s:%s...' % addr)
        try:
            data = sock.recv(1024)
            rcvStr = data.decode('utf-8')
            sendStr = 'received: ' + rcvStr + '\r\n'
            sock.send(sendStr.encode('utf-8'))
            #str2shell(rcvStr)
            print(sendStr.replace('\r\n', ''))
            if rcvStr=='img':
                sendImg(sock)
            sock.close()
        except ConnectionAbortedError as e:
            print('Connection Aborted!')
        finally:
            print('Connection from %s:%s closed.' % addr)


t = threading.Thread(target=tcplink)
t.start()


