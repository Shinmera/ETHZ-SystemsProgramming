#include "complex.h"
#include "complex_set.h"

complex_set *alloc_set(complex c_arr[], int length){
  complex_set set = malloc(sizeof(complex_set));
  if(set == NULL) return NULL;

  set->length = length;
  set->points = malloc(length * sizeof(complex));

  for(int i=0; i<length; ++i){
    set->points[i] = c_arr[i];
  }

  return set;
}

void free_set(complex_set *set){
  free(set->points);
  free(set);
}
