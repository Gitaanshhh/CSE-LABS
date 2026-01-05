/*
Compiler Design 
Name : Gitaansh H Bhuradia
Section : CSE B VI Sem
Roll no : 36
Registration no : 230905254
Lab Week 1 

Q2 : To reverse the file contents and store in another file. 
Also display the size of file using file handling function.
*/

//Program :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_LEN 100

int main(){
  FILE* fptr = NULL;
  
  char* filename = calloc(sizeof(char), FILENAME_LEN);
  
  printf("Enter name of file to copied: ");
  scanf("%s", filename);
  fptr = fopen(filename, "r");
  if(fptr==NULL){
    perror("File with given filename couldn't be opened for reading: ");
    perror(filename);
    exit(0);
  }

  int chars = 0;
  
  for(char c = getc(fptr); c != EOF; c = getc(fptr)){
    chars++; 
  }

  fseek(fptr, -2, SEEK_END);//go just before the end
  memset(filename, '\0', sizeof(filename));

  FILE* fptrForCopy = NULL;
  printf("Enter name of file to hold copied contents: ");
  scanf("%s", filename);
  fptrForCopy = fopen(filename, "w+");

  if(fptrForCopy == NULL){
    perror("File with given filename couldn't be opened for writing: ");
    perror(filename);
    exit(0);
  }

  for(int i = chars; i>=0; i--){
    char c = getc(fptr);
    putc(c, fptrForCopy);
    fseek(fptr, -2, SEEK_CUR);
  }
  
  fclose(fptr);
  free(filename);
  fptr = NULL;
  filename = NULL;

  printf("File succesfully copied in reverse. The file is %d bytes\n", sizeof(char)*chars);
  
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

$ ./Q2ReverseContents
Enter name of file to copied: sample.txt
Enter name of file to hold copied contents: sampleReverseCopy.txt
File succesfully copied in reverse. The file is 38 bytes

sampleReverseCopy.txt
----------------------
.eyb ,woN
lapinaM TIM ot emocleW
 ,iHiH
----------------------

*/
