#include "gestion_fichier.h"

int ouvrir_fichier(char * nom){
  struct stat st;
  if(stat(nom,&st)==1){
    return -2;
  }
  if(!S_ISREG(st.st_mode)){
    return -3;
  }
  return open(nom, O_RDONLY, 0666);
}

int mot_suivant(int fd, char * mot){
  char c;
  int ret;
  int cpt=0;
  if((ret=read(fd, &c, sizeof(char)))==-1){
    return -1;
  }else if(ret==0){
    return 0;
  }

  while(!isalnum(c)){
    if((ret=read(fd,&c,sizeof(char)))==0){
      return 0;
    }else if(ret==-1){
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
      return -1;
    }
  }
  mot[cpt]='\0';
  return cpt;
}
