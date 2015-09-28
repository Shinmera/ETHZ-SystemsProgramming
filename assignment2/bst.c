#include <stdbool.h>
#include <stdlib.h>
#include "bst.h"

struct Cell{
  int value;
  cell *left;
  cell *right;
};

cell *make_cell(int value, cell *left, cell *right){
  cell *new_cell = malloc(sizeof (*new_cell));
  new_cell->value = value;
  new_cell->left = left;
  new_cell->right = right;

  return new_cell;
}

void insert(int value, cell *tree){
  cell *new_cell = make_cell(value, NULL, NULL);
  while(true){
    if(value <= tree->value){
      if(tree->left != NULL){
        tree = tree->left;
      }else{
        tree->left = new_cell;
        break;
      }
    }else{
      if(tree->right != NULL){
        tree = tree->right;
      }else{
        tree->right = new_cell;
        break;
      }
    }
  }
}

cell *lookup(int value, cell *tree){
  while(tree != NULL){
    if(tree->value == value)
      return tree;
    if(tree->value < value)
      tree = tree->right;
    if(value < tree->value)
      tree = tree->left;
  }
  return NULL;
}

bool delete(int value, cell *tree){
  while(tree != NULL){
    if(tree->value == value){
      free(tree);
      return true;
    }
    if(tree->value < value)
      tree = tree->right;
    if(value < tree->value)
      tree = tree->left;
  }
  return false;
}

void inorder(void (*func)(int), cell *tree){
  if(tree->left != NULL)
    inorder(func, tree->left);
  func(tree->value);
  if(tree->right !=NULL)
    inorder(func, tree->right);
}
