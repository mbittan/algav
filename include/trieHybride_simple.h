#ifndef _TH_SIMPLE_H_
#define _TH_SIMPLE_H_

#include "trieHybride_primitives.h"

/*
  Fonction permettant de chercher si un mot est present dans le trie hybride
  passe en parametre. Renvoie 1 si le mot est present, 0 sinon.
*/
int recherche_trie_hybride(TrieHybride * t, char * mot);

/*
  Compte le nombre de mots present dans le trie hybride t
*/
int comptage_mots(TrieHybride * t);
#endif
