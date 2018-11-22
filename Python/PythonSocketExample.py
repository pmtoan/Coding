import socket
import sys

'''
	Simple server example
'''
soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soc.bind(('0.0.0.0', 3000))
soc.listen(10)
while True:
	client_soc, addr = soc.accept()
	message = client_soc.recv(1024).decode('utf8')
	client_soc.send('Message from server'.encode("utf8"))
	# do more stuff here
	client_soc.close()


'''
	Simple client example
'''
soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
r = soc.connect(('server_ip', 'server_port'))
soc.send('Message from client'.encode('utf8'))
message = soc.recv(1024).decode('utf8')