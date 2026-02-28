/*
Recursive descent parser for the following simple grammar
S → aAcBe
A → Ab|b
B → d


Removing left recursion from A → Ab|b gives
A → bA'
A' → bA' | 𝜖
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void A();
void Aprime();
void B();

void invalid() {
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid() {
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void S() {
    if (str[curr] == 'a') {
        curr++;
        A();
        if (str[curr] == 'c') {
            curr++;
            B();
            if (str[curr] == 'e') {
                curr++;
                return;
            }
            else invalid(); 
        }
        else invalid();
    }
    else invalid();
}

void A() {
    if (str[curr] == 'b') {
        curr++;
        Aprime();
        return;
    }
    else invalid();
}


void Aprime() {
    if (str[curr] == 'b') {
        curr++;
        Aprime();
        return;
    }    
}

void B() {
    if (str[curr] == 'd') {
        curr++;
        return;
    }
    else invalid();
}

int main() {
    printf("Enter String: ");
    scanf("%s", str);
    S();
    if (str[curr] == '\0')
        valid();
    else
        // printf("%c\n", str[curr]);s
        invalid();
}