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
	return ch;
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
    /*permet de libérer un workFile*/

    free(wf->name);
    if(wf->hash){
        free(wf->hash);
    }
    free(wf);
}

void libererWorkTree(WorkTree* wkt){
	/*permet de libérer un workTree*/
    if(wkt != NULL){
        for(int i=0; i<wkt->n;i++){
            libererWorkFile(wkt->tab+i);
        }
        free(wkt->tab);
        free(wkt);
    }
}


int main(){

	/*Test pour l'exercice 4*/
	printf("Exercice 4\n");
    printf("\n");
	/*Test pour createWorFile*/
	printf("createWorkFile : ");
    WorkFile* wkf1 = createWorkFile("createWorkFile");
    printf("%s\n", wkf1->name);
	printf("\n");

    /*Test pour wfts*/
	printf("wtfs : ");
    char* ch1 = wfts(wkf1);
    printf("%s\n", ch1);
    printf("\n");

	/*Test pour stwf*/
	printf("stwf : ");
    WorkFile* wkf2 = stwf(ch1);
    printf("%s %s %d\n", wkf2->name,wkf2->hash,wkf2->mode);
	printf("\n");
    /*libérer mes workfiles et chaine de caractère */
    libererWorkFile(wkf1);
    libererWorkFile(wkf2);
    free(ch1);

	/*Test pour initWorkTree*/
	printf("initWorktree_taille : ");
	WorkTree* wkt1 = initWorkTree();
	printf("%d\n",wkt1->size);
	printf("\n");

    /*Test pour appendWorkTree*/
	printf("appendWorktree : ");
	int res = appendWorkTree(wkt1,"File",NULL,0);
	printf("%d\n",res);
	printf("\n");

	/*Test pour inWorkTree*/
	printf("inWorktree : ");
	int valeur = inWorkTree(wkt1,"File");
	printf("%d\n",valeur);
    
	/*Test pour wtts*/
    printf(" wtts : ");
	char* ch2 = wtts(wkt1);
	printf("%s\n",ch2);
	printf("\n");

	/*Test pour wttf*/
	printf(" wttf : ");
	int d = wttf(wkt1,"file.txt");
	printf("%d\n",d);
	printf("\n");

	/*Test pour ftwt*/
	printf("ftwt : ");
	WorkTree* wkt2 = ftwt("file.txt");
	printf("%s\n",wtts(wkt2));

	/*libérer mes worktree et chaine de caractères*/
	libererWorkTree(wkt1);
	libererWorkTree(wkt2);
	free(ch2);
	 
    

    return 0;
}
