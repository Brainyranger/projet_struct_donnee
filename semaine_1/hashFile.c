#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashFile(char* source, char* dest){
	char buffer[100];
	sprintf(buffer,"cat %s | sha256sum > %s", source,dest);
	system(buffer);
	return 1;
}

char * sha256file(char *file) {

	static char template[] = "/tmp/myfileXXXXXX";
	char fname[1000];
	strcpy(fname, template);
	int fd = mkstemp(fname);
	
	hashFile(file,fname);
	
	FILE* f = fopen(fname,"r");
	
	char* buffer = malloc(sizeof(char)*65); // car 256 bites donc 64 +1
	fgets(buffer,65,f);
	
	fclose(f);
	
	char buffer2[100];
	sprintf(buffer2,"rm %s", fname);
	system(buffer2);
	
	return buffer;
}

int main(){

	system("ls");
	printf("\n");
	hashFile("test1.txt","test2.txt");
	
	char* hash = sha256file("test1.txt");
	printf("%s\n", hash);
	
	return 0;
}
