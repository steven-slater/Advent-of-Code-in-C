#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "uthash.h"

typedef struct {
    int row;
    int col;
    bool on;
    UT_hash_handle hh;
} Point;

Point *grid = NULL;

int main() {
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
    fclose(fp);
    char *token;
    long fileindex = 0;
    int lineindex = 0;
    char temp[256];
    int linectr = 0;

    while (fileindex < filesize) {
        char *line = calloc(512, sizeof(char));
        int lineindex = 0;
        while (buffer[fileindex] == '\r' || buffer[fileindex] == '\n') {
            fileindex++;
        }
        while (fileindex < filesize && buffer[fileindex] != '\r' &&
               buffer[fileindex] != '\n') {
            line[lineindex++] = buffer[fileindex++];
        }
        line[lineindex] = '\0';
        printf("%s\n", line);
        int len = strlen(line);
        lineindex = 0;
    }
}