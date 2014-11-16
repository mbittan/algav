CC = gcc
CFLAGS = -Wall -g
SRC = src
INC = include
OBJ = obj
BIN = bin

all : directories test_exemple_base briandais

directories: $(OBJ) $(BIN) $(LIB)

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

$(LIB):
	mkdir -p $(LIB)

test_exemple_base : $(BIN)/test_exemple_base

briandais: $(BIN)/briandais

$(BIN)/test_exemple_base : $(OBJ)/test_exemple_base.o $(OBJ)/trieHybride_primitives.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

$(BIN)/briandais:  $(OBJ)/briandais.o
	$(CC) $(CFLAGS) -o $@ $< -I$(INC)

$(OBJ)/test_exemple_base.o : $(SRC)/test_exemple_base.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I$(INC)

$(OBJ)/trieHybride_primitives.o : $(SRC)/trieHybride_primitives.c $(INC)/trieHybride_primitives.h $(INC)/structureTrieHybride.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/briandais.o: $(SRC)/briandais.c $(INC)/briandais.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

clean :
	rm -rf $(OBJ)/ $(BIN)/ *~ \#* .\#*
	rm -f $(SRC)/*~ $(SRC)/\#* $(SRC)/.\#*
	rm -f $(INC)/*~ $(INC)/\#* $(INC)/.\#*

.PHONY: all clean test_exemple_base briandais
