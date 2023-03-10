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
    
    int i = 0;
	system("pwd > chemin.txt");
	FILE* f = fopen("chemin.txt","r");
	if(f == NULL){
		return i;
	}
	char ligne[256];
	fgets(ligne,256,f);
	
	List  *L = listdir(ligne);
	fclose(f);
	system("rm chemin.txt");
	
	if(searchList(L,file) != NULL){
		i = 1;
	}
	Cell *tmp = NULL;
	Cell *c = *L;
	while(c){
		tmp = c->next;
		free(c->data);
		free(c);
		c = tmp;
	}
	free(L);
	return i;
}

void cp(char *from, char *to){
    /*copie le contenu d’un fichier vers un autre, en faisant une lecture ligne par ligne du fichier source*/

    if (file_exists(from) == 0)
        return;
    

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
   


int main(){
    /*test Listdir*/
    //List *L = listdir(".");
    //char *str = ltos(L);
    //if (str != NULL){
       // printf("%s\n", str);
      //  free(str);
   // }
    /*test file_exist*/
    //printf("Le fichier Exo_3.c existe : %d\n", file_exists("Exo_3.c"));
    
    /*test cp*/
    cp("Exo_3.c", "Exo_3.txt");
    
    /*test hashtofile*/
    char* path_file_tmp = hashToPath("c822da1af674a4931200d698c1adbe22aa850cd72215d6f14fcebfa70aeb0b67");
    printf("Chemin du hash : %s\n", path_file_tmp);
    free(path_file_tmp);

    /*test blobFile*/
    blobFile("Exo_3.txt");
    

    //liberer_List(L);

    return 0;


}