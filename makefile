include makefile.inc

all : directories lib_trie_hybride test_exemple_base briandais liste_tests

directories: $(OBJ) $(BIN) $(BINTEST) $(LIB)

$(LIB) : 
	mkdir -p $@

$(BINTEST) : 
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

liste_tests : $(BINTEST)/liste_tests

test_exemple_base : $(BIN)/test_exemple_base

<<<<<<< HEAD
=======
briandais: $(BIN)/briandais

lib_trie_hybride : $(LIB)/trie_hybride.a

$(LIB)/trie_hybride.a : $(OBJ)/trieHybride_primitives.o $(OBJ)/trieHybride_simple.o $(OBJ)/trieHybride_complexe.o
	ar -rs $@ $^

>>>>>>> 7091b59eaf28f9666d23f7d1fce669c22568cc2a
$(BINTEST)/liste_tests : $(OBJ)/liste.o $(OBJ)/liste_tests.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

$(BIN)/test_exemple_base : $(OBJ)/test_exemple_base.o $(LIB)/trie_hybride.a $(OBJ)/gestion_fichier.o $(OBJ)/briandais.o $(OBJ)/liste.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

<<<<<<< HEAD
=======
$(BIN)/briandais:  $(OBJ)/briandais.o $(OBJ)/gestion_fichier.o $(OBJ)/liste.o $(LIB)/trie_hybride.a
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

>>>>>>> 7091b59eaf28f9666d23f7d1fce669c22568cc2a
$(OBJ)/test_exemple_base.o : $(SRC)/test_exemple_base.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I$(INC)

$(OBJ)/liste.o : $(SRC)/liste.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I$(INC)

$(OBJ)/liste_tests.o : $(SRCTEST)/liste_tests.c
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
