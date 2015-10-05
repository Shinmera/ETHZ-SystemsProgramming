#include <stdio.h>
#include "complex.h"

void prt(char *string, complex c){
  printf(string);
  print_complex(c);
  printf("\n");
}

int main(){  
  complex a = c(10, 5);
  complex b = c(2, 3);

  prt("A: ", a);
  prt("B: ", b);
  prt("A+B: ", add(a, b));
  prt("A-B: ", subtract(a, b));
  prt("A*B: ", multiply(a, b));
  prt("A/B: ", divide(a, b));
  
  return 0;
}
