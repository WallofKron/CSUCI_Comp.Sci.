# =====SERVER======
#!/usr/bin/python3
#Group: Zoltan Batoczki, Robert Florence
#Server/Client rock,paper scissors program using UDP sockets

import socket
from random import randint

#Generates random move to send back to client
def generateMove():
    moves = {1:'rock', 2:'paper', 3:'scissors'}
    cpuInput = moves[randint(1,3)]
    return cpuInput

def Main():
    #create socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    #set server address and port
    server_addr = (socket.gethostname(), 5000)

    #bind port
    server_socket.bind(server_addr)
    print("Starting server at %s at port %s" % server_addr)

    while True: 
        print("Waiting to recieve data") 
        try:     
            data, address = server_socket.recvfrom(10) #recieve 10 bytes
            print("Recieved %s bytes from %s" % (len(data), address))
        except socket.timeout:
            print(">>>TIMEOUT ON SOCKET<<<")
            continue

        if not data:
            error_message = "Did not recieve message"
            print(error_message)
            server_socket.sendto(error_message.encode('ascii'), address)
            break
        elif data.decode('ascii') == 'quit':
            break
        else:
            user_command = data.decode('ascii')
            print("From connected user: " + user_command)
            if user_command == 'play':
                move = generateMove()
                print("Generated \'%s\'" % move)
                server_socket.sendto(move.encode('ascii'), address)

    print("Closing connection...")
    server_socket.close()

if __name__ == '__main__':
    Main()
