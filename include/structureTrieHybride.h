#ifndef _STRUCT_TRIE_HYBRIDE_H_
#define _STRUCT_TRIE_HYBRIDE_H_

typedef struct _trie_hybride {
  char c;   //Caractere de la racine
  char fin; //Vaut 1 si le noeud represente la fin d'un mot
  struct _trie_hybride * inferieur;
  struct _trie_hybride * egal;
  struct _trie_hybride * superieur;
} TrieHybride;

#endif
