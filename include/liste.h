#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct _elem {
  void * data;
  struct _elem * suiv;
  struct _elem * prec;
} Element;

typedef struct _liste {
  int taille;
  Element * debut;
  Element * fin;
} Liste;

/*
  Cree une liste vide.
*/
Liste * creer_liste();

/*
  Cree un element vide a partir de donnee passee en parametre.
*/
Element * creer_element(void * data);

/*
  Insere l'element passe en parametre au debut de la liste.
*/
void inserer_debut(Liste * l, void * data);

/*
  Insere l'element en fin de liste
*/
void inserer_fin(Liste * l, void * data);

/*
  Supprime le premier element de la liste
*/
void * supprimer_debut(Liste * l);
#endif
