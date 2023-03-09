#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int hashFile(char * source, char *dest) {
	char cmd[100];
	sprintf(cmd, "sha256sum %s > %s", source,dest);
	system(cmd);
	
	return 0;
}

char* sha256file(char* file){
    static char template [] = "/tmp/tempXXXXXX" ;
    char fname[1000];
    strcpy (fname,template) ;
    int fd = mkstemp (fname);

    hashFile(file, fname);
    FILE* f= fopen(fname,"r");
    char *cmd1= malloc(sizeof(char)*1000);
    fscanf(f," %s",cmd1);

    char cmd2[1000];
    sprintf(cmd2,"rm -rf %s",fname);
    system(cmd2);

    fclose(f);
    return cmd1;
}


int main(){

	hashFile("main.c", "file.tmp");
	char *hash = sha256file("main.c");
	printf("%s\n", hash);
	free(hash);
	
	return 0;
}

	