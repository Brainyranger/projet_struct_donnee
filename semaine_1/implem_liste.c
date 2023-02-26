#include <stdio.h>
#include <stdlib.>
#include <string.h>


List* initList(){
    /*initialise une liste vide*/
    List *L = malloc(sizeof(List));
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
    if(L==NULL){
        *L = C;
    }
    else{
        C->next = *L;
        *L = C;
    }

}

char* ctos(Cell* c){
    /* retourne la chaîne de caract`eres qu’elle représente */
    return c->data;
}

char* ltos(List* L){
    /* transforme une liste en une chaîne de caractères avec le format suivant : chaîne1|chaîne2|chaîne3| */
    char *chaine = "";
    Cell *c = *L
    while(c->>next){
        chaine=chaine+c->data+"|";
    }
    return chaine+c->data
}


Cell* listGet(List* L, int i){
    /* renvoie le ième  ́elément d’une liste */
    int j=0;
    Cell *c=*L;
    if(L==NULL){
        return NULL;
    }

    while(j!=i && c!=NULL){
        j=j+1;
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
    c = buildCell(s);
    return c->data;

}

void ltof(List* L, char* path){
    /* permet d’écrire une liste dans un fichier */
    stol(L,path);
    FILE *f=fopen(path,"w");
    if (f==NULL){
        return;
    }
    cell *c=*L;
    while(c!=NULL){
        fprintf(f,"%s\n",c->data);
        c=c->next;
    }
    fclose(f);

}

List* ftol(char* path){
    /* permet de lire une liste enregistrée dans un fichier */
    FILE *f = fopen(path,"r");
    if (f==NULL){
        printf("Erreur lors de l'ouverture du ficher\n");
        return NULL;
    }
    char ligne[256];
    for (int i = 0;i<256;i++){
        if (fget(ligne,256,f)!=NULL){
            printf("%s",ligne);
            break;
        }
    }
    fclose(f);
}