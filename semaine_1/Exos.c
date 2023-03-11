#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Exos.h"

int hashFile(char * source, char *dest) {
    /*  ́etant donné le chemin de deux fichiers, calcule le hash du contenu du premier fichier et l’ ́ecrit dans le deuxième fichier.*/
    
	char buffer[100];
	sprintf(buffer, "sha256sum %s > %s", source,dest);
	system(buffer);
	
	return 0;
}

char* sha256file(char* file){
    /*renvoie une chaîne de caractères contenant le hash du fichier donné en paramètre*/

    static char template [] = "/tmp/tempXXXXXX" ;
    char fname[1000];
    strcpy (fname,template) ;
    int fd = mkstemp (fname);

    hashFile(file, fname);
    FILE* f= fopen(fname,"r");
    char *buffer1= malloc(sizeof(char)*1000);
    fscanf(f," %s",buffer1);

    char buffer2[1000];
    sprintf(buffer2,"rm -rf %s",fname);
    system(buffer2);

    fclose(f);
    return buffer1;
}

List* initList(){
    /*initialise une liste vide*/
    List *L = malloc(sizeof(List));
    *L = NULL;
    return L;

}

Cell* buildCell(char* ch){
    /* permet d’allouer et de retourner une cellule de la liste */
    Cell* c = malloc(sizeof(Cell));
    c->data = strdup(ch);
    c->next = NULL;
    return c;
    }

void insertFirst(List *L, Cell* C){
    /* permet d’ajouter un  ́elément en tête d’une liste */
    
    C->next = *L;
    *L = C;

}

char* ctos(Cell* c){
    /* retourne la chaîne de caractères qu’elle représente */
    if(c ==NULL) return NULL;
	char *ch = strdup(c->data);
	return ch;

}

char* ltos(List* L){
    /* transforme une liste en une chaîne de caractères avec le format suivant : chaîne1|chaîne2|chaîne3| */
    Cell *c = *L;
    char *buffer = malloc(sizeof(char)*1000);
    strcpy(buffer,ctos(c));
	c= c->next;
    while(c){
        strcat(buffer,"|");
        strcat(buffer, ctos(c));
        c = c->next;
    }
    strcat(buffer,"|");
    return buffer;
}


Cell* listGet(List* L, int i){
    /* renvoie le ième  ́elément d’une liste */
    int j=0;
    Cell *c=*L;
    if(L==NULL){
        return NULL;
    }

    while(j!=i && c!=NULL){
        j++;
        c=c->next;
    }
    return c;   

}

Cell* searchList(List* L, char* str){
    /* recherche un  ́elément dans une liste à partir de son contenu et renvoie une référence vers lui ou NULL s’il n’est pas dans la liste */

    Cell *c = *L;

    while(c){
        if(strcmp(c->data,str)==0){
            return c;
        }
        c=c->next;
    }
    return NULL;
}

List* stol(char* s){
    /* permet de transformer une chaîne de caracteres representant une liste en une liste chaınée */

	List *L=initList();
	char* ch = (char*)malloc(sizeof(char)*1000);
	int i = 0;
	int j = 0;
	while(s[i] != '\0'){
		if(s[i] != '|'){
			ch[j] = s[i];
			j++;
		}else{
			ch[j] = '\0';
			insertFirst(L,buildCell(ch));
			free(ch);
			ch = (char*)malloc(sizeof(char)*1000);
			j = 0;
		}
		i++;
	}
	free(ch);
	return L;



}

void ltof(List* L, char* path){
    /* permet d’écrire une liste dans un fichier */
    FILE *f=fopen(path,"w");
    if (f==NULL){
        return;
    }
    Cell *c=*L;
    while(c!=NULL){
        fprintf(f,"%s\n",c->data);
        c=c->next;
    }
    fclose(f);

}

List* ftol(char* path){
    /* permet de lire une liste enregistrée dans un fichier */
    FILE *f = fopen(path , "r");
    List *L = initList();
    char buffer[1000];
    while(fgets(buffer,1000,f)!=NULL){
        Cell *c=buildCell(buffer);
        insertFirst(L,c);
    }
    fclose(f);
    return L;

}
/*ajout des fonctions utiles*/

void liberer_Cell(Cell* c){
    /*libère une cellule*/
	free(c->data);
	free(c);
}

void liberer_List(List* L){
    /*libère une liste*/
	Cell* c = *L;
	Cell* tmp;
	while(c){
		tmp = c;
		c = c->next;
		liberer_Cell(tmp);
	}
	free(L);
}


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
    
    hashFile("main.c", "file.tmp");
	char *hash = sha256file("main.c");
	printf("%s\n", hash);
	free(hash);
	
    /*création de mes chaînes de caractères*/
    char *ch1_1 = "chaine1";
    char *ch1_2 = "chaine2";
    char *ch1_3 = "chaine3";
    /*création de ma liste*/
	List *L1 = initList();
    /*création de mes cellules*/
	Cell *c1 = buildCell(ch1_1);
    Cell *c2 = buildCell(ch1_2);
    Cell *c3 = buildCell(ch1_3);
    insertFirst(L1,c3);
    insertFirst(L1,c2);
    insertFirst(L1,c1);

	/*test pour ctos*/ 
	char *ch2 = ctos(c1);
	printf("ctos : %s\n",ch2);
	free(ch2);
	
	/*test pour ltos*/
	char *ch3 = ltos(L1);
	printf("ltos : %s\n",ch3);
	free(ch3);

	/*test de listGet*/
	char *ch_get = ctos(listGet(L1,1));
	printf("listGet : %s\n",ch_get);
	free(ch_get);

	/*test pour searchList*/
	Cell *c4 = searchList(L1,"chaine3");
	char *ch4 = ctos(c4);
	printf("searchList : %s\n",ch4);
	free(ch4);
	
	/*test pour stol*/
	char *ch5 = "table|de|hachage|";
	List *L2 = stol(ch5);
	char *ch6 = ltos(L2);
	printf("stol : %s\n",ch6);
	free(ch6);
	
	/*test pour ltof*/
	ltof(L2, "Exo_2.txt");
	
	/*test pour ftol*/
	List *L3 = ftol("Exo_2.txt");
	char *ch7 = ltos(L3);
	printf("ftol : %s",ch7);
	free(ch7);

    /*libérer mes listes*/

	liberer_List(L1);
	liberer_List(L2);
	liberer_List(L3);

    /*test pour Listdir*/
    List *L = listdir(".");
    char *str = ltos(L);
    if (str != NULL){
        printf("%s\n", str);
        free(str);
    }
    /*test pour file_exist*/
    printf("Le fichier Exo_3.c existe : %d\n", file_exists("Exo_3.c"));
    
    /*test pour cp*/
    cp("Exo_3.c", "Exo_3.txt");
    
    /*test hashtofile*/
    char* path_file_tmp = hashToPath("c822da1af674a4931200d698c1adbe22aa850cd72215d6f14fcebfa70aeb0b67");
    printf("Chemin du hash : %s\n", path_file_tmp);
    free(path_file_tmp);

    /*test blobFile*/
    blobFile("Exo_3.txt");
    

    liberer_List(L);

    return 0;

}