import socket
import threading


def tcplink(sock, addr):
    print('Accept new connection from %s:%s...' % addr)
    while True:
        data = sock.recv(1024)
        print(repr(data))
        if not data or data.decode('utf-8') == 'exit':
            break
        sock.send(('Hello, %s!' % data.decode('utf-8')).encode('utf-8'))
    sock.close()
    print('Connection from %s:%s closed.' % addr)


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('10.128.72.36',9999))
s.listen(1)
print('waiting for connection.....')

while   True:
    sock, addr = s.accept()
    t = threading.Thread(target=tcplink, args=(sock,addr))
    t.start()
