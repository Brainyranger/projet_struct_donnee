#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "Exo_1.h"
#include "Exo_2.h"

List* listdir(char* root_dir){
    /*renvoie une liste contenant le noms des fichiers et répertoires qui s’y trouvent*/
    DIR *dp = opendir (root_dir);
    struct dirent *ep;
    List *L =initList();
    if(dp!= NULL){
        while ((ep=readdir(dp)) != NULL){
            Cell *c = buildCell(ep->d_name);
            insertFirst(L,c);
        }
    }
    return L;
}

int file_exists(char *file){
    /*retourne 1 si le fichier existe dans le répertoire courant et 0 sinon.*/
    
    static char template [] = "/tmp/tempXXXXXX" ;
    char fname[1000];
    strcpy (fname,template) ;
    int fd = mkstemp ( fname );
    
    char cmd1[1000];
    sprintf(cmd1,"pwd>%s",fname);
    system(cmd1);

    char cmd2[1000];    
    FILE* f= fopen(fname,"r");
    fgets(cmd2,1000,f);

    fclose(f);
    sprintf(cmd1,"rm -rf %s",fname);

    List *L= listdir(cmd2);
    Cell* c = searchList(L,file);

    if(c!=NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void cp(char *from, char *to){
    /*copie le contenu d’un fichier vers un autre, en faisant une lecture ligne par ligne du fichier source*/

    if (file_exists(from) == 0)
        return;
    
    // Ouverture
    FILE* f = fopen(from, "r");
    if (f == NULL) return;
    FILE* t = fopen(to, "w");
    if (t == NULL){
        fclose(f);
        return;
    }

    char buffer[256];
    char* res = fgets(buffer, 256, f);
    while(res){
        fprintf(t, "%s", buffer);
        res = fgets(buffer, 256, f);
    }

    fclose(f);
    fclose(t);

}

char* hashToPath(char* hash){
    /*retourne le chemin d’un fichier à partir de son hash*/

    char* chemin = (char*) malloc(100*sizeof(char));
    chemin[0] = hash[0];
    chemin[1] = hash[1];
    chemin[2] = '/';
    int i = 2;
    while(hash[i] != '\0'){
        chemin[i+1] = hash[i];
        i++;
    }
    chemin[i+1] = '\0'; 
    return chemin;
}

void blobFile(char* file){
    /*enregistre un instantané du fichier donn ́e en entrée*/

    char *hash = sha256file(file);
    char *chemin = hashToPath(hash);
    printf("Le chemin : %s\n", chemin);
    char dir[3] = {chemin[0], chemin[1], '\0'};
    if (! file_exists(dir)){
        char template[10];
        sprintf(template, "mkdir %s", dir);
        system(template);
    }
    cp(file, chemin);

    free(hash);
    free(chemin);
}
   
