#include "uthash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char key[50];
    int value;
    int index;
    UT_hash_handle hh; // makes this struct hashable
} Entry;

Entry *table = NULL;
void printTable(Entry *table) {
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%s' value: %d\n", current->key, current->value);
    }
    printf("---\n"); // set breakpoint on this line
}
int main() {
    char *invalid = "iol";
    bool isValid = true;
    bool hasDouble = false;
    bool hasTriple = false;
    FILE *fp = fopen("s1.txt", "rb");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    char *buffer;
    long filesize;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    printf("%ld\n", filesize);
    buffer = (calloc(filesize + 1, sizeof(char)));
    long bytesRead = fread(buffer, sizeof(char), filesize, fp);
    if (bytesRead != filesize) {
        perror("Error reading file");
        free(buffer);
        fclose(fp);
        return 1;
    }
    long index = 0;
    while (index < filesize) {
        char *line = calloc(256, sizeof(char));
        char c = buffer[index];
        while (c != '\0' && c != '\n' && c != '\r') {
            line[index++] = c;
            c = buffer[index];
        }
        index = 0;
        for (int i = 0; i < strlen(line); i++) {
            c = line[i];
            if (strchr(invalid, c)) {
                printf("Invalid character '%c' at index %ld\n", c, i);
                isValid = false;
                break;
            }
            index++;
            c = buffer[index];
        }
        if (isValid && hasDouble && hasTriple) {
            Entry *entry;
            HASH_FIND_STR(table, buffer, entry);
            if (entry) {
                entry->value++;
            } else {
                entry = (Entry *)malloc(sizeof(Entry));
                strncpy(entry->key, buffer, sizeof(entry->key) - 1);
                entry->key[sizeof(entry->key) - 1] =
                    '\0'; // Ensure null-termination
                entry->value = 1;
                HASH_ADD_STR(table, key, entry);
            }
            index++;
        }
    }

    fclose(fp);
    return 0;
}