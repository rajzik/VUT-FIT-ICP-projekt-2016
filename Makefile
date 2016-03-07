# Variables
GUI_CLIENT = HRA2016
CLI_CLIENT = $(GUI_CLIENT)-cli

CXX = $(shell command -v g++-4.8 >/dev/null 2>&1 && echo -n "g++-4.8" || echo -n "g++")
RM = rm -rf
ZIP = zip -r

CFLAGS = -Wall -Wextra -c --std=c++11 -pedantic
CFLAGS_RELEASE = -O2
CFLAGS_DEBUG = -O0 -g -DDEBUG

QFLAGS_DEBUG = CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug

LFLAGS = -lpthread -lboost_system -lboost_filesystem
LFLAGS += $(shell command -v g++-4.8 >/dev/null 2>&1 && echo -n "-static-libstdc++")

SRC_FOLDER = src
BIN_FOLDER = bin
OBJ_FOLDER = obj
GUI_FOLDER = gui

# ZIP_FILE = xmilko01.zip
# PACKED_FILES = src/* inc/* art/* gui/* examples/* Makefile README.txt protocol.txt doxyconfig
# DOXYFILE = doxyconfig
# DOXY_DIR = doc

INCLUDES = -Iinc

# SERVER_SRCS = $(wildcard $(SRC_FOLDER)/*.cpp)
# SERVER_OBJS = $(addprefix $(OBJ_FOLDER)/server/, $(notdir $(patsubst %.cpp, %.o, $(SERVER_SRCS))))

CLIENT_SRCS = $(wildcard $(SRC_FOLDER)/*.cpp)
CLIENT_OBJS = $(addprefix $(OBJ_FOLDER)/, $(notdir $(patsubst %.cpp, %.o, $(CLIENT_SRCS))))

# COMMON_SRCS = $(wildcard $(SRC_FOLDER)/common/*.cpp)
# COMMON_OBJS = $(addprefix $(OBJ_FOLDER)/common/, $(notdir $(patsubst %.cpp, %.o, $(COMMON_SRCS))))

# Targets
release: CFLAGS += $(CFLAGS_RELEASE)
release: build

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: QFLAGS += $(QFLAGS_DEBUG)
debug: build

build: client


client: $(CLIENT_OBJS)
	$(CXX) $^ -o $(BIN_FOLDER)/$(CLI_CLIENT) $(LFLAGS)
	
gui:
	@cd $(GUI_FOLDER) && qmake -o ../$(GUI_WORK_FOLDER)/Makefile $(QFLAGS)
	$(MAKE) CXX=$(CXX) -C $(GUI_WORK_FOLDER)


$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)/
	$(CXX) $(INCLUDES) $(CFLAGS) $< -o $@

# $(OBJ_FOLDER)/common/%.o: $(SRC_FOLDER)/common/%.cpp
# 	@mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)/common
# 	$(CXX) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	$(RM) $(BIN_FOLDER) $(OBJ_FOLDER) $(ZIP_FILE) $(DOXY_DIR) $(GUI_WORK_FOLDER)

pack:
	$(ZIP) $(ZIP_FILE) $(PACKED_FILES)

run: gui
	# @cd ./$(BIN_FOLDER) && ./$(BIN_SERVER) &
	@cd ./$(BIN_FOLDER) && ./$(GUI_CLIENT)

run-cli: client
	# @cd ./$(BIN_FOLDER) && ./$(CLI_CLIENT) &
	@cd ./$(BIN_FOLDER) && ./$(CLI_CLIENT)

# doxygen:
# 	@command -v doxygen >/dev/null 2>&1 \
# 		&& { doxygen $(DOXYFILE); true; } \
# 		|| echo "icp-make: Doxygen not installed."

.PHONY: build release debug gui run run-cli clean 
