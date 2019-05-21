import socket
import threading
import os
import time
import time


def reverseIns(action_list):
    while len(action_list) > 0:
        list_pop = action_list.pop()
        if list_pop == 1:
            os.system(r'rosrun team_108 go_backward')
            continue
        if list_pop == 2:
            os.system(r'rosrun team_108 go_forward')
            continue
        if list_pop == 3:
            os.system(r'rosrun team_108 go_right')
            continue
        if list_pop == 4:
            os.system(r'rosrun team_108 go_left')
            continue


def str2shell(str):
    action_list = []
    if str == 'map_start':
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_bringup minimal.launch; exec bash\"'")
        time.sleep(2)
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_tutorials hector_mapping.launch; exec bash\"'")
    if str == 'map_finish':
        os.system("gnome-terminal -e 'bash -c \"rosrun map_server map_saver -f map\"'")
        os.system("gnome-terminal -e 'bash -c \"cp ~/map.pgm ~/catkin_ws/src/team_108/maps/\"'")
        os.system("gnome-terminal -e 'bash -c \"cp ~/map.yaml ~/catkin_ws/src/team_108/maps/\"'")
        # reverseIns(action_list)
    if str == 'move_forward':
        os.system("gnome-terminal -e 'bash -c \"rosrun team_108 go_forward\"'")
        action_list.append(1)
    if str == 'move_backward':
        os.system("gnome-terminal -e 'bash -c \"rosrun team_108 go_backward\"'")
        action_list.append(2)
    if str == 'move_left':
        os.system("gnome-terminal -e 'bash -c \"rosrun team_108 go_left\"'")
        action_list.append(3)
    if str == 'move_right':
        os.system("gnome-terminal -e 'bash -c \"rosrun team_108 go_right\"'")
        action_list.append(4)
    if 'addNewWayPoint' in str:
        os.system("gnome-terminal -e 'bash -c \"roslaunch team_108 script_exc.launch\"'")
    if 'goto' in str:
        command = "gnome-terminal -e 'bash -c \"roslaunch team_108 script_goto"+str[4]+".launch\"'"
        os.system(command)



def sendImg(sock):
    path = r'C:\Users\94808\Desktop\jqb.jpg'
    img = open(path, 'rb')
    while 1:
        data = img.read(1024)
        if not data:
            print(path + ' send over')
            break
        sock.send(data)


def tcplink():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    winip = '192.168.43.6'
    linuxip = '192.168.43.229'
    s.bind((linuxip, 9999))
    s.listen(1)
    while True:
        print('waiting for connection.....')
        sock, addr = s.accept()
        print('Accept new connection from %s:%s...' % addr)
        try:
            data = sock.recv(1024)
            rcvStr = data.decode('utf-8')
            if (rcvStr == 'end'):
                sock.close()
                break
            sendStr = 'received: ' + rcvStr + '\r\n'
            str2shell(rcvStr)
            sock.send(sendStr.encode('utf-8'))
            print(sendStr.replace('\r\n', ''))
            sock.close()
        except ConnectionAbortedError as e:
            print('Connection Aborted!')
        finally:
            print('Connection from %s:%s closed.' % addr)
    s.close()


# t = threading.Thread(target=tcplink)
# t.start()
tcplink()
