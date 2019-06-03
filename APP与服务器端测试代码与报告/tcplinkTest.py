import socket
import threading
import os
import time
import subprocess


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
            sock.send(sendStr.encode('utf-8'))
            print(sendStr.replace('\r\n', ''))
            sock.close()
        except ConnectionAbortedError as e:
            print('Connection Aborted!')
        finally:
            print('Connection from %s:%s closed.' % addr)
    s.shutdown(2)
    s.close()

tcplink()



