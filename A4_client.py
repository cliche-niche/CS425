# A4 Submission from 200057

from socket import *

serverName = 'localhost'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
clientSocket.connect((serverName, serverPort))
sentence = input('Input lowercase sentence: ')
clientSocket.sendto(sentence.encode(), (serverName, serverPort))
modifiedSentence, addr = clientSocket.recvfrom(1024)
print ('Upper case sentence from Server', addr, modifiedSentence.decode())
clientSocket.close()