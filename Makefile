
NAME=HRA2016
NAMECLI=$(NAME)-cli 


CC=g++
CFLAGS=-Wall -Wextra --std=c++11 -pedantic

all: $(NAMECLI) $(NAME)


$(NAME): src/main-gui.cpp
	$(CC) $(CFLAGS) src/main-gui.cpp -o $(NAME) src/game.cpp src/player.cpp 
	
$(NAMECLI): src/main-cli.cpp
	$(CC) $(CFLAGS) src/main-cli.cpp -o $(NAMECLI) src/game.cpp src/game-cli.cpp src/player.cpp src/console.cpp


run-cli: $(NAMECLI)
	@./HRA2016-cli 

clean:
	rm -f *~ *.bak
	rm -f $(NAME)
