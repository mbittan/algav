#ifndef _TH_SIMPLE_H_
#define _TH_SIMPLE_H_

#include "trieHybride_primitives.h"

/*
  Fonction permettant de chercher si un mot est present dans le trie hybride
  passe en parametre. Renvoie 1 si le mot est present, 0 sinon.
*/
int recherche_trie_hybride(TrieHybride * t, char * mot);

/*
  Compte le nombre de mots present dans le trie hybride t
*/
int comptage_mots(TrieHybride * t);

/*
  Affiche la liste des mots dans l'ordre alphabetique
*/
void liste_mots(TrieHybride * t);

/*
  Compte le nombre de pointeur vers NULL
 */
int comptage_nil(TrieHybride *t);

/*
  Renvoi la hauteur du trie hybride
*/
int hauteur(TrieHybride * t);

/*
  Renvoi la profondeur moyenne du trie hybride
*/
double profondeur_moyenne(TrieHybride * t);

/*
  Compte le nombre de mots du dictionnaire qui sont prefixes par le mot passe
  en parametre
*/
int prefixe(TrieHybride * t, char * mot);

#endif
