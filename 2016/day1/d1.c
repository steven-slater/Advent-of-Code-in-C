#include "../uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWSTART 5000
#define COLSTART 5000
typedef struct {
    char key[50];
    int value;
    UT_hash_handle hh; // makes this struct hashable
} Entry;

Entry *table = NULL;
void printTable(Entry *table) {
    int index = 0;
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("[%d] dkey: '%s' value: %d\n", index++, current->key,
               current->value);
    }
    printf("---\n"); // set breakpoint on this line
}
int compute_distance(int row, int col) {
    return abs(ROWSTART - row + COLSTART - col);
}
int main() {
    char loc[50];
    char cloc[25];
    char rloc[25];
    Entry *found;
    bool notdone = true;
    FILE *fp = fopen("p1.txt", "rb");
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer;
    buffer = calloc(1, filesize + 1);
    fread(buffer, sizeof(char), filesize, fp);
    buffer[filesize] = '\0';
    long fileindex = 0;
    char line[256];
    int col = 5000;
    int row = 5000;
    char direction = 'N';
    char prevdirection = 'N';
    int amount = 0;
    int linectr = 0;
    int tottomove = 0;

    itoa(col, cloc, 10);
    itoa(row, rloc, 10);
    strcpy(loc, cloc);
    strcat(loc, rloc);
    // char key[25];
    // strcpy(key, loc);
    Entry *entry = calloc(1, sizeof(Entry));
    entry->value = 0;
    strcpy(entry->key, loc);
    HASH_ADD_STR(table, key, entry);

    while (fileindex < filesize) {
        linectr++;
        int lineindex = 0;
        if (buffer[fileindex] == '\r') {

            linectr++;
            prevdirection = 'N';
            direction = 'N';
        }
        if (buffer[fileindex] == '\n' || buffer[fileindex] == '\r' ||
            buffer[fileindex] == ',' || buffer[fileindex] == ' ') {
            fileindex += 2;
        }
        while (fileindex < filesize && buffer[fileindex] != '\n' &&
               buffer[fileindex] != ' ' && buffer[fileindex] != '\r' &&
               buffer[fileindex] != ',') {
            line[lineindex++] = buffer[fileindex++];
        }
        line[lineindex] = '\0';
        int len = strlen(line);
        if (len == 0)
            continue;
        else {
            direction = line[0];
            amount = atoi(&line[1]);
        }

        switch (direction) {
        case 'R':
            if (prevdirection == 'N') {
                prevdirection = 'E';
                tottomove = col + amount;

                itoa(row, rloc, 10);

                while (col++ < tottomove) {

                    itoa(col, cloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }

                col--;
            } else if (prevdirection == 'S') {
                prevdirection = 'W';
                tottomove = col - amount;
                itoa(row, rloc, 10);
                while (col-- > tottomove) {

                    itoa(col, cloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }

                col++;
            } else if (prevdirection == 'E') {
                prevdirection = 'S';
                tottomove = row - amount;
                itoa(col, cloc, 10);

                while (row-- > tottomove) {

                    itoa(row, rloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                row++;
            } else if (prevdirection == 'W') {
                prevdirection = 'N';
                tottomove = row + amount;
                itoa(col, cloc, 10);

                while (row++ < tottomove) {

                    itoa(row, rloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                row--;
            }
            break;

        case 'L':
            if (prevdirection == 'S') {
                prevdirection = 'E';
                tottomove = col + amount;
                itoa(row, rloc, 10);
                while (col++ < tottomove) {
                    itoa(col, cloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                col--;
            } else if (prevdirection == 'N') {
                prevdirection = 'W';
                tottomove = col - amount;
                itoa(row, rloc, 10);
                while (col-- > tottomove) {

                    itoa(col, cloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                col++;
            } else if (prevdirection == 'E') {
                prevdirection = 'N';
                tottomove = row + amount;
                itoa(col, cloc, 10);

                while (row++ < tottomove) {

                    itoa(row, rloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                row--;
            } else if (prevdirection == 'W') {
                prevdirection = 'S';
                tottomove = row - amount;
                itoa(col, cloc, 10);

                while (row-- > tottomove) {
                    itoa(row, rloc, 10);
                    strcpy(loc, cloc);
                    strcat(loc, rloc);
                    HASH_FIND_STR(table, loc, found);
                    if (found) {
                        fileindex = filesize;
                        int total = compute_distance(row, col);
                        printf("\n%d", total);
                        break;
                    } else {
                        Entry *entry = calloc(1, sizeof(Entry));
                        char *key = strdup(loc);
                        strcpy(entry->key, key);
                        entry->value = 0;
                        HASH_ADD_STR(table, key, entry);
                    }
                }
                row++;
            }
            break;

        default:
            break;
        }

        //   printTable(table);
    }
    if (fileindex > 2 && linectr > 2) {
        int distance = compute_distance(row, col);
    }
    return 0;
}
