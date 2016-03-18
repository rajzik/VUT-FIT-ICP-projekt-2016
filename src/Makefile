
NAME=HRA2016-cli
 
CC=g++
CFLAGS=-Wall -Wextra --std=c++11 -pedantic


$(NAME): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(NAME) game.cpp game-cli.cpp player.cpp console.cpp 
	
clean:
	rm -f *~ *.bak
	rm -f $(NAME)
