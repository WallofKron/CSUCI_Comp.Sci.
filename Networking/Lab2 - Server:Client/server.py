#!/usr/bin/python3

#Write a server program
#(optional) use a telnet connection to communicate with the server
#use PuTTY for Windows

import socket
from random import randint

def generateMove():
    moves = {1:'rock', 2:'paper', 3:'scissors'}
    cpuInput = moves[randint(1,3)]
    return cpuInput

def Main():
    #create socket object
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #get local host
    host = socket.gethostname() #'192.168.1.2'
    #print(host)
    port = 5000

    #bind port
    serverSocket.bind((host, port))

    #set number of connections to accept
    serverSocket.listen(1) #only one connection will be accepted

    #establish connection
    print('Waiting for client...')
    clientSocket, addr = serverSocket.accept()
    print("Connected with " + str(addr))
    msg = 'WELCOME!' + "\r\n" + '>PLAY >SCORE >QUIT' + "\r\n"
    clientSocket.send(msg.encode('ascii'))

    while True: 
              
        data = clientSocket.recv(1024).decode('ascii')
        if not data:
            break
        elif data == 'play':
            print("From connected user: " + data)
            move = generateMove()
            print("Generated \'%s\'" % move)
            clientSocket.send(move.encode('ascii'))

    print("Closing connection from " + str(addr))
    clientSocket.close()

if __name__ == '__main__':
    Main()