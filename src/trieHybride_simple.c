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

int liste_mots_rec(TrieHybride * t, char * buff, int n){
  if(t==NULL){
    return 0;
  }
  liste_mots_rec(t->inferieur,buff,n);
  buff[n]=t->c;
  buff[n+1]='\0';
  if(t->fin){
    printf("%s\n",buff);
  }
  liste_mots_rec(t->egal,buff,n+1);
  buff[n]='\0';
  liste_mots_rec(t->superieur,buff,n);
  return 0;
}

void liste_mots(TrieHybride * t){
  char buff[100];
  liste_mots_rec(t,buff,0);
}

int comptage_nil(TrieHybride * t){
  if(t==NULL){
    return 1;
  }

  int n1,n2,n3;
  n1=comptage_nil(t->inferieur);
  n2=comptage_nil(t->egal);
  n3=comptage_nil(t->superieur);
  return n1+n2+n3;
} 

int max(int a, int b){
  if(a<b){
    return b;
  }else{
    return a;
  }
}
int hauteur(TrieHybride *t){
  if(t==NULL){
    return 0;
  }

  int n1,n2,n3;
  n1=hauteur(t->inferieur);
  n2=hauteur(t->egal);
  n3=hauteur(t->superieur);
  return 1+max(max(n1,n2),n3); 
}

double profondeur_moyenne(TrieHybride * t){
  if(t==NULL){
    return 0;
  }
  int n1,n2,n3;
  n1=hauteur(t->inferieur);
  n2=hauteur(t->egal);
  n3=hauteur(t->superieur);
  return (n1+n2+n3)/3.0;
}

int prefixe(TrieHybride * t, char * mot){
  if(t==NULL){
    return 0;
  }
  int n = strlen(mot);
  if(n==1 && mot[0]==racine(t)){
    return t->fin+comptage_mots(egal(t));
  }
  if(mot[0]<racine(t)){
    return prefixe(inferieur(t),mot);
  }
  if(mot[0]>racine(t)){
    return prefixe(superieur(t),mot);
  }
  return prefixe(egal(t),mot+1);
}

TrieHybride * extraire_minimum(TrieHybride * t, TrieHybride * res){
  if(t->inferieur==NULL){
    TrieHybride * aux = t->superieur;
    res->c=t->c;
    res->fin=t->fin;
    res->inferieur=NULL;
    res->superieur=NULL;
    res->egal=t->egal;
    free(t);
    return aux;
  }else{
    t->inferieur=extraire_minimum(t->inferieur,res);
    return t;
  }
}

TrieHybride * supprimer_racine(TrieHybride * t){
  if(t->inferieur==NULL && t->superieur==NULL){
    free(t);
    return NULL;
  }else if(t->inferieur==NULL){
    TrieHybride * aux = t->superieur;
    t->c=aux->c;
    t->fin=aux->fin;
    t->inferieur=aux->inferieur;
    t->egal=aux->egal;
    t->superieur=aux->superieur;
    free(aux);
    return t;
  }else if(t->superieur==NULL){
    TrieHybride * aux = t->inferieur;
    t->c=aux->c;
    t->fin=aux->fin;
    t->inferieur=aux->inferieur;
    t->egal=aux->egal;
    t->superieur=aux->superieur;
    free(aux);
    return t;
  }else{
    TrieHybride res;
    t->superieur=extraire_minimum(t->superieur,&res);
    t->c=res.c;
    t->fin=res.fin;
    t->egal=res.egal;
    return t;
  }
}
TrieHybride * supprimer(TrieHybride * t, char * mot){
  if(t==NULL){
    return NULL;
  }
  int n = strlen(mot);
  if(n==1 && mot[0]==racine(t)){
    t->fin=0;
    if(t->egal==NULL){
      return supprimer_racine(t);
    }else{
      return t;
    }
  }
  if(mot[0]<racine(t)){
    t->inferieur=supprimer(inferieur(t),mot);
    return t;
  }else if(mot[0]>racine(t)){
    t->superieur=supprimer(superieur(t),mot);
    return t;
  }else{
    t->egal=supprimer(egal(t),mot+1);
    if(t->egal==NULL && t->fin==0){
      return supprimer_racine(t);
    }else{
      return t;
    }
  }
}
