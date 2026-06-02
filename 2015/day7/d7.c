#include "uthash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
    UT_hash_handle hh; // makes this struct hashable
} Entry;
void add_entry(Entry **table, const char *key, int value) {
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    strncpy(entry->key, key, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0'; // Ensure null-termination
    entry->value = value;
    HASH_ADD_STR(*table, key, entry);
}
void printTable(Entry *table) {
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%s' value: %d\n", current->key, current->value);
    }
    printf("---\n"); // set breakpoint on this line
}
Entry *table = NULL;
int main() {
    char *buffer;
    FILE *fp;
    fp = fopen("s1.txt", "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    printf("%ld\n", fileSize);
    buffer = (char *)malloc(fileSize + 1);
    long bytesRead = fread(buffer, sizeof(char), fileSize, fp);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        fclose(fp);
        return 1;
    }
    buffer[fileSize] = '\0';
    int fileindex = 0;
    char line[256];
    char operator[12];
    char *token;
    int amt = 0;
    char reg1[5], reg2[5], reg3[5];
    int reg1val, reg2val, reg3val;
    Entry *found;
    while (fileindex < fileSize) {
        int lineindex = 0;
        if (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }
        while (fileindex < fileSize && buffer[fileindex] != '\n' &&
               buffer[fileindex] != '\r') {
            line[lineindex++] = buffer[fileindex++];
        }
        line[lineindex] = '\0';
        int len = strlen(line);
        printf("line: '%s' \n", line);
        //  printf("%s %ld\n", line, len);

        token = strtok(line, " ");
        printf("first token: %s\n", token);
        char c = token[0];
        if (isdigit(c)) {
            amt = atoi(token);
            printf("%d\n", amt);

            token = strtok(NULL, " ");
            printf("second token: %s\n", token);
            if (strcmp(token, "->") == 0) {
                token = strtok(NULL, " ");
                printf("third token: %s\n", token);
                strcpy(reg1, token);
                token = strtok(NULL, " ");
                if (token == NULL) {
                    printf("Finished line. Process operation\n");
                    HASH_FIND_STR(table, reg1, found);
                    if (found) {
                        printf("Found register: %s with value: %d\n",
                               found->key, found->value);
                        found->value += amt;
                        printf("Updated register: %s with new value: %d\n",
                               found->key, found->value);
                    } else {
                        printf("Register not found, adding: %s\n", reg1);

                        add_entry(&table, reg1, amt);
                        printTable(table);
                    }
                    fileindex++;
                    continue;
                }
                token = strtok(NULL, " "); // skip the "->" token

                strcpy(reg2, token);
                printf("%d -> %s\n", amt, reg2);
                HASH_FIND_STR(table, reg2, found);
                if (found) {
                    printf("Found register: %s with value: %d\n", found->key,
                           found->value);
                    found->value += amt;
                    printf("Updated register: %s with new value: %d\n",
                           found->key, found->value);
                } else {
                    printf("Register not found, adding: %s\n", reg2);

                    add_entry(&table, reg2, amt);
                    printTable(table);
                    // token = strtok(NULL, " ");
                }
            }
        } else {
            strcpy(reg1, token);
            token = strtok(NULL, " ");
            strcpy(operator, token);
            if (stricmp(reg1, "NOT") == 0) {
                char temp[5];
                strcpy(temp, operator);
                strcpy(operator, reg1);
                strcpy(reg1, temp);
            } else if (stricmp(operator, "AND") == 0 ||
                       stricmp(operator, "OR") ||
                       stricmp(operator, "NOT") == 0 ||
                       stricmp(operator, "XOR") == 0 ||
                       stricmp(operator, "LSHIFT") == 0 ||
                       stricmp(operator, "RSHIFT") == 0) {
                // register AND/OR/NOT register -> register
                // strcat(operator, " AND/OR/NOT");
                token = strtok(NULL, " ");
                strcpy(reg2, token);
                token = strtok(NULL, " "); // skip the "->" token
                token = strtok(NULL, " ");
                strcpy(reg3, token);
                printf("%s %s %s -> %s\n", reg1, operator, reg2, reg3);
                HASH_FIND_STR(table, reg1, found); // REGISTER 1
                if (found) {
                    printf("Found register: %s with value: %d\n", found->key,
                           found->value);
                    reg1val = found->value;
                } else {
                    printf("Register not found, adding: %s\n", reg1);

                    add_entry(&table, reg1, 1);

                    //                    token = strtok(NULL, " ");
                }
                HASH_FIND_STR(table, reg2, found);
                if (found) {
                    printf("Found register: %s with value: %d\n", found->key,
                           found->value);
                    reg2val = found->value;
                } else {
                    printf("Register not found, adding: %s\n", reg2);

                    add_entry(&table, reg2, 1);
                    printTable(table);
                    // token = strtok(NULL, " ");
                }
                HASH_FIND_STR(table, reg3, found);

                int result = 0;

                int r1 = reg1val;
                int r2 = reg2val;

                if (stricmp(operator, "AND") == 0) {
                    result = r1 & r2;
                } else if (stricmp(operator, "OR") == 0) {
                    result = r1 | r2;
                } else if (stricmp(operator, "NOT") == 0) {
                    result = ~r1;
                } else if (stricmp(operator, "XOR") == 0) {
                    result = r1 ^ r2;
                } else if (stricmp(operator, "LSHIFT") == 0) {
                    result = r1 << r2;
                } else if (stricmp(operator, "RSHIFT") == 0) {
                    result = r1 >> r2;
                }
                if (found) {
                    printf("Found register: %s with value: %d\n", found->key,
                           found->value);
                    found->value = result;
                } else {
                    printf("Register not found, adding: %s\n", reg3);

                    add_entry(&table, reg3, result);
                    printTable(table);
                    // token = strtok(NULL, " ");
                }
            }
        }

        if (fileindex < fileSize && buffer[fileindex] == '\n' ||
            buffer[fileindex] == '\r') {
            fileindex++;
        }
    }
    return 0;
}