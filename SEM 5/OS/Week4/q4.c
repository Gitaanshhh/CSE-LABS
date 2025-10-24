#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc < 3) exit(1);
    FILE *src = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "w");
    if(!src || !dest) exit(1);
    int ch;
    while((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
    return 0;
}
