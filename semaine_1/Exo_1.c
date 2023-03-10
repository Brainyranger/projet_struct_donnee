#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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


int main(){

	hashFile("main.c", "file.tmp");
	char *hash = sha256file("main.c");
	printf("%s\n", hash);
	free(hash);
	
	return 0;
}

	