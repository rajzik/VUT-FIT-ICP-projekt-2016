
NAME=HRA2016
NAMECLI=$(NAME)-cli 


CC=g++
CFLAGS=-Wall -Wextra --std=c++11 -pedantic
LFLAGS=-lboost_system -lboost_filesystem
LFLAGS += $(shell command -v g++-4.8 >/dev/null 2>&1 && echo -n "-static-libstdc++")

all: $(NAMECLI) gui


#$(NAME): src/main-gui.cpp
#	$(CC) $(CFLAGS) src/main-gui.cpp -o $(NAME) src/game.cpp src/player.cpp $(LFLAGS) 
gui:
	qmake-qt5 src/src.pro -o gui-compiled/Makefile  
	$(MAKE) CXX=$(CC) -C gui-compiled -o $(NAME)
	rm -rf gui-compiled/

$(NAME):src/main-gui.cpp
	$(CC) $(CFLAGS) src/main-gui.cpp -o $(NAME) src/game.cpp src/player.cpp $(LFLAGS) 


$(NAMECLI): src/main-cli.cpp
	$(CC) $(CFLAGS) src/main-cli.cpp -o $(NAMECLI) src/game.cpp src/game-cli.cpp src/player.cpp src/console.cpp $(LFLAGS)

cli: $(NAMECLI)
	@./HRA2016-cli



run: all
	@./HRA2016 && ./HRA2016-cli 

clean:
	rm -f $(NAME) $(NAMECLI)
