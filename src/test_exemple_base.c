#include "gestion_fichier.h"
#include "trieHybride_complexe.h"
#include "liste.h"
#include "briandais.h"

void print(void * d){
  printf("Mot : %s\n", (char *) d);
}
int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  Liste * l = fichiers_reguliers(SHAKESPEARE_DIR);
  printf("%d\n",l->taille);
  char * fic;
  map(l,print);
  while((fic=(char *)supprimer_fin(l))){
    t=lire_fichier_th(fic,t);
  }

  printf("%d %f, %d %d\n", hauteur(t),profondeur_moyenne(t),hauteur(t->superieur), hauteur(t->inferieur));
  t=equilibrer(t);
  printf("%d %f, %d %d\n", hauteur(t),profondeur_moyenne(t),hauteur(t->superieur), hauteur(t->inferieur));
  /* map(l,print); */
  /* printf("------------------------------------------------------------------------\n); */
  /* map(l2,print); */
  free_trie_hybride(t);
  map(l,free);
  destroy_liste(l);
  return EXIT_SUCCESS;
}
