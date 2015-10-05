#include <stdio.h>
#include "complex.h"

complex c(double r, double i){
  complex c = {
    .r = r, .i = i
  };
  return c;
}

complex add(complex a, complex b){
  return c(a.r+b.r, a.i+b.i);
}

complex subtract(complex a, complex b){
  return c(a.r-b.r, a.i-b.i);
}

complex multiply(complex a, complex b){
  return c((a.r*b.r)-(a.i*b.i), (a.r*b.i)+(a.i*b.r));
}

complex divide(complex a, complex b){
  double div = b.r*b.r + b.i*b.i;
  return c(((a.r*b.r)+(a.i*b.i))/div,
           ((a.i*b.r)-(a.r*b.i))/div);
}

int print_complex(complex c){
  return printf("%f+%fi", c.r, c.i);
}
