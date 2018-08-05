#!/usr/bin/python3
# ===== CLIENT =====
#Group: Zoltan Batoczki, Robert Florence
#Server/Client rock,paper scissors program using UDP sockets

import socket

wins = 0
losses = 0
draws = 0

def play(cpu_choice):
    global wins
    global losses
    global draws
    playerMove = input("Choose rock, paper, or scissors --> ") #player makes a move

    #client processes server move
    print("Player chose: " + playerMove.lower())
    print("Server played: " + cpu_choice)


    #determines outcome
    if(playerMove == cpu_choice) :
        draws += 1                #draw
        print("It's a draw!")
    elif(playerMove == 'rock'):
        if(cpu_choice == 'paper'):
            losses += 1              #player lost
            print("You lost!")
        else:
            wins += 1                #cpu_choice: scissors
            print("You win!")
    elif(playerMove == 'paper'):
        if(cpu_choice == 'scissors'):
            losses += 1
            print("You lost!")
        else:
            wins += 1                 #cpu choice: rock
            print("You win!")
    elif(playerMove == 'scissors'):
        if(cpu_choice == 'rock'):
            losses += 1
            print("You lost!")
        else:
            wins += 1                 #cpu choice: paper
            print("You win!")

def Main():
    global wins
    global losses
    global draws
    #tracks player score
    

    #Create UDP 
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = (input("Enter IP address: "), int(input("Enter port number: ")))
    message = input("Enter 'play' or 'quit': ").lower()

    try:
        while message != 'quit':
            #Send message to UDP server
            print("Sending message")
            sent = client_socket.sendto(message.encode('ascii'), server_address)

            #Recieve message
            print("Waiting to recieve...")
            data, server = client_socket.recvfrom(10)
            print("Recieved data")
            play(data.decode('ascii'))
            message = input("Enter 'play' or 'quit': ").lower()
    finally:
        print("Wins: %s | Losses: %s | Draws: %s" % (wins,losses,draws))
        print("Closing socket...")
        client_socket.close()

if __name__ == '__main__':
    Main()
