#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Work.h"

#define N 3

WorkFile* createWorkFile(char* name){
        /* Permet de créer un WorkFile et de l’initialiser */

        WorkFile* wf = malloc(sizeof(WorkFile));
        if (wf == NULL){
            return NULL;
        } 
        wf -> name = strdup(name);
        wf -> hash = NULL;
        wf -> mode = 0;
        return wf;
}


char* wfts(WorkFile* wf){
    /* Permet de convertir un WorkFile en chaîne de caractères contenant les différents champs séparés par des tabulations (caract`ere ’\t’) */

    char  *ch = malloc(sizeof(char)); 
    if (ch== NULL){
        return NULL;
    }
    sprintf(ch, "%s\t%s\t%d", wf->name, wf->hash, wf->mode);
    return ch;
}

WorkFile* stwf(char* ch){
        /*Permet de convertir une chaîne de caractères représentant un WorkFile en un WorkFile*/
        
        char *name = malloc(sizeof(char));
	    char *hash = malloc(sizeof(char));
	    int mode;
	    sscanf(ch,"%s\t%s\t%d\n",name,hash,&mode);
	    WorkFile *wf=createWorkFile(name);
	    wf->hash=strdup(hash);
	    wf->mode=mode;
	    return wf;

}

WorkTree* initWorkTree(){
        /* Permet d’allouer un WorkTree de taille fixée (donnée par une constante du programme) et de l’initialiser */

        WorkTree  *wkt = malloc(sizeof(WorkTree));
        if(wkt == NULL){
            return NULL;
        } 
        wkt->tab = malloc(N*sizeof(WorkFile));
        wkt->size = N;
        wkt->n=0;
        return wkt;
}


int inWorkTree(WorkTree* wt, char* name){
    /* Vérifie la présence d’un fichier ou répertoire dans un WorkTree. Cette fonction doit retourner la position du fichier dans le tableau s’il est présent, et -1 sinon */

	for(int i=0;i<=wt->n;i++){
		if(strcmp(name,wt->tab[i].name)==0){
			return i;
		}
	}
	return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode){
    /* Ajoute un fichier ou répertoire au WorkTree (s’il n’existe pas déjà)*/

	if (inWorkTree(wt,name)==-1){
		WorkFile* wf=createWorkFile(name);
		wf->hash=strdup(hash);
		wf->mode=mode;
		if(wt->n<N){
			wt->tab[wt->n]=*wf;
			(wt->n)++;
			return 1;
		}
		return -1;
	}
	return 0;
}

char* wtts(WorkTree* wt){
      /* Convertit un WorkTree en une chaîne de caractères composée des représentations des WorkFile séparées par un saut de ligne (caractère ’\n’ */

	char *ch=malloc(sizeof(char));
	for(int i=0;i<=wt->n;i++){
		strcat(ch,wfts(wt->tab+i));
		strcat(ch,"\n");
	}
	return c;
}

WorkTree* stwt(char* ch){
    /* Convertit une chaîne de caractères représentant un WorkTree en un WorkTree*/

	WorkTree* wt=initWorkTree();
	char* name=malloc(sizeof(char));
	char* hash=malloc(sizeof(char));
	int mode;
	char *chaine=ch;
	char *chaine2=ch;
	while(*chaine!='\0'){
		if(*chaine=='\n'){
			sscanf(chaine2,"%s\t%s\t%d\n",name,hash,&mode);
			appendWorkTree(wt,name,hash,mode);
			*chaine='\0';
		}else{
			chaine2=chaine+1;
		}
		chaine++;	
	}
	sscanf(ch,"%s\t%s\t%d\n",name,hash,&mode);
	appendWorkTree(wt,name,hash,mode);
	return wt;
}

int wttf(WorkTree* wt, char* file){
    /* Ecrit dans le fichier file la chaîne de caractères représentant un WorkTree */

	FILE* f=fopen(file,"w");
	char* truc=wtts(wt);
	fprintf(f,"%s\n",truc);
	fclose(f);
	return 0;
}

WorkTree* ftwt(char* file){
    /* Construit un WorkTree à partir d’un fichier qui contient sa repr ́esentation en chaîne de caractères */

	FILE* f=fopen(file,"r");
	char* tmp;
	char buffer[600];
	while(fgets(buffer,600,f)){
		strcat(tmp,buffer);
	}
	WorkTree* wt=stwt(tmp);
	fclose(f);
	return wt;
}


/*ajout des fonctions utiles*/

void libererWorkFile(WorkFile* wf){
    /*permet de convertir un WorkFile en chaîne de caractères contenant les différents champs séparés par des tabulations (caract`ere ’\t’)*/

    free(wf->name);
    if(wf->hash){
        free(wf->hash);
    }
    free(wf);
}

void libererWorkTree(WorkTree* wkt){
    if(wkt != NULL){
        for(int i=0, i<wkt->n, i++){
            free(wkt->tab[i]);
        }
        free(wkt->tab);
        free(wkt);
    }
}


int main(){
    WorkFile* wf1 = createWorkFile("test_createWorkFile");
    printf("%s\n", wf1->name);
    
    char *s1 = wfts(wf1);
    printf("%s\n", s1);

    WorkFile* wf2 = stwf(s1);
    printf("%s\n", wf2->name);

    libererWorkFile(wf1);
    libererWorkFile(wf2);
    free(s1);

    return 0;
}
