#define _XOPEN_SOURCE 777

#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#include "trieHybride_complexe.h"
#include "gestion_fichier.h"

#define NB_THREADS 4

Liste * fics=NULL;
Liste * tries=NULL;
pthread_mutex_t mutex_fics = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_tries = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t sem;

void temps(struct timeval * t){
  gettimeofday(t,NULL);
}

double soustraire(struct timeval start, struct timeval end){
  double s = start.tv_sec+(double)start.tv_usec*(1e-6);
  double e = end.tv_sec+(double)end.tv_usec*(1e-6);
  return e-s;
}  

void afficher_res(struct timeval start, struct timeval end){
  int i;
  for(i=0;i<strlen("En cours ...");i++){
    printf("\b");
  }
  printf("%f secondes\n", soustraire(start,end));
}

void * creation_trie_thread(void * args){
  char * fichier;
  TrieHybride *t = NULL;

  pthread_mutex_lock(&mutex_fics);
  while((fichier=(char *)supprimer_debut(fics))){
    pthread_mutex_unlock(&mutex_fics);
    t=lire_fichier_th(fichier,t);
    pthread_mutex_lock(&mutex_tries);
    inserer_debut(tries,t);
    sem_post(&sem);
    pthread_mutex_unlock(&mutex_tries);
    t=NULL;
    free(fichier);
    pthread_mutex_lock(&mutex_fics);
  }
  pthread_mutex_unlock(&mutex_fics);
  return NULL;
}

