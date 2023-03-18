#ifndef Exos_H_
#define Exos_H_

typedef struct cell{
char *data ;
struct cell *next ;
}Cell;

typedef Cell *List;

int hashFile(char* source, char* dest);
char* sha256file(char* file);
List* initList();
Cell* buildCell(char* ch);
void insertFirst(List *L, Cell* C);
char* ctos(Cell* c);
char* ltos(List* L);
Cell* listGet(List* L, int i);
Cell* searchList(List* L, char* str);
List* stol(char* s);
void ltof(List* L, char* path);
List* ftol(char* path);
void liberer_Cell(Cell* c);
void liberer_List(List* L);
List* listdir(char* root_dir);
int file_exists(char *file);
void cp(char *to, char *from);
char* hashToPath(char* hash);
void blobFile(char* file);
#endif
