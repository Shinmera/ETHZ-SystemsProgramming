struct Complex{
  double r,i;
};
typedef struct Complex complex;

complex c(double r, double i);
complex add(complex a, complex b);
complex subtract(complex a, complex b);
complex multiply(complex a, complex b);
complex divide(complex a, complex b);
int print_complex(complex c);
