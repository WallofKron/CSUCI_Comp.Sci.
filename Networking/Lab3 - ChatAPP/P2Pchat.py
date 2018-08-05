#!usr/bin/python3

#Group: Zoltan Batoczki, Robert Florence

#REFERENCES
#http://code.activestate.com/recipes/578591-primitive-peer-to-peer-chat/
#http://cs.berry.edu/~nhamid/p2p/framework-python.html
##http://stackoverflow.com/questions/23828264/how-to-make-a-simple-multithreaded-socket-server-in-python-that-remembers-client


import socket
import threading
from time import sleep

MAX_CLIENTS = 5
client_list = [[0]*3 for i in range(MAX_CLIENTS)] #used to store connected users ip and port they are connected on; should include host information?
numClients=0

def RecieveUserList(client):
    print("test2")

def AddUsertoList(addr):
    client_list[numClients][0] = addr[0]
    client_list[numClients][1] = addr[1]
    numClients = numClients + 1
    print(client_list)

def DelUserfromList():
    print(client_list)

def CheckUsername(name):
    if len(name) >= 4 and len(name) <= 32:
        return True
    else: return False    
    
    
    
class Listener(threading.Thread):
    def __init__(self, username):
        threading.Thread.__init__(self)
        self.ip = socket.gethostbyname(socket.gethostname()) #may or may not need
        self.port = int(input("Input Port Number: "))									#LOCAL PORT
        self.username = username

    def run(self):
        print("Starting listening thread.\n")
        print('\nlocalIP = ' + str(self.ip) + '\nPort = ' + str(self.port))
        listening_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        listening_socket.bind((self.ip, self.port))
        listening_socket.listen(MAX_CLIENTS)
        while True:
            connection, addr = listening_socket.accept()
            #print('\naddr - ' + str(addr))
            AddUsertoList(addr)
            threading.Thread(target= self.ListenToClientThread, args = (connection, addr) ).start() 	#start a new thread and verify user list

            
            
    def ListenToClientThread(self, client, address):
        print("\nConnection established with " + str(address) + ". New thread started for connection.")
        self.checkClientsList(client) #check user name of client is valid
        while True:
            try:
                message = client.recv(2048).decode('ascii')
                if message: print("Them: " + message)
                else: raise error('Client disconnected')
                #message = input("You: ")
                #client.send(message.encode('ascii'))
            except:
                client.close()
                print("Client disconnected.")
                self.DelUserfromList()
                return False
        
          
    def checkClientsList(self, client):
    #List should represent a multiline string with each line of the format 
    #USERS <username> <IP> <port>\r\n
        print("*Check Clients List Running Here*")
    

    
    
    
#function used to connect to other clients    
class Sender(threading.Thread):
    def __init__(self, username, ip, port):
        threading.Thread.__init__(self)
        self.username = username
        self.ip = ip
        self.port = port

    def run(self):
        sending_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sending_socket.connect((self.ip, self.port))
        while True:
            message = input("You: ")
            if message.lower() == "quit":
                break
            else:
                try:
                    message = message + "\r\n"
                    sending_socket.send(message.encode('ascii'))
                    #recievedMsg = sending_socket.recv(2048).decode('ascii')
                    #print("Them: "+recievedMsg)
                except:
                    Exception

                    
                    

def main():

    username = input("Please create a username between 4 and 32 characters: ")
    while not CheckUsername(username):
        print("Invalid input. Please try again.")
        username = input("Please create a username between 4 and 32 characters: ")

    
    chat_listener = Listener(username)		#init Listener thread
    chat_listener.start()

    
    while True:
        command = input("\nType in command: ")
        if command.startswith("JOIN"):
            parameters = command.split(" ")
            username = parameters[1]
            ip = parameters[2]
            port = int(parameters[3])
            chat_sender = Sender(username, ip, port)
            break
            if (len(parameters[1]) == 0 or len(parameters[2]) == 0 or len(parameters[3]) == 0):
                print("INVALID JOIN COMMAND INPUT!")
        else:
            if command.startswith("QUIT"):
                sys.exit("\nProgram Terminated!")
        
            if command.startswith("HELP"):
                print("\nJOIN <username> <IP> <PORT>\nQUIT - exit program\nLIST - list all connected users")

            
    chat_sender.start()			#initialize sender thread
    
    chat_listener.join()		#wait for listener and sender thread to finish. Then Finish Program
    chat_sender.join()
    print('Goodbye.')
    
    
    
if __name__ == "__main__":
    main()

    
    #GENERALIZED FOR ALL CLIENTS    - no one user should do something that all users don't do - 
# ask for username and check value
# specify port to connect to
# spin off thread for listener and another for sender
# establish listener with IP and port
# establish sender with IP and port (does sender need a seperate port?)
# connect listener/sender to all users on 'client_list'
# 
