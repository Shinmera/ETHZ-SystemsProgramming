#include <stdio.h>
#include <stdlib.h>

// tsk tsk tsk, the example code
// is not even closing the FDs.

int is_linebreak(char c){
  return (c == '\n'
          || c == '\r');
}

int is_whitespace(char c){
  return (c == ' '
          || is_linebreak(c)
          || c == '\t'
          || c == '\v');
}

int main(int argc, char* argv[]){
  FILE *file_pointer = NULL;
  int file_count = --argc;
  int arg_counter = 1;
  char *current_file = "";

  if(file_count == 0){
    file_pointer = stdin;
    file_count++;
  }else{
    current_file = argv[arg_counter++];
    file_pointer = fopen(current_file, "r");
  }
    
  while(file_count > 0){
    if(file_pointer == NULL){
      fprintf(stderr, "Unable to open input\n");
      exit(-1);
    }

    unsigned long characters=0, words=0, lines=0;
    char c='\0', prev='\0';
    while((c = getc(file_pointer)) != EOF){
      ++characters;
      if(is_linebreak(c)) ++lines;
      if(!is_whitespace(prev)
         && is_whitespace(c))
        ++words;
      prev = c;
    }
    // Make sure to count the last one.
    if(prev != '\0' && !is_whitespace(prev))++words;

    printf("%ld %ld %ld %s\n", lines, words, characters, current_file);
    
    file_count--;
    if (file_count > 0){
      current_file = argv[arg_counter++];
      file_pointer = fopen(current_file, "r");
    }
  }
  return 0;
}
