#ifndef Work_H_
#define Work_H_


typedef struct {
    char * name;
    char * hash;
    int mode ;
} WorkFile;

typedef struct {
    WorkFile * tab;
    int size;
    int n;
} WorkTree;

WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);
WorkTree* initWorkTree();
int inWorkTree(WorkTree* wt, char* name);
int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode);
char* wtts(WorkTree* wt)
int wttf(WorkTree* wt, char* file);
WorkTree* ftwt(char* file);
void libererWorkFile(WorkFile* wf);
void libererWorkTree(WorkTree* wkt);

#endif