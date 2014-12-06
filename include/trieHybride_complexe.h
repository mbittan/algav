#ifndef _TH_COMPLEXE_H_
#define _TH_COMPLEXE_H_

#include "briandais.h"
#include "trieHybride_simple.h"

/*
  Convertit le trie hybride en arbre de la briandais
*/
briandais_t * conversion(TrieHybride * t);

/*
  Equilibre le trie hybride passe en parametre
*/
TrieHybride * equilibrer(TrieHybride * t);
#endif
