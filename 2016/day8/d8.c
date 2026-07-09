#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct {
    int row;
    int col;
    UT_hash_handle hh;
} Point;

Point *grid = NULL;

void main() {
    int ROWMAX = 3;
    int COLMAX = 7;
    int row = 0;
    int col = 0;
    int grid[3][7];
    FILE *fp = fopen("s1.txt", "rb");
    long filesize = 0;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize + 1, sizeof(char));
    long bytesread = fread(buffer, sizeof(char), filesize, fp);
    if (bytesread != filesize) {
        perror("fread");
    }
    char *token;
    long fileindex = 0;
    while (fileindex < filesize) {
    }
}