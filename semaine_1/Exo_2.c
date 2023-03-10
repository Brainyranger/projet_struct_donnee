#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exo_2.h"

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
	Cell *c;
	char *chaine1=s;
    char *chaine2="";
	while(*chaine1!='\0'){
		if(*chaine1=='|'){
            c = buildCell(chaine2);
            insertFirst(L,c);
            chaine2 = "";
            }
        *chaine2=*chaine2+*chaine1;
		*chaine1++;	
    }
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


int main(){
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
	ltof(L2, "chaine.txt");
	
	/*test pour ftol*/
	List *L3 = ftol("chaine.txt");
	char *ch7 = ltos(L3);
	printf("ftol : %s\n",ch7);
	free(ch7);

    /*libérer mes listes*/

	liberer_List(L1);
	liberer_List(L2);
	liberer_List(L3);

    return 0;

}