#include <dirent.h>

List* listdir(char* root_dir){
    DIR * dp = opendir (root_dir);
    struct dirent * ep ;
    List *L =initList();
    if(dp!= NULL){
        while (( ep = readdir (dp) ) != NULL ){
            Cell *c = buildCell(ep->d_name);
            insertFirst(L,c);
        }
    }
    return L;
}

int file_exists(char *file){

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

    
