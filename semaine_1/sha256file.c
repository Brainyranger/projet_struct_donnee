#include <stdio.h>
#include <stdlib.h>

int hashFile(char * source, char * dest) {
    int res; 

    //Fichier source
    FILE* f1 = fopen("source.txt", "w");
    fprintf(f1, "%s", source);
    fclose(f1);

    //Fichier de destination
    FILE* f2 = fopen("dest.txt", "w");
    fprintf(f2, "%s", dest);
    fclose(f2);

    //Commande de hash
    system("cat source.txt | cat | sha256sum > dest.txt");
    system("rm source.txt; cat dest.txt");

    //On garde la valeur dans dest.txt pour retourner
    //On copie ce qu'on a trouvé dans dest.txt dans le fichier char* dest
    FILE* f3 = fopen("dest.txt", "r");
    FILE* f4 = fopen(dest, "w");
    fscanf(f3, "%d", &res);
    fprintf(f4,"%d", res);
    fclose(f3);
    fclose(f4);
    
    return res;   
}

int main() {
    hashFile("file_src.txt", "file_dest.txt");
    return 0;
}