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
} Memo;
Memo *memo = NULL;
void add_entry(Memo **table, const char *key, int value) {
    Memo *kvp = (Memo *)malloc(sizeof(Memo));
    strncpy(kvp->key, key, sizeof(kvp->key) - 1);
    kvp->key[sizeof(kvp->key) - 1] = '\0'; // Ensure null-termination
    kvp->value = value;
    HASH_ADD_STR(*table, key, kvp);
}
void printTable(Memo *table) {
    int index = 0;
    Memo *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("[%d] dkey: '%s' value: %d\n", index++, current->key,
               current->value);
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
Memo *keyvaluepair = NULL;
Wires *registers = NULL;
int evalwire(char *wire, Wires *registers, Memo **keyvaluepair) {
    Memo *found;
    HASH_FIND_STR(*keyvaluepair, wire, found);
    if (found) {
        return found->value;
    }
    if (isdigit((unsigned char)wire[0])) {
        return atoi(wire);
    }

    Wires *def;
    HASH_FIND_STR(registers, wire, def);
    if (!def) {
        fprintf(stderr, "wire %s not found\n", wire);
        return -1;
    }

    int result;
    if (strcmp(def->operation, "ASSIGN") == 0) {
        result = evalwire(def->oper1, registers, keyvaluepair);
    } else if (strcmp(def->operation, "AND") == 0) {
        result = evalwire(def->oper1, registers, keyvaluepair) &
                 evalwire(def->oper2, registers, keyvaluepair);
    } else if (strcmp(def->operation, "OR") == 0) {
        result = evalwire(def->oper1, registers, keyvaluepair) |
                 evalwire(def->oper2, registers, keyvaluepair);
    } else if (strcmp(def->operation, "NOT") == 0) {
        result = (~evalwire(def->oper1, registers, keyvaluepair));
    } else if (strcmp(def->operation, "LSHIFT") == 0) {
        result = evalwire(def->oper1, registers, keyvaluepair)
                 << atoi(def->oper2);
    } else if (strcmp(def->operation, "RSHIFT") == 0) {
        result =
            evalwire(def->oper1, registers, keyvaluepair) >> atoi(def->oper2);
    } else {
        result = 0; // shouldn't happen
    }
    result &= 0xFFFF;
    add_entry(keyvaluepair, wire, result); // memoize
                                           // printTable(*keyvaluepair);
    return result;
}
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
    Memo *found;
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
        //  printf("line: '%s' \n", line);
        //  printf("%s %ld\n", line, len);
        char op1[20];
        char op2[20];
        char target[20];
        char tokens[4][20];
        int tokindex = 0;
        char amount[20];
        token = strtok(line, " ");

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

        // for (int k = 0; k < tokindex; k++) {
        //     printf("%s ", tokens[k]);
        // }
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
        } else if (tokindex == 3) {
            //   printf("found NOT");
            strcpy(operator, tokens[0]);
            strcpy(op1, tokens[1]);
            strcpy(target, tokens[2]);
            strcpy(op2, "NA");
        }
        Wires *wire = calloc(1, sizeof(Wires));
        wire->key = strdup(target);
        wire->oper1 = strdup(op1);
        wire->oper2 = strdup(op2);
        wire->operation = strdup(operator);
        HASH_ADD_STR(registers, key, wire);
        // printRegisters(registers);
        tokindex = 0;
    }
    int answer = evalwire("a", registers, &keyvaluepair);
    printf("%d ", answer);
    Wires *wire = calloc(1, sizeof(Wires));
    wire->key = "b";
    char amttoassign[10];
    itoa(answer, amttoassign, 10);
    wire->oper1 = strdup(amttoassign);
    wire->oper2 = "NA";
    wire->operation = "ASSIGN";
    keyvaluepair = NULL;
    HASH_ADD_STR(registers, key, wire);
    printf("\n");
    printRegisters(registers);
    answer = evalwire("a", registers, &keyvaluepair);
    printf("%d", answer);
}