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

int comptage_mots(TrieHybride * t){
  if(t==NULL){
    return 0;
  }
  int inf,eq,sup;
  inf=comptage_mots(t->inferieur);
  eq=comptage_mots(t->egal);
  sup=comptage_mots(t->superieur);
  if(t->fin){
    return 1+inf+eq+sup;
  }else{
    return inf+eq+sup;
  }
}
