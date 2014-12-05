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

/*
  Supprime le dernier element de la liste
*/
void * supprimer_fin(Liste * l);

/*
  Applique la fonction passee en parametre a tout les elements de la liste
*/
void map(Liste * l, void (*f)(void *));

/*
  Libere la memoire associee a la liste
*/
void destroy_liste(Liste * l);

/*
  Cherche si l'element est present dans la liste.
  le pointeur eq doit pointer sur une fonction qui renvoie 1 si les deux
  elements sont egaux, 0 sinon.
*/
int estpresent(Liste * l, void * data, int (*eq)(void *,void*));
#endif
