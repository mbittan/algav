include makefile.inc

all : directories test_exemple_base briandais liste_tests

directories: $(OBJ) $(BIN) $(BINTEST)

$(BINTEST) : 
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

liste_tests : $(BINTEST)/liste_tests

test_exemple_base : $(BIN)/test_exemple_base

$(BINTEST)/liste_tests : $(OBJ)/liste.o $(OBJ)/liste_tests.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

$(BIN)/test_exemple_base : $(OBJ)/test_exemple_base.o $(OBJ)/trieHybride_primitives.o $(OBJ)/trieHybride_simple.o $(OBJ)/gestion_fichier.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC)

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

rapport:
	cd $(RAPPORT) && make

clean :
	rm -rf $(OBJ)/ $(BIN)/ *~ \#* .\#*
	rm -f $(SRC)/*~ $(SRC)/\#* $(SRC)/.\#*
	rm -f $(INC)/*~ $(INC)/\#* $(INC)/.\#*

cleanall: clean
	cd $(RAPPORT) && make cleanall

force_look:
		true

.PHONY: all clean test_exemple_base briandais cleanall rapport
