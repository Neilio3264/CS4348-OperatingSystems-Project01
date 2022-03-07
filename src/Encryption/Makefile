BIN_DIR = ../../bin
OBJS_DIR = ../../lib

OBJS	= $(OBJS_DIR)/krypto.o $(OBJS_DIR)/encryption.o
SOURCE	= krypto.cpp encryption.cpp
HEADER	= ../../include/Encryption/encryption.h ../../include/Encryption/encryption_states.h
OUT	= $(BIN_DIR)/krypto
CC	 = g++
FLAGS	 = -g -c -std=c++11 -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS_DIR)/krypto.o: krypto.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR)/encryption.o: encryption.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)