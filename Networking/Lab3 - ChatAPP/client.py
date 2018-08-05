#!/usr/bin/python
#Group: Zoltan Batoczki, Robert Florence
import socket

def play(connection):
    playerMove = input("Choose rock, paper, or scissors --> ") #player makes a move
    #client requests server move
    connection.send('play'.encode('ascii'))
    serverMove = connection.recv(1024).decode('ascii')
    #reports move to user
    print("Server played " + serverMove)
    #determines outcome
    if(playerMove == serverMove) :
        results = 2 #draw
    elif(playerMove == 'rock'):
        if(serverMove == 'paper'):
            results = 0 #player lost
        else:
            results = 1 #player won
    elif(playerMove == 'paper'):
        if(serverMove == 'scissors'):
            results = 0
        else:
            results = 1
    elif(playerMove == 'scissors'):
        if(serverMove == 'rock'):
            results = 0
        else:
            results = 1
    return results

def Main():
    #tracks player score
    wins = 0
    losses = 0
    draws = 0

    host = '192.168.13.146'
    port = 5000

    #attemptes to connect to server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host,port))
    #recieve welcome message from server
    data = s.recv(1024).decode('ascii')
    print(data)

    #user gives input and client responds accordingly
    userInput = input("-> ").lower()
    while userInput != 'quit':
        if(userInput == 'score'): #report score
            msg = '---YOUR SCORE---\n WINS: %d | LOSSES: %d | DRAWS: %d\r\n' % (wins, losses, draws)
            print(msg)
        elif userInput == 'play': #play a game
            result = play(s)
            if result == 0:
            	print("You lose!")
            	losses += 1
            elif result == 1:
            	print("You won!")
            	wins += 1
            elif result == 2:
            	print("It\'s a draw!")
            	draws += 1
        else:
            print("Incorrect input. Please try again.")
        print('>PLAY >SCORE >QUIT' + "\r\n")
        userInput = input("-> ").lower()

    print("Goodbye!")
    s.close()

if __name__ == '__main__':
    Main()