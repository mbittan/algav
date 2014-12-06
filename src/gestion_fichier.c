#include "gestion_fichier.h"

int ouvrir_fichier(char * nom){
  struct stat st;
  if(stat(nom,&st)==-1){
    perror("stat");
    return -1;
  }
  if(!S_ISREG(st.st_mode)){
    return -1;
  }
  return open(nom, O_RDONLY, 0666);
}

int mot_suivant(int fd, char * mot){
  char c;
  int ret;
  int cpt=0;
  if((ret=read(fd, &c, sizeof(char)))==-1){
    perror("read");
    return -1;
  }else if(ret==0){
    return 0;
  }

  while(!isalnum(c)){
    if((ret=read(fd,&c,sizeof(char)))==0){
      return 0;
    }else if(ret==-1){
      perror("read");
      return -1;
    }
  }

  while(isalnum(c)){
    if(c>='A' && c<='Z'){
      c=c-'A'+'a';
    }
    mot[cpt++]=c;
    if((ret=read(fd,&c,sizeof(char)))==0){
      break;
    }else if(ret==-1){
      perror("read");
      return -1;
    }
  }

  mot[cpt]='\0';
  return cpt;
}

TrieHybride * lire_fichier_th(char * fichier, TrieHybride * t){
  int fd;
  char buff[128];
  if((fd=ouvrir_fichier(fichier))==-1){
    return NULL;
  } 

  while(mot_suivant(fd,buff)>0){
    t=ajouter_trie_hybride(buff,t);
  }
  return t;
}

briandais_t * lire_fichier_briandais(char * fichier, briandais_t * t){ 
  int fd;
  char buff[128];
  if((fd=ouvrir_fichier(fichier))==-1){
    return NULL;
  }  
  
  while(mot_suivant(fd,buff)>0){
    t=insert_briandais(t,buff);
  }

  if(close(fd)==-1){
    perror("close");
  }

  return t;
}

Liste * fichiers_reguliers(char * dir){
  Liste * l = creer_liste();
  DIR * d= opendir(dir);
  struct dirent * dirEnt; 
  struct stat st;
  char buff[256];
  if(d==NULL){
    return NULL;
  }
  
  while((dirEnt=readdir(d))!=NULL){
    sprintf(buff,"%s%s",dir,dirEnt->d_name);
    if(stat(buff,&st)==-1){
      perror("stat");
      return NULL;
    } 

    if(S_ISREG(st.st_mode)){
      inserer_fin(l,strdup(buff));
    }
  }
  closedir(d);
  return l;
}



