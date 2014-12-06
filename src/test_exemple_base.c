#include "trieHybride_complexe.h"
#include "gestion_fichier.h"
#include "liste.h"
#include "briandais.h"

void print(void * d){
  printf("Mot : %s\n", (char *) d);
}
int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  double res;
  char buff[100];
  int fd=ouvrir_fichier(SHAKESPEARE_DIR"hamlet.txt");
  if(fd<0){
    perror("open");
    exit(1);
  }
  memset(buff,'\0',100*sizeof(char));
  while(mot_suivant(fd,buff)){
    t=ajouter_trie_hybride(buff,t);
  }
 
  printf("%d %f %d\n", hauteur(t),profondeur_moyenne(t),comptage_mots(t));
  generer_fichier_dot("t1.dot",t);
  Liste * l = liste_mots(t);
  t=equilibrer(t);
  printf("%d %f %d\n", hauteur(t),profondeur_moyenne(t),comptage_mots(t));
  generer_fichier_dot("t2.dot",t);
  Liste * l2=liste_mots(t);
  printf("%d,%d\n",l->taille,l2->taille);
  /* map(l,print); */
  /* printf("------------------------------------------------------------------------\n"); */
  /* map(l2,print); */
  return EXIT_SUCCESS;
}
