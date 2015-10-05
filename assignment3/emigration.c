#include <stdio.h>
#include <stdlib.h>

// Usually I'd love to do a general case CSV reader
// that is flexible and usable for all kinds of formats
// and include other functions to perform generic ops
// on the data records, but doing anything flexible in
// C is such a pain in the ass that I won't bother.
//
// Most specific solution ahead!

void print_record(char *label, int count){
  printf("%-25s %25d\n", label, count);
}

void skip_line(FILE *file_descriptor){
  fscanf(file_descriptor, "%*[^\n]\n");
}


int main(){
  FILE *file_descriptor = fopen("stateoutflow0708.txt", "r");
  if(file_descriptor == NULL)
    return 1;

  int total = 0;
  int origin = 0;
  char name[25];
  int count = 0;

  // Skip header
  skip_line(file_descriptor);

  printf("STATE                                         COUNT\n");
  printf("===================================================\n");
  while(fscanf(file_descriptor, " \"%2d\" \"%*3d\" \"%*2d\" \"%*3d\" \"%*2c\" \"%25[^\"]\" %*d %*d %d",
               &origin, name, &count) != EOF){
    
    if(origin == 25){
      print_record(name, count);
      total += count;
    }
  }
  printf("===================================================\n");
  print_record("TOTAL", total);
  
  fclose(file_descriptor);
  return 0;
}
