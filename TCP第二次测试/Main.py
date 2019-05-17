import socket
import threading


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
            sendStr = 'received: ' + data.decode('utf-8') + '\r\n'
            sock.send(sendStr.encode('utf-8'))
            print(sendStr.replace('\r\n',''))
            sock.close()
        except ConnectionAbortedError as e:
            print('Connection Aborted!')
        finally:
            print('Connection from %s:%s closed.' % addr)




t = threading.Thread(target=tcplink)
t.start()
