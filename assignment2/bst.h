#include <stdbool.h>
#include <stdlib.h>

struct Cell;
typedef struct Cell cell;

cell *make_cell(int value, cell *left, cell *right);
void insert(int value, cell *tree);
cell *lookup(int value, cell *tree);
bool delete(int value, cell *tree);
void inorder(void (*f)(int), cell *tree);
