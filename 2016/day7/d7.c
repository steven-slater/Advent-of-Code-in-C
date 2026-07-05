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
Address *bab = NULL;
Address *aba = NULL;
int sort_by_key(Address *a, Address *b) {
    return (a->key > b->key);
    // For ascending order, use: return (a->count - b->count);
}
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
    FILE *fp = fopen("s1.txt", "rb");
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
    fclose(fp);
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

            part = calloc(256, sizeof(char));
            partindex = 0;

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

    printf("Part1: %d are valid\n", count);
    count = 0;
    FILE *fd = fopen("s2.txt", "rb");
    if (fd == NULL) {
        perror("Can't open file");
    }
    count = 0;
    bool ABA = true;
    bool BAB = true;
    filesize = 0;
    fseek(fd, 0, SEEK_END);
    filesize = ftell(fd);
    rewind(fd);
    buffer = calloc(filesize + 1, sizeof(char));
    bytesread = fread(buffer, sizeof(char), filesize, fd);
    if (bytesread != filesize) {
        perror("fread");
    }

    fileindex = 0;
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
        lineindex = 0;
        int start = 0;
        while (lineindex < len) {
            char *part = calloc(256, sizeof(char));
            int partindex = 0;
            while (lineindex < len && line[lineindex] != '[') {
                part[partindex++] = line[lineindex++];
            }
            part[partindex] = '\0';
            char ip[4];
            start = 0;

            int end = strlen(part - 2);
            int plen = strlen(part);
            for (int j = 0; j < plen - 1; j++) {
                if (part[start] == part[start + 2] &&
                    part[start] != part[start + 1]) {
                    ip[0] = part[start + 1];
                    ip[1] = part[start + 2];
                    ip[2] = part[start + 1];
                    ip[3] = '\0';

                    Address *addr = calloc(1, sizeof(Address));
                    addr->key = strdup(ip);
                    addr->bracket = 0;
                    start++;
                    HASH_ADD_KEYPTR(hh, nobrak, addr->key, strlen(part), addr);
                    for (Address *current = nobrak; current != NULL;
                         current = current->hh.next) {
                        printf("key: '%s' value: %d\n", current->key,
                               current->bracket);
                    }
                    continue;
                }

                else {
                    start++;
                }
            }
            lineindex++; // move past [
            if (lineindex >= len)
                break;
            else {
                char *part = calloc(256, sizeof(char));
                partindex = 0;
                while (lineindex < len && line[lineindex] != ']') {
                    part[partindex++] = line[lineindex++];
                }
                start = 0;
                plen = strlen(part);
                for (int j = 0; j < plen - 1; j++) {
                    if (part[start] == part[start + 2] &&
                        part[start] != part[start + 1]) {
                        ip[0] = part[start + 1];
                        ip[1] = part[start + 2];
                        ip[2] = part[start + 1];
                        ip[3] = '\0';

                        Address *found = NULL;
                        HASH_FIND(hh, nobrak, ip, strlen(ip), found);
                        if (found != NULL) {
                            count++;
                        }
                        lineindex++; // move past ]
                    }
                }
            }
        }