import socket
import threading
import os

def str2shell(str):
    if(str=='map_start'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/map_start.sh')
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_base.sh')
    if (str == 'map_finish'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/map_finish.sh')
    if (str == 'move_up'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_up.sh')
    if (str == 'move_down'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_down.sh')
    if (str == 'move_left'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_left.sh')
    if (str == 'move_right'):
        os.system(r'sh ~/catkin_ws/src/team_108/bash/move_right.sh')

def tcplink():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    s.bind(('192.168.43.6', 9999))
    s.listen(1)
    while True:
        print('waiting for connection.....')
        sock, addr = s.accept()
        print('Accept new connection from %s:%s...' % addr)
        try:
            data = sock.recv(1024)
            rcvStr=data.decode('utf-8')
            str2shell(rcvStr)
            sendStr = 'received: ' + rcvStr + '\r\n'
            sock.send(sendStr.encode('utf-8'))
            print(sendStr.replace('\r\n',''))
            sock.close()
        except ConnectionAbortedError as e:
            print('Connection Aborted!')
        finally:
            print('Connection from %s:%s closed.' % addr)



t = threading.Thread(target=tcplink)
t.start()

