#include "trieHybride_simple.h"

int recherche_trie_hybride(TrieHybride * t, char * mot){
  if(est_trie_vide(t)){
    return 0;
  }else{
    int n = strlen(mot);
    if(n==1 &&  mot[0]==racine(t)){
      return t->fin;
    }else{
      if(mot[0]<racine(t)){
	return recherche_trie_hybride(inferieur(t),mot);
      }else if(mot[0]>racine(t)){
	return recherche_trie_hybride(superieur(t),mot);
      }else{
	return recherche_trie_hybride(egal(t),mot+1);
      }
    }
  }
}
