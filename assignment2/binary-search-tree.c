#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void printi(int value){
  printf("%i ", value);
}

int main(){
  cell *root = make_cell(5, NULL, NULL);
  insert(3, root);
  insert(7, root);
  insert(1, root);
  insert(2, root);
  insert(4, root);
  insert(6, root);
  
  inorder(printi, root);
  
  return 0;
}
