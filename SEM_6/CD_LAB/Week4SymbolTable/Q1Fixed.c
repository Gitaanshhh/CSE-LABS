#include <stdio.h>
#include <string.h>
#include "getNextToken.h"

typedef struct {
    char lexeme[20];
    char type[10];
    int size;
    char scope;     // 'G' or 'L'
} Symbol;

typedef struct {
    char fname[20];
    Symbol locals[MAX];
    int count;
} LocalTable;

Symbol globalTable[MAX];
int gCount = 0;

LocalTable localTables[MAX];
int fCount = 0;


int sizeOf(char *type) {
    if (!strcmp(type,"int")) return 4;
    if (!strcmp(type,"float")) return 4;
    if (!strcmp(type,"char")) return 1;
    return 0;
}

void addGlobal(char *name, char *type) {
    strcpy(globalTable[gCount].lexeme, name);
    strcpy(globalTable[gCount].type, type);
    globalTable[gCount].size = 0;     // function
    globalTable[gCount].scope = 'G';
    gCount++;
}

void addLocal(char *name, char *type) {
    LocalTable *lt = &localTables[fCount-1];
    strcpy(lt->locals[lt->count].lexeme, name);
    strcpy(lt->locals[lt->count].type, type);
    lt->locals[lt->count].size = sizeOf(type);
    lt->locals[lt->count].scope = 'L';
    lt->count++;
}

int main() {
    FILE *fp = fopen("test.c","r");
    if (!fp) return 1;

    Token t, prev;
    char currType[10] = "";
    int inParams = 0;

    prev.type = END;

    while ((t = getNextToken(fp)).type != END) {

        if (t.type == KEYWORD)
            strcpy(currType, t.lexeme);

        if (t.type == IDENTIFIER && prev.type == KEYWORD) {

            Token next = getNextToken(fp);

            /* function */
            if (next.lexeme[0] == '(') {
                addGlobal(t.lexeme, currType);
                strcpy(localTables[fCount].fname, t.lexeme);
                localTables[fCount].count = 0;
                fCount++;
                inParams = 1;
            }
            /* variable / parameter */
            else {
                addLocal(t.lexeme, currType);
            }

            prev = next;
            continue;
        }

        if (t.type == SPECIAL && t.lexeme[0] == ')')
            inParams = 0;

        prev = t;
    }

    fclose(fp);

    printf("\nGLOBAL SYMBOL TABLE\n");
    printf("Name\tType\n");
    for (int i = 0; i < gCount; i++)
        printf("%s\t%s\n", globalTable[i].lexeme, globalTable[i].type);

    for (int i = 0; i < fCount; i++) {
        printf("\nLOCAL SYMBOL TABLE : %s\n", localTables[i].fname);
        printf("Name\tType\tSize\n");
        for (int j = 0; j < localTables[i].count; j++) {
            Symbol *s = &localTables[i].locals[j];
            printf("%s\t%s\t%d\n", s->lexeme, s->type, s->size);
        }
    }

    return 0;
}
