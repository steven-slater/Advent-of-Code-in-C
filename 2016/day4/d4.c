#include "uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char key[2];
    int count;

    UT_hash_handle hh; // makes this struct hashable
} Letter;
Letter *table = NULL;
int main(void) {
    FILE *fp = fopen("s1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
    }
    char *buffer;
    long filesize = 0;
    long fileindex = 0;
    char *line;
    int lineindex = 0;
    char *token;
    char numb[25];
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    buffer = (char *)malloc(filesize + 1);
    fread(buffer, 1, filesize, fp);
    while (fileindex < filesize) {
        line = calloc(256, sizeof(char));
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }

        while (buffer[fileindex] != '\n' && fileindex < filesize &&
               buffer[fileindex] != '\0' && buffer[fileindex] != '\r') {
            line[lineindex++] = buffer[fileindex++];
        }

        //        line[lineindex] = '\0';
        int len = strlen(line);
        printf("%s is %d bytes\n", line, len);
        for (int i = 0; i < len; i++) {
            char key = line[i];
            while (isdigit(key) == false) {
                printf("%c", key);
                if (key == '-') {
                    i++;
                    key = line[i];
                    continue;
                }
                Letter *found;

                HASH_FIND_STR(table, &key, found);
                if (!found) {
                    Letter *letter = calloc(1, sizeof(Letter));
                    letter->key[0] = key;
                    letter->key[1] = '\0';
                    letter->count++;
                    HASH_ADD_STR(table, key, letter);
                } else {
                    found->count++;
                }
                i++;
                key = line[i];
            }
            int index = 0;
            while (key != '[') {
                numb[index++] = key;
                i++;
                key = line[i];
            }
            numb[index] = '\0';
        }
    }

    return 0;
}