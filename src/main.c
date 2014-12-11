#define _XOPEN_SOURCE 777

#include "trieHybride_complexe.h"
#include "briandais.h"
#include "gestion_fichier.h"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define NORMAL "\033[39m"

#define THTYPE 1
#define BRTYPE 2

TrieHybride * t = NULL;
briandais_t * b = NULL;
int fin = 0;

void print(void * d){
  printf("%s\n",(char *)d);
}
void get_chaine(char * buff, size_t taille){
  fgets(buff,taille,stdin);
  buff[strlen(buff)-1]='\0';
}

int getchoix(int deb, int fin){
  int choix;
  char buff[128];
  fgets(buff,128*sizeof(char),stdin);
  sscanf(buff,"%d",&choix);
  while(choix<deb || choix > fin){
    printf("Choix incorrect. Nouveau choix : ");
    fgets(buff,128*sizeof(char),stdin);
    sscanf(buff,"%d",&choix);
  }
  return choix;
}

void insertion(int type){
  char buff[1024];
  int choix;

  printf("\nType d'insertion :\n");
  printf("1 : Lecture de mots a partir d'un fichier\n");
  printf("2 : Insertion d'un seul mot\n");
  printf("Votre choix : ");
  choix=getchoix(1,2);

  if(choix==1){
    printf("Chemin du fichier contenant les mots a inserer : ");
    get_chaine(buff,1024*sizeof(char));
    if(type==THTYPE){
      t=lire_fichier_th(buff,t);
      if(t==NULL){
	perror("Lecture fichier");
	return;
      }
    }else{
      b=lire_fichier_briandais(buff,b);
      if(b==NULL){
	perror("Lecture fichier");
	return;
      }
    }
    printf("L'insertion s'est bien passee\n");
  }else{
    printf("Mot a inserer : ");
    get_chaine(buff,1024*sizeof(char));
    if(type==THTYPE){
      t=ajouter_trie_hybride(buff,t);
    }else{
      b=insert_briandais(b,buff);
    }
    printf("L'insertion s'est bien passee\n");
  }
}

void insert_shakespeare(type){
  Liste * l = fichiers_reguliers(SHAKESPEARE_DIR);
  char * fic;
  while((fic=(char *)supprimer_debut(l))){
    if(type==THTYPE){
      t=lire_fichier_th(fic,t);
    }else{
      b=lire_fichier_briandais(fic,b);
    }
    free(fic);
  }
  free(l);
  printf("L'insertion s'est bien passee !\n");
}

void recherche(int type){
  char buff[128];
  int res;
  printf("Mot a chercher : ");
  get_chaine(buff,128*sizeof(char));

  if(type==THTYPE){
    res=recherche_trie_hybride(t,buff);
  }else{
    res=search_briandais(b,buff);
  }

  if(res){
    printf(GREEN"Mot %s trouve !\n"NORMAL,buff);
  }else{
    printf(RED"Mot %s non trouve !\n"NORMAL,buff);
  }
}

void compter(int type){
  int res;  
  if(type==THTYPE){
    res=comptage_mots(t);
  }else{
    res=count_briandais(b);
  }
  printf("Nombre de mots :"BLUE" %d\n"NORMAL, res);
}

void lister(int type){
  Liste * mots = NULL;
  if(type==THTYPE){
    mots=liste_mots(t);
  }else{
    mots=list_briandais(b);
  }

  if(mots->debut!=NULL){
    map(mots,print);
    map(mots,free);
    destroy_liste(mots);
  }else{
    printf("Aucun mots !\n");
  }
}

void cpt_null(int type){
  int res;  
  if(type==THTYPE){
    res=comptage_nil(t);
  }else{
    res=count_null_briandais(b);
  }
  printf("Nombre de pointeurs vers NULL :"BLUE" %d\n"NORMAL, res);
}

void produire_latex(int type){
  char * nom;
  if(type==THTYPE){
    nom="trie_hybride.tex";
    generer_fichier_latex(nom,t);
  }else{
    nom="briandais.tex";
    export_to_latex(b,nom);
  }
  printf("Fichier exporté avec succes sous le nom "BLUE"%s\n"NORMAL,nom);
}

void produire_svg(int type){
  char * nom;
  if(type==THTYPE){
    nom="trie_hybride";
    creer_fichier_svg(nom,t);
    printf("Fichier exporté avec succes sous le nom "BLUE"%s.svg\n"NORMAL,nom);
  }else{
    nom="briandais.svg";
    export_to_svg(b,nom);
    printf("Fichier exporté avec succes sous le nom "BLUE"%s\n"NORMAL,nom);
  }
}

void haut(int type){
  int res;  
  if(type==THTYPE){
    res=hauteur(t);
  }else{
    res=height_briandais(b);
  }
  printf("Hauteur :"BLUE" %d\n"NORMAL, res);
}

void profmoy(int type){
  double res;  
  if(type==THTYPE){
    res=profondeur_moyenne(t);
  }else{
    res=average_depth_briandais(b);
  }
  printf("Profondeur moyenne :"BLUE" %f\n"NORMAL, res);
}

void prefix(int type){
  char buff[128];
  int res; 

  printf("Prefixe : ");
  get_chaine(buff,128*sizeof(char));
 
  if(type==THTYPE){
    res=prefixe(t,buff);
  }else{
    res=prefix_briandais(b,buff);
  }
  printf("Nombre de mots dont %s est le prefixe  :"BLUE" %d\n"NORMAL, buff, res);
}

