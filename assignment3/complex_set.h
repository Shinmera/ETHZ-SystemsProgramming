#include "complex.h"

struct Complex_set {
  int length;
  struct complex *points;
};
typedef struct Complex_set complex_set;

complex_set *alloc_set(complex c_arr[], int length);
void free_set(complex_set *set);
