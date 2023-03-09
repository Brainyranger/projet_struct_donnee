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

char *sha256file(char *file) {
	static char template[] = "/tmp/myfileXXXXXX";
	char tmp[1000];
	strcpy(tmp, template);
	int fdTmp = mkstemp(tmp);
	hashFile(file, tmp);
	char *hash = malloc(sizeof(char) * 64);
	read(fdTmp, hash, 64);
	close(fdTmp);
	char rm[1003];
	sprintf(rm, "rm %s", tmp);
	system(rm);
	return hash;
}

int main(){

	hashFile("main.c", "file.tmp");
	char *hash = sha256file("main.c");
	printf("%s\n", hash);
	free(hash);
	
	return 0;
}

	