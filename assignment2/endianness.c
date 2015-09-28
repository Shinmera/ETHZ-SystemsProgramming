#include <stdio.h>

int is_little_endian(){
  unsigned int one = 1;
  char *byte = (char*) &one;
  return (int)*byte;
}

int main(){
  if(is_little_endian()){
    printf("LE");
  }else{
    printf("BE");
  }
  
  return 0;
}