void * fusion_thread(void * args){
  int nbfics=*((int *)args);
  int i=1;
  TrieHybride *t=NULL;
  TrieHybride *t2 =NULL;
  sem_wait(&sem);
  pthread_mutex_lock(&mutex_tries);
  t=supprimer_debut(tries);
  pthread_mutex_unlock(&mutex_tries);

  while(i<nbfics){
    sem_wait(&sem);
    i++;
    pthread_mutex_lock(&mutex_tries);
    t2=supprimer_debut(tries);
    pthread_mutex_unlock(&mutex_tries);
    t=fusion_trie_hybride(t,t2);
    free_trie_hybride(t2);
  }
  inserer_debut(tries,t);
  pthread_cond_signal(&cond);
  return NULL;
}
int usage_memoire(TrieHybride *t){
  if(t==NULL){
    return 0;
  }
  int res=usage_memoire(t->inferieur)+usage_memoire(t->egal)
    +usage_memoire(t->superieur);
  return res+sizeof(TrieHybride);
}
int main(int argc, char ** argv){
  struct timeval start, end;
  Liste * fichiers = fichiers_reguliers(SHAKESPEARE_DIR);
  Liste * mots;
  char * fichier;
  TrieHybride * t = NULL;
  int i,fd,fd2,arg_fusion,res;
  double res_d;
  char buff[128];
  pthread_t tid[NB_THREADS];
  pthread_attr_t attr; 
  briandais_t * br;

  /****************************************************************************
                      BENCHMARK INSERTION NON MULTITHREADE
  ****************************************************************************/
  printf("Insertion de toutes les pieces de Shakespeare \t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  while((fichier=supprimer_debut(fichiers))){
    t=lire_fichier_th(fichier,t);
    free(fichier);
  }
  temps(&end);
  afficher_res(start,end);
  destroy_liste(fichiers);

  /****************************************************************************
                          SUPPRESSION MOTS HAMLET
  ****************************************************************************/
  printf("Suppression des mots de la piece \"Hamlet\" \t\t: En cours ...");  
  fflush(stdout);

  fd=ouvrir_fichier(SHAKESPEARE_DIR"hamlet.txt");
  if(fd<0){
    perror("ouverture fichier");
    exit(EXIT_FAILURE);
  }

  temps(&start);
  while(mot_suivant(fd,buff)>0){
    t=supprimer(t,buff);
  }
  temps(&end);
  afficher_res(start,end);

  if(close(fd)==-1){
    perror("close");
    exit(EXIT_FAILURE);
  }

  /****************************************************************************
                         RECHERCHE ALL'S WELL & HAMLET
  ****************************************************************************/
  printf("Recherche des mots de All's Well et Hamlet \t\t: En cours ...");  
  fflush(stdout);

  fd=ouvrir_fichier(SHAKESPEARE_DIR"hamlet.txt");
  if(fd<0){
    perror("ouverture fichier");
    exit(EXIT_FAILURE);
  }

  fd2=ouvrir_fichier(SHAKESPEARE_DIR"allswell.txt");
  if(fd2<0){
    perror("ouverture fichier");
    exit(EXIT_FAILURE);
  }

  temps(&start);
  while(mot_suivant(fd,buff)>0){
    recherche_trie_hybride(t,buff);
  } 
  while(mot_suivant(fd2,buff)>0){
    recherche_trie_hybride(t,buff);
  }
  temps(&end);

  afficher_res(start,end);
  if(close(fd)==-1){
    perror("close");
    exit(EXIT_FAILURE);
  } 

  if(close(fd2)==-1){
    perror("close");
    exit(EXIT_FAILURE);
  }

  /****************************************************************************
                        DESTRUCTION TRIE HYBRIDE
  ****************************************************************************/
  printf("Destruction du trie hybride \t\t\t\t: En cours ...");  
  fflush(stdout);

  temps(&start);
  free_trie_hybride(t);
  temps(&end);

  afficher_res(start,end);

  /****************************************************************************
                       CREATION SHAKESPEARE MULTITHREADE
  ****************************************************************************/
  fics=fichiers_reguliers(SHAKESPEARE_DIR);
  tries=creer_liste();
  sem_init(&sem,1,0);
  arg_fusion=fics->taille;  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

  printf("Insertion multithreade des oeuvres de Shakespeare\t: En cours ...");  
  fflush(stdout);


  temps(&start);
  pthread_mutex_lock(&mutex_fics);
  for(i=0;i<NB_THREADS-1;i++){
    if(pthread_create(&(tid[i]),&attr,creation_trie_thread,NULL)==-1){
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
  
  if(pthread_create(&(tid[NB_THREADS-1]),&attr,fusion_thread,&arg_fusion)==-1){
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }

  pthread_cond_wait(&cond,&mutex_fics);
  temps(&end);

  afficher_res(start,end);

  destroy_liste(fics);
  t=supprimer_debut(tries);
  destroy_liste(tries);

 /****************************************************************************
                                COMPTAGE MOTS
  ****************************************************************************/
  printf("Comptage des mots \t\t\t\t\t: En cours ...");
  fflush(stdout);

  temps(&start);
  res=comptage_mots(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %d\n",res);

  /****************************************************************************
                              POINTEURS VERS NULL
  ****************************************************************************/ 
  printf("Comptage des pointeurs vers NULL\t\t\t: En cours ...");
  fflush(stdout);

  temps(&start);
  res=comptage_nil(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %d\n",res);

  /****************************************************************************
                 CREATION ET DESTRUCTION DE LA LISTE DES MOTS
  ****************************************************************************/ 
  printf("Creation et destruction de la liste des mots\t\t: En cours ...");
  fflush(stdout);

  temps(&start);
  mots=liste_mots(t);
  while(mots->taille!=0){
    char * tmp=supprimer_debut(mots);
    free(tmp);
  }
  free(mots);
  temps(&end);
  afficher_res(start,end);

  /****************************************************************************
                                   HAUTEUR
  ****************************************************************************/
  printf("Calcul de la hauteur \t\t\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  res=hauteur(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %d\n",res);


  /****************************************************************************
                                 EQUILIBRAGE
  ****************************************************************************/
  printf("Equilibrage du trie\t\t\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  t=equilibrer(t);
  temps(&end);
  afficher_res(start,end);

  /****************************************************************************
                              RECALCUL HAUTEUR
  ****************************************************************************/
  printf("Recalcul de la hauteur \t\t\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  res=hauteur(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %d\n",res);

  /****************************************************************************
                             PROFONDEUR MOYENNE
  ****************************************************************************/
  printf("Profondeur Moyenne\t\t\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  res_d=profondeur_moyenne(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %f\n",res_d);

  /****************************************************************************
                          CONVERSION VERS BRIANDAIS
  ****************************************************************************/
  printf("Conversion vers arbre de la briandais\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  br=conversion(t);
  temps(&end);
  afficher_res(start,end);
  destroy_briandais(&br);

  /****************************************************************************
                        INSERTION D'UN MOT INEXISTANT
  ****************************************************************************/
  printf("Insertion d'un mot inexistant(anticonstitutionnellement): En cours ...");
  fflush(stdout);
  temps(&start);
  t=ajouter_trie_hybride("anticonstitutionnellement",t);
  temps(&end);
  afficher_res(start,end);
 
 /****************************************************************************
                        INSERTION D'UN MOT INEXISTANT
  ****************************************************************************/
  printf("Usage memoire (en octets)\t\t\t\t: En cours ...");
  fflush(stdout);
  temps(&start);
  res=usage_memoire(t);
  temps(&end);
  afficher_res(start,end);
  printf("\t\t\t\t\t\t\t  %d\n",res);

  free_trie_hybride(t);
  return EXIT_SUCCESS;
}
