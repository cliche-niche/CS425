# A4 Submission from 200057

from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
serverSocket.bind(("localhost", serverPort))
print ("The server is ready to receive")

while True:
    sentence, addr = serverSocket.recvfrom(1024)
    print("Connection from", addr, "is established")
    print("Server received:", sentence.decode())
    serverSocket.sendto(sentence.decode().upper().encode(), addr)

# Please write a socket programming for UDP client server application with 1 server and 1 client. 
# You can reuse the code shown in the class and can do some small changes as needed.