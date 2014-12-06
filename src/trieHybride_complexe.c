#include "trieHybride_complexe.h"

briandais_t * conversion(TrieHybride * t){
  if(t==NULL){
    return NULL;
  }
  briandais_t * b = conversion(t->inferieur);
  briandais_t * b2, * aux;
  if(t->fin){
    b2 = new_briandais(t->c,new_empty_briandais(),NULL);
    b2->son->brother=conversion(t->egal);
  }else{
    b2 = new_briandais(t->c,NULL,NULL);
    b2->son=conversion(t->egal);
  }
  b2->son=conversion(t->egal);
  b2->brother=conversion(t->superieur);

  aux = b;
  while(aux && aux->brother!=NULL){
    aux=aux->brother;
  }
  if(aux==NULL){
    return b2;
  }else{
    aux->brother=b2;
  }
  return b;
}
