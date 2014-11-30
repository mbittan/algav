#ifndef _TRIE_HYBRIDE_PRIMITIVES_H_
#define _TRIE_HYBRIDE_PRIMITIVES_H_

#include "structureTrieHybride.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
  Créé un trie hybride ayant comme racine c et comme fils inf, eq et sup.
*/
TrieHybride * trie_hybride(char c, char fin, TrieHybride * inf, 
			   TrieHybride * eq, TrieHybride * sup);

/*
  Libere la memoire associée au trie hybride t, ainsi qu'a ses fils.
*/
void free_trie_hybride(TrieHybride * t);

/*
  Description : Renvoie le caractere a la racine du trie t.
*/
char racine(TrieHybride * t);

/*
  Renvoie le sous arbre qui représente tout les (sous-)mots commencant par une
  lettre inferieur a celle presente a la racine de t
*/
TrieHybride * inferieur(TrieHybride *t);

/*
  Renvoie le sous-arbre qui contient les sous-mots dont la premiere lettre est
  le racine de t
*/
TrieHybride * egal(TrieHybride * t);

/*
  Renvoie le sous arbre qui représente tout les (sous-)mots commencant par une
  lettre superieur a celle presente a la racine de t
*/
TrieHybride * superieur(TrieHybride * t);

/*
  Renvoie 1 si t est un trie vide, 0 sinon.
*/
int est_trie_vide(TrieHybride * t);

/*
  Creer le trie hybride representant le mot passe en parametre
*/
TrieHybride * creer_mot(char * mot);

/*
  Fonction creant un fichier xml (valide et indenté !) représentant le trie 
  hybride passe en parametre
*/
void generer_fichier_xml(char * nom_fichier, TrieHybride * t);

/*
  Crée le fichier (dot) répresentant le trie hybride passee en parametre
 */
void generer_fichier_dot(char * nom_fichier, TrieHybride * t);
/*
  Affiche le trie hybride sur la sortie standard (moche)
*/
void print_trie_hybride(TrieHybride * t);

/*
  Fonction permettant d'ajouter un mot au trie passé en parametre
*/
TrieHybride * ajouter_trie_hybride(char * mot, TrieHybride * t);
#endif
