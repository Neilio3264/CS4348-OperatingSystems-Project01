BIN_DIR = ../bin
OBJS_DIR = ../lib

OBJS	= $(OBJS_DIR)/main.o
SOURCE	= main.cpp
OUT	= $(BIN_DIR)/driver
CC	 = g++
FLAGS	 = -g -c -std=c++11 -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS_DIR)/main.o: main.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)