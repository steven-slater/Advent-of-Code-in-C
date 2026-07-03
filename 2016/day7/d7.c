#include "uthash.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    char *key;
    bool bracket;

    UT_hash_handle hh; // makes this struct hashable
} Address;
// Address *table = NULL;
Address *nobrak = NULL;
Address *inbrak = NULL;
void freeTable(Address **table) {
    Address *current, *tmp;
    HASH_ITER(hh, *table, current, tmp) {
        HASH_DEL(*table, current); // remove from the hash table
        free(current->key);        // free the strdup'd key
        free(current);             // free the struct itself
    }
    // *table is now NULL — HASH_DEL updates the head pointer as entries are
    // removed
}
int main(void) {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
    }
    int count = 0;
    bool valid = true;
    long filesize = 0;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize + 1, sizeof(char));
    long bytesread = fread(buffer, sizeof(char), filesize, fp);
    if (bytesread != filesize) {
        perror("fread");
    }

    int fileindex = 0;

    while (fileindex < filesize) {
        char *line = calloc(512, sizeof(char));
        int lineindex = 0;
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
        int len = strlen(line);

        //  printf("%s\n", line);
        lineindex = 0;
        while (lineindex < len) {
            char *part = calloc(256, sizeof(char));
            int partindex = 0;
            while (lineindex < len && line[lineindex] != '[') {
                part[partindex++] = line[lineindex++];
            }
            part[partindex] = '\0';
            Address *addr = calloc(1, sizeof(Address));
            //         strcpy(addr->key, part);
            addr->key = strdup(part);
            addr->bracket = false;
            HASH_ADD_KEYPTR(hh, nobrak, addr->key, strlen(part), addr);
            // for (Address *current = nobrak; current != NULL;
            //      current = current->hh.next) {
            //     printf("key: '%s' value: %d\n", current->key,
            //     current->bracket);
            //            }
            part = calloc(256, sizeof(char));
            partindex = 0;

            int current = 0;
            int start = 0;
            lineindex++; // move past [
            if (lineindex >= len)
                break;
            else {
                while (lineindex < len && line[lineindex] != ']') {
                    part[partindex++] = line[lineindex++];
                }

                addr = calloc(1, sizeof(Address));
                addr->key = strdup(part);
                addr->bracket = true;
                HASH_ADD_KEYPTR(hh, inbrak, addr->key, strlen(part), addr);
                lineindex++; // move past ]
                // for (Address *current = inbrak; current != NULL;
                //      current = current->hh.next) {
                //     printf("key: '%s' value: %d\n", current->key,
                //            current->bracket);
                // }
            }
        }
        int start = 0;
        int end = 0;
        char *test;
        // process tables
        for (Address *current = inbrak; current != NULL;
             current = current->hh.next) {
            test = calloc(strlen(current->key + 1), sizeof(char));
            strcpy(test, current->key);
            start = 0;
            end = strlen(test) - 3;
            for (int i = 0; i < end; i++) {
                //     printf("%s\n", test + i);
                if (test[start] == test[start + 3] &&
                    test[start] != test[start + 1] &&
                    test[start + 1] == test[start + 2]) {
                    valid = false;
                    //  free(test);
                    break;

                } else {
                    //                    valid = true;
                    start++;
                }
            }
        }
        freeTable(&inbrak);

        if (valid == true) {
            valid = false;
            for (Address *current = nobrak; current != NULL;
                 current = current->hh.next) {

                //   printf("key: '%s' value: %d\n", current->key,
                //   current->bracket);
                test = calloc(strlen(current->key) + 1, sizeof(char));
                strcpy(test, current->key);
                start = 0;
                end = strlen(test) - 3;
                for (int i = 0; i < end; i++) {
                    //                    printf("%s\n", test + i);
                    if (test[start] == test[start + 3] &&
                        test[start] != test[start + 1] &&
                        test[start + 1] == test[start + 2]) {
                        valid = true;
                        printf("WINNER: %s\n", test + i);
                        break;

                    } else {

                        start++;
                    }
                }
                if (valid)
                    break;
            }
            free(test);
        }
        if (valid) {

            freeTable(&nobrak);
            count++;
        }
        if (nobrak != NULL) {
            freeTable(&nobrak);
        }
        free(line);
        valid = true;
    }
    printf("%d are valid", count);
    return 0;
}