/*
Compiler Design 
Name : Gitaansh H Bhuradia
Section : CSE B VI Sem
Roll no : 36
Registration no : 230905254
Lab Week 1 

Q1 : To count the number of lines and characters in a file.
*/

//Program :

#include <stdio.h>
#include <stdlib.h>

#define FILENAME_LEN 100

int main(){
  FILE* fptr = NULL;
  
  char* filename = calloc(sizeof(char), FILENAME_LEN);

  printf("Enter file name: ");
  scanf("%s", filename);
  
  fptr = fopen(filename, "r");
  
  if(fptr==NULL){
    perror("File with given filename couldn't be opened for reading: ");
    perror(filename);
    exit(0);
  }

  int lines = 0, chars = 0;

  for(char c = getc(fptr); c != EOF; c = getc(fptr)){
    if(c=='\n')
      lines++;
    chars++; 
  }
  
  printf("The number of charecters in given file { %s } : %d\nThe number of lines in given file { %s } : %d\n", filename, chars, filename, lines);

  fclose(fptr);
  free(filename);
  fptr = NULL;
  filename = NULL;
  
  return 0;
}

/*

Sample input and Output : 

sample.txt
----------------------
Hi,
Welcome to MIT Manipal
Now, bye.
----------------------

$ ./Q1CountLinesAndChars
Enter file name: sample.txt
The number of charecters in given file { sample.txt } : 38
The number of lines in given file { sample.txt } : 3

*/
