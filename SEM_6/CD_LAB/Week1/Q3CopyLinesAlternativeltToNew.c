/*
Compiler Design 
Name : Gitaansh H Bhuradia
Section : CSE B VI Sem
Roll no : 36
Registration no : 230905254
Lab Week 1 

Q3 : That merges lines alternatively from 2 files and stores it in a resultant file
*/

//Program :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_LEN 100
#define NEW_FILE "result.txt"

int main(){
  FILE* fptr1 = NULL;
  FILE* fptr2 = NULL;
  FILE* fptr3 = NULL;
  
  char* filename = calloc(sizeof(char), FILENAME_LEN);

  printf("Enter name of the first file to be copied from: ");
  scanf("%s", filename);
  fptr1 = fopen(filename, "r");
  if(fptr1==NULL){
    perror("File with given filename couldn't be opened for reading: ");
    perror(filename);
    exit(0);
  }
  
  memset(filename, '\0', sizeof(filename));
  
  printf("Enter name of the second file to be copied from: ");
  scanf("%s", filename);
  fptr2 = fopen(filename, "r");
  if(fptr2==NULL){
    perror("File with given filename couldn't be opened for reading: ");
    perror(filename);
    exit(0);
  }

  fptr3 = fopen(NEW_FILE, "w+");
  if(fptr3==NULL){
    perror("File with given filename couldn't be opened for writing: ");
    perror(filename);
    exit(0);
  }

  int turn = 0, done=0;
  while(1){
    char c='\0';
    if(turn==0){
      c = getc(fptr1);
      if(c==EOF)done++;
      else if(c=='\n'){
        putc(c, fptr3);
        turn=1;
      }
      else putc(c, fptr3);
    }
    else{
      c = getc(fptr2);
      if(c==EOF)done++;
      else if(c=='\n'){
        putc(c, fptr3);
        turn=0;
      }
      else putc(c, fptr3);
    }
    if(done==2)break; 
  }

  printf("Copied succesfully into result.txt!\n");

  fclose(fptr1);
  fclose(fptr2);
  fclose(fptr3);
  free(filename);
  fptr1 = NULL;
  fptr2 = NULL;
  fptr3 = NULL;
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

sampleReverseCopy.txt
----------------------
.eyb ,woN
lapinaM TIM ot emocleW
 ,iHiH
----------------------

$ ./Q3CopyLinesAlternativeltToNew
Enter name of the first file to be copied from: sample.txt
Enter name of the second file to be copied from: sampleReverseCopy.txt
Copied succesfully into result.txt!

result.txt
----------------------
Hi,
.eyb ,woN
Welcome to MIT Manipal
lapinaM TIM ot emocleW
Now, bye.
 ,iHiH
----------------------

*/
