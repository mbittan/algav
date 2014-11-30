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

int listeMotsRec(TrieHybride * t, char * buff, int n){
  if(t==NULL){
    return 0;
  }
  listeMotsRec(t->inferieur,buff,n);
  buff[n]=t->c;
  buff[n+1]='\0';
  if(t->fin){
    printf("%s\n",buff);
  }
  listeMotsRec(t->egal,buff,n+1);
  buff[n]='\0';
  listeMotsRec(t->superieur,buff,n);
  return 0;
}

void listeMots(TrieHybride * t){
  char buff[100];
  listeMotsRec(t,buff,0);
}

int comptageNil(TrieHybride * t){
  if(t==NULL){
    return 1;
  }
  int n1,n2,n3;
  n1=comptageNil(t->inferieur);
  n2=comptageNil(t->egal);
  n3=comptageNil(t->superieur);
  return n1+n2+n3;
} 
