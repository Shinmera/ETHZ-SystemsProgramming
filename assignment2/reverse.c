#include <stdio.h>

void swap_uint(unsigned int *a, unsigned int* b){
  unsigned int t = *a;
  *a = *b;
  *b = t;
}

void reverse_array(unsigned int *array, unsigned int length){
  for(unsigned int i=0; i<length/2; ++i){
    swap_uint(&array[i], &array[length-i-1]);
  }
}

int main(){
  printf("Number of numbers: ");
  unsigned int length;
  scanf("%u", &length);

  unsigned int array[length];
  printf("Enter the numbers: ");
  for(unsigned int i=0; i<length; ++i){
    scanf("%u", &array[i]);
  }

  reverse_array(array, length);

  for(unsigned int i=0; i<length; ++i){
    printf("%u ", array[i]);
  }
  return 0;
}
