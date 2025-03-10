/*
1) Write a program to implement Horspool’s algorithm for String Matching and 
find the number of key comparisons in successful search and unsuccessful search.
*/

#include<stdio.h>

#define ALPHABET_SIZE 256  // Number of possible characters (extended ASCII)

int opCount = 0;

void printArr(int arr[], int n){
    for (int i = 0; i < n; i++)
          printf("%c ", arr[i]);
      printf("\n");
  }

void createBadShiftTable(char shiftTable[], char pattern[], int m){
    for (int i = 0; i < ALPHABET_SIZE; i++)
        shiftTable[i] = m;  // Default shift = length of the pattern

    // Set the shift for characters that appear in the pattern
    for (int i = 0; i < m - 1; i++)
        shiftTable[(unsigned char) pattern[i]] = m - i - 1;
}

int main(){
    int n, m;

    printf("Enter the number of Elements in the Text : ");
    scanf("%d",&n);

    char arr[n];
    printf("Enter the Elements : ");
    for(int i = 0; i < n; i++)
      scanf("%c",&arr[i]);
    
    printf("Enter the number of Elements in the Pattern : ");
    scanf("%d",&n);

    char subStr[m];
    printf("Enter the Elements : ");
    for(int i = 0; i < m; i++)
      scanf("%c",&subStr[i]);

    char shiftTable[ALPHABET_SIZE];
    createBadShiftTable(shiftTable, subStr, m);
    
    printf("It took %d Operations.", opCount);
    return 0;
}