void suppr(int type){
  char buff[1024];
  int choix;
  int fd;

  printf("\nType de suppression :\n");
  printf("1 : Suppression de mots a partir d'un fichier\n");
  printf("2 : Suppression d'un seul mot\n");
  printf("Votre choix : ");
  choix=getchoix(1,2);

  if(choix==1){
    printf("Chemin du fichier contenant les mots a supprimer : ");
    get_chaine(buff,1024*sizeof(char));
    if((fd=ouvrir_fichier(buff))<0){
      perror("Ouverture fichier");
      return;
    }

    while(mot_suivant(fd,buff)>0){
      if(type==THTYPE){
	t=supprimer(t,buff);
      }else{
	delete_briandais(&b,buff);
      }
    }

    printf("La suppression s'est bien passee\n");
  }else{
    printf("Mot a supprimer : ");
    get_chaine(buff,1024*sizeof(char));
    if(type==THTYPE){
      t=supprimer(t,buff);
    }else{
      delete_briandais(&b,buff);
    }
    printf("La suppression s'est bien passee\n");
  }
}

int usage_memoire(TrieHybride *t){
  if(t==NULL){
    return 0;
  }
  int res=usage_memoire(t->inferieur)+usage_memoire(t->egal)
    +usage_memoire(t->superieur);
  return res+sizeof(TrieHybride);
}

void usemem(int type){
  int res;  
  if(type==THTYPE){
    res=usage_memoire(t);
  }else{
    res=memory_usage_briandais(b);
  }
  printf("Utilisation memoire :"BLUE" %d octets\n"NORMAL, res);
}

void equil(int type){
  if(type==THTYPE){
    printf("Hauteur avant equilibrage : "BLUE"%d"NORMAL
	   ", profondeur moyenne : "BLUE"%f\n"NORMAL,hauteur(t),profondeur_moyenne(t));
    t=equilibrer(t);
    printf("Hauteur apres equilibrage : "BLUE"%d"NORMAL
	   ", profondeur moyenne : "BLUE"%f\n"NORMAL,hauteur(t),profondeur_moyenne(t));
  }else{
    printf("L'equilibrage n'existe pas pour les arbres de la briandais\n");
  }
}

void conv(int * type){
  if(*type==THTYPE){
    *type=BRTYPE;
    b=conversion(t);
    free_trie_hybride(t);
    t=NULL;
  }else{
    *type=THTYPE;
    t=convert_to_hybrid(b);
    destroy_briandais(&b);
    b=NULL;
  }
}
void traitement_choix(int choix, int * type){
  switch(choix){
  case 1 : {
    insertion(*type);
    break;
  }
  case 2 : {
    insert_shakespeare(*type);
    break;
  }
  case 3 : {
    recherche(*type);
    break;
  }
  case 4 : {
    compter(*type);
    break;
  } 
  case 5 : {
    lister(*type);
    break;
  }  
  case 6 : {
    cpt_null(*type);
    break;
  }  
  case 7 : {
    haut(*type);
    break;
  } 
  case 8 : {
    profmoy(*type);
    break;
  } 
  case 9 : {
    prefix(*type);
    break;
  } 
  case 10 : {
    suppr(*type);
    break;
  }
  case 11 : {
    equil(*type);
    break;
  }
  case 12 : {
    produire_latex(*type);
    break;
  }
  case 13 : {
    produire_svg(*type);
    break;
  }
  case 14 : {
    usemem(*type);
    break;
  } 
  case 15 : {
    conv(type);
    break;
  }
  case 16 : {
    if(t!=NULL){
      free_trie_hybride(t);
      t=NULL;
    }
    if(b!=NULL){
      destroy_briandais(&b);
      b=NULL;
    }
    fin=1;
    break;
  }
    
  }
}

int main(int argc, char ** argv){
  int choix;  
  int type=0;

  printf("Structure a utiliser :\n");
  printf("1 : Tries Hybride\n");
  printf("2 : Arbres de la briandais\n");
  printf("Votre choix : ");

  choix=getchoix(1,2);
  type=choix;

  while(!fin){
    printf("\nOperation a effectuer :\n");
    printf("1  : Inserer des mots\n");
    printf("2  : Insertion de l'ensemble de l'oeuvre de Shakespeare\n");
    printf("3  : Rechercher un mot\n");
    printf("4  : Compter le nombre de mots\n");
    printf("5  : Afficher la liste des mots\n");
    printf("6  : Afficher le nombre de pointeurs vers NULL\n");
    printf("7  : Calculer la hauteur de l'arbre\n");
    printf("8  : Profondeur moyenne de l'arbre\n");
    printf("9  : Nombre de mots prefixés par un certain mot\n");
    printf("10 : Suppresion de mots\n");
    printf("11 : Equilibrage (seulement pour trie hybride)\n");
    printf("12 : Exporter vers latex (marche seulement avec des petits arbres)\n");
    printf("13 : Exporter vers svg (marche avec toutes tailles d'arbre, mais\n");
    printf("requiert beaucoup de temps pour les tries hybrides)\n");
    printf("14 : Utilisation memoire\n");
    printf("15 : Conversion vers %s (Les fonctions s'appliqueront alors\n a l'arbre converti)\n", 
	   type==THTYPE ? "arbre de la briandais" : "trie hybride");
    printf("16 : Quitter\n");
    printf("Votre choix : ");  
    
    traitement_choix(getchoix(1,16),&type);
  }
  return EXIT_SUCCESS;
}
