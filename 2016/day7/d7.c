#include "uthash.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    char key;
    int count;

    UT_hash_handle hh; // makes this struct hashable
} Letter;
Letter *table = NULL;
void printTable(Letter *table) {
    Letter *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%c' value: %d\n", current->key, current->count);
    }
    printf("---\n"); // set breakpoint on this line
}
int sort_by_count(Letter *a, Letter *b) {
    if (b->count > a->count)
        return 1;
    if (b->count < a->count)
        return -1;
    return (a->key > b->key);
    // For ascending order, use: return (a->count - b->count);
}

int main(void) {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
    }
    long filesize = 0;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize + 1, sizeof(char));
    long bytesread = fread(buffer, sizeof(char), filesize, fp);
    if (bytesread != filesize) {
        perror("fread");
    }
    char *line = calloc(512, sizeof(char));
    int fileindex = 0;
    int lineindex = 0;
    while (fileindex < filesize) {
        if (fileindex < filesize && buffer[fileindex] == '\n' ||
            buffer[fileindex] == '\r') {
            while (fileindex < filesize && buffer[fileindex] == '\n' ||
                   buffer[fileindex] == '\r') {
                fileindex++;
            }
        }
        while (fileindex < filesize && buffer[fileindex] != '\n' &&
               buffer[fileindex] != '\r') {
            line[lineindex++] = buffer[fileindex++];
        }
        printf("%s\n", line);
        char *token;
        char *pos = strchr(line, '[');
        token = strtok(line, "[]");
        while (token != NULL) {
            printf("token: %s\n", token);
            token = strtok(NULL, line);
        }
    }
    return 0;
}