#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
void main() {

    FILE *fp = fopen("s1.txt", "rb");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize, sizeof(char));
    long bytesread = fread(buffer, 1, filesize, fp);
    if (bytesread != filesize) {
        perror(fread);
    }
}