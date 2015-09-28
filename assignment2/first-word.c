#include <stdio.h>
#include <stdlib.h>

struct word{
  int length;
  char *string;
};

struct word first_word(char *string){
  // Find range
  int start = -1;
  int end = -1;
  for(int i=0; string[i]!=0; ++i){
    if(string[i] == ' '){
      if(start < 0){
        start = i+1;
        end = i;
      }else{
        break;
      }
    }
    if(0 < start){
      ++end;
    }
  }
  // Copy word
  struct word word = {end-start, (char*)malloc(end-start)};
  for(int i=start; i<end; ++i){
    word.string[i-start] = string[i];
  }
  return word;
}
  
int main(){
  char string[64];
  printf("Enter a string (max 64 chars): ");
  if (fgets(string, sizeof string, stdin)) {
    struct word word = first_word(string);
    printf("The first word is %d characters long: %.*s\n", word.length, word.length, word.string);
    // Out string is malloced, free it.
    free((&word)->string);    
    return 0;
  }
  return 1;
}
