#include "uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_number(const char *s) {
    if (s == NULL || *s == '\0')
        return 0; // null/empty → false
    while (*s) {
        if (!isdigit(*s))
            return 0;
        s++;
    }
    return 1;
}
typedef struct {
    char *key;
    char *oper1;
    char *operation;
    char *oper2;
    UT_hash_handle hh;
} Wires;

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
void printRegisters(Wires *table) {
    Wires *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%s' values: %s %s %s\n", current->key, current->oper1,
               current->operation, current->oper2);
    }
    printf("---\n"); // set breakpoint on this line
}
Entry *table = NULL;
Wires *registers = NULL;

int main() {
    char *buffer;
    FILE *fp;
    fp = fopen("p1.txt", "rb");
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
        if (len == 0)
            continue;
        printf("line: '%s' \n", line);
        //  printf("%s %ld\n", line, len);
        char op1[20];
        char op2[20];
        char target[20];
        char tokens[4][20];
        int tokindex = 0;
        char amount[20];
        token = strtok(line, " ");
        printf("first token: %s\n", token);
        for (int j = 0; j <= 4; j++) {
            if (token == NULL) {
                break;
            }
            if (strcmp(token, "->") == 0) {
                if (tokindex == 1) {
                    strcpy(operator, "ASSIGN");
                }
                token = strtok(NULL, " ");
                continue;
            }
            strcpy(tokens[tokindex++], token);
            token = strtok(NULL, " ");
        }

        for (int k = 0; k < tokindex; k++) {
            printf("%s ", tokens[k]);
        }
        if (tokindex == 4) {
            strcpy(target, tokens[3]);
            strcpy(op1, tokens[0]);
            strcpy(operator, tokens[1]);
            strcpy(op2, tokens[2]);

        } else if (tokindex == 2) {

            strcpy(target, tokens[1]);
            strcpy(op1, tokens[0]);
            strcpy(op2, "NA");
            strcpy(operator, "ASSIGN");
        }
        Wires *wire = calloc(1, sizeof(Wires));
        wire->key = strdup(target);
        wire->oper1 = strdup(op1);
        wire->oper2 = strdup(op2);
        wire->operation = strdup(operator);
        HASH_ADD_STR(registers, key, wire);
        printRegisters(registers);
        tokindex = 0;
    }
    fileindex = 0;
    while (fileindex < fileSize) {
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
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(reg2, token);
            } else if (stricmp(operator, "LSHIFT") == 0) {
                printf("LSHIFT operator found\n");
                token = strtok(NULL, " ");
                strcpy(reg2, token);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(reg3, token);
                printf("%s %s %s\n", reg1, operator, reg2);
            } else if (stricmp(operator, "RSHIFT") == 0) {
                printf("RSHIFT operator found\n");
                token = strtok(NULL, " ");
                strcpy(reg2, token);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(reg3, token);
                //      printf("%s %s %s\n", reg1, operator, reg2);

            } else if (stricmp(operator, "AND") == 0 ||
                       stricmp(operator, "XOR") == 0 ||
                       stricmp(operator, "OR") == 0) {

                token = strtok(NULL, " ");
                strcpy(reg2, token);
                token = strtok(NULL, " "); // skip the "->" token
                token = strtok(NULL, " ");
                strcpy(reg3, token);
                //    printf("%s %s %s -> %s\n", reg1, operator, reg2, reg3);
            }
            HASH_FIND_STR(table, reg1, found); // REGISTER 1
            if (found) {
                //        printf("Found register: %s with value: %d\n",
                //      found->key,
                //     found->value);
                reg1val = found->value;
            } else {
                printf("Register not found, adding: %s\n", reg1);

                add_entry(&table, reg1, 0);
            }

            if (stricmp(operator, "LSHIFT") != 0 &&
                stricmp(operator, "RSHIFT") != 0) {
                HASH_FIND_STR(table, reg2, found);

                if (found) {
                    //              printf("Found register: %s with value:
                    //              %d\n", found->key,
                    //  found->value);
                    reg2val = found->value;
                } else {
                    printf("Register not found, adding: %s\n", reg2);

                    add_entry(&table, reg2, 1);
                    printTable(table);
                    // token = strtok(NULL, " ");
                }
                if (stricmp(operator, "NOT") == 0) {
                    strcpy(reg3, reg2);
                }
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
                result = (~r1) & 0xFFFF; // because of 16bit unsigned int
            } else if (stricmp(operator, "XOR") == 0) {
                result = r1 ^ r2;

            } else if (stricmp(operator, "LSHIFT") == 0) {
                result = r1 << atoi(reg2);
            } else if (stricmp(operator, "RSHIFT") == 0) {
                result = r1 >> atoi(reg2);
            }
            if (found) {
                //            printf("Found register: %s with value: %d\n",
                //            found->key,
                //         found->value);
                found->value = result;
            } else {
                printf("Register not found, adding: %s\n", reg3);

                add_entry(&table, reg3, result);

                // token = strtok(NULL, " ");
            }
            //   printTable(table);
        }

        if (fileindex < fileSize && buffer[fileindex] == '\n' ||
            buffer[fileindex] == '\r') {
            fileindex++;
        }
    }
    HASH_FIND_STR(table, "a", found);
    if (found) {
        printf("Final value in register 'a': %d\n", found->value);
    }
    return 0;
}