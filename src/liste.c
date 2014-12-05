#include "liste.h"

Liste * creer_liste(){
  Liste * l = malloc(sizeof(Liste));
  if(l==NULL){
    fprintf(stderr,"Erreur lors de l'allocation de la liste\n");
    return NULL;
  }

  l->taille=0;
  l->debut=NULL;
  l->fin=NULL;
  return l;
}

Element * creer_element(void * data){
  Element * e = malloc(sizeof(Element));
  if(e==NULL){
    fprintf(stderr,"Erreur lors de l'allocation d'un element liste\n");
    return NULL;
  }

  e->data=data;
  e->suiv=NULL;
  e->prec=NULL;
  return e;
}

void inserer_debut(Liste * l, void * data){
  Element * e = creer_element(data);
  if(l->taille==0){
    e->suiv=e;
    e->prec=e;
    l->debut=e;
    l->fin=e;
  }else{
    e->suiv=l->debut;
    e->prec=l->fin;
    l->debut->prec=e;
    l->fin->suiv=e;
    l->debut=e;
  }
  l->taille++;
}

void inserer_fin(Liste * l, void * data){
  Element * e = creer_element(data);
  if(l->taille==0){
    e->suiv=e;
    e->prec=e;
    l->debut=e;
    l->fin=e;
  }else{
    e->suiv=l->debut;
    e->prec=l->fin;
    l->debut->prec=e;
    l->fin->suiv=e;
    l->fin=e;
  }
  l->taille++;
}

void * supprimer_debut(Liste * l){
  void * data;
  Element * aux;
  if(l->taille==0){
    return NULL;
  }

  if(l->taille==1){
    data=l->debut->data;
    free(l->debut);
    l->debut=NULL;
    l->fin=NULL;
  }else{
    data=l->debut->data;
    l->debut->suiv->prec=l->fin;
    l->fin->suiv=l->debut->suiv;
    aux=l->debut;
    l->debut=l->debut->suiv;
    free(aux);
  }
  l->taille--;
  return data;
}

void * supprimer_fin(Liste * l){
  void * data;
  Element * aux;
  if(l->taille==0){
    return NULL;
  }

  if(l->taille==1){
    data=l->debut->data;
    free(l->debut);
    l->debut=NULL;
    l->fin=NULL;
  }else{
    data=l->fin->data;
    l->fin->prec->suiv=l->debut;
    l->debut->prec=l->fin->prec;
    aux=l->fin;
    l->fin=l->fin->prec;
    free(aux);
  }
  l->taille--;
  return data;
}

void map(Liste * l,void (*f)(void *)){
  Element * e=l->debut;
  int i;
  for(i=0;i<l->taille;i++,e=e->suiv){
    f(e->data);
  }
}

void destroy_liste(Liste * l){
  Element * e=l->debut;
  Element * aux;
  int i;
  for(i=0;i<l->taille;i++){
    aux=e;
    e=e->suiv;
    free(aux);
  }
  free(l);
}

int estpresent(Liste * l, void * data, int (*eq)(void *,void*)){
  Element * e=l->debut;
  int i;
  for(i=0;i<l->taille;i++,e=e->suiv){
    if(eq(data,e->data)){
      return 1;
    }
  }
  return 0;
}
