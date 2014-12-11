include makefile.inc

all : directories lib_trie_hybride lib_briandais benchmark benchmark_trie_hybride main

directories: $(OBJ) $(BIN) $(LIB)

$(LIB) : 
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

main : $(BIN)/main

benchmark_trie_hybride : $(BIN)/bench_trie_hybride

$(BIN)/main : $(OBJ)/gestion_fichier.o $(OBJ)/main.o $(LIB)/trie_hybride.a $(LIB)/briandais.a $(OBJ)/liste.o 
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC) -pthread

$(BIN)/bench_trie_hybride : $(OBJ)/gestion_fichier.o $(OBJ)/bench_trie_hybride.o $(LIB)/trie_hybride.a $(LIB)/briandais.a $(OBJ)/liste.o 
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC) -pthread

benchmark : $(BIN)/benchmark

test_exemple_base : $(BIN)/test_exemple_base

lib_trie_hybride : $(LIB)/trie_hybride.a

lib_briandais: $(LIB)/briandais.a

$(LIB)/trie_hybride.a : $(OBJ)/trieHybride_primitives.o $(OBJ)/trieHybride_simple.o $(OBJ)/trieHybride_complexe.o
	ar -rs $@ $^

$(LIB)/briandais.a: $(OBJ)/briandais.o
	ar -rs $@ $<

$(BIN)/benchmark: $(OBJ)/benchmark.o $(OBJ)/gestion_fichier.o $(LIB)/trie_hybride.a $(LIB)/briandais.a $(OBJ)/liste.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC) -pthread

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/bench_trie_hybride.o: $(SRC)/bench_trie_hybride.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/benchmark.o: $(SRC)/benchmark.c $(INC)/benchmark.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/liste.o : $(SRC)/liste.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I$(INC)

$(OBJ)/gestion_fichier.o : $(SRC)/gestion_fichier.c $(INC)/gestion_fichier.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/trieHybride_primitives.o : $(SRC)/trieHybride_primitives.c $(INC)/trieHybride_primitives.h $(INC)/structureTrieHybride.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/trieHybride_simple.o : $(SRC)/trieHybride_simple.c $(INC)/trieHybride_simple.h $(INC)/trieHybride_primitives.h $(INC)/structureTrieHybride.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/briandais.o: $(SRC)/briandais.c $(INC)/briandais.h $(INC)/gestion_fichier.h $(INC)/trieHybride_simple.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

$(OBJ)/trieHybride_complexe.o :  $(SRC)/trieHybride_complexe.c $(INC)/trieHybride_complexe.h $(INC)/trieHybride_simple.h $(INC)/trieHybride_primitives.h $(INC)/structureTrieHybride.h
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC)

rapport:
	cd $(RAPPORT) && make

clean :
	rm -rf $(LIB)/ $(OBJ)/ $(BIN)/ *~ \#* .\#*
	rm -f $(SRC)/*~ $(SRC)/\#* $(SRC)/.\#*
	rm -f $(INC)/*~ $(INC)/\#* $(INC)/.\#*

cleanall: clean
	cd $(RAPPORT) && make cleanall

force_look:
		true

.PHONY: all clean test_exemple_base briandais cleanall rapport
