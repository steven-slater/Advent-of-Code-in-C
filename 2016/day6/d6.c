#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char key;
    int count;
    UT_hash_handle hh; // makes this struct hashable
} Columns;

Columns *col0 = NULL;
Columns *col1 = NULL;
Columns *col2 = NULL;
Columns *col3 = NULL;
Columns *col4 = NULL;
Columns *col5 = NULL;
int sort_by_count(Columns *a, Columns *b) {
    if (b->count > a->count)
        return 1;
    if (b->count < a->count)
        return -1;
    return (a->key > b->key);
    // For ascending order, use: return (a->count - b->count);
}
void printTable(Columns *table) {
    Columns *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%c' value: %d\n", current->key, current->count);
    }
    printf("---\n"); // set breakpoint on this line
}
void main() {
    char answer[256];
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize, sizeof(char));
    long bytesread = fread(buffer, 1, filesize, fp);
    if (bytesread != filesize) {
        perror("fread");
    }
    int fileindex = 0;
    int lineindex = 0;
    char *line;
    while (fileindex < filesize) {

        line = calloc(7, sizeof(char));
        lineindex = 0;
        if (line == NULL) {
            perror("calloc");
            exit(1);
        }
        if (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
                fileindex++;
            }
        }
        while (fileindex < filesize && buffer[fileindex] != '\r' &&
               buffer[fileindex] != '\n') {
            char c = buffer[fileindex];
            Columns *found;
            switch (lineindex) {
            case 0:
                HASH_FIND(hh, col0, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col0, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col0\n");
                printTable(col0);
                break;
            case 1:
                HASH_FIND(hh, col1, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col1, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col1\n");
                printTable(col1);

                break;
            case 2:
                HASH_FIND(hh, col2, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col2, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col2\n");
                printTable(col2);

                break;
            case 3:
                HASH_FIND(hh, col3, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col3, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col3\n");
                printTable(col3);

                break;
            case 4:
                HASH_FIND(hh, col4, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col4, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col4\n");
                printTable(col4);

                break;
            case 5:
                HASH_FIND(hh, col5, &c, sizeof(char), found);
                if (found == NULL) {
                    Columns *entry = calloc(1, sizeof(Columns));
                    entry->key = c;

                    entry->count++;
                    HASH_ADD(hh, col5, key, sizeof(char), entry);

                } else {
                    found->count++;
                }
                printf("Col5\n");
                printTable(col5);

                break;
            default:
                break;
            }

            line[lineindex++] = buffer[fileindex++];
        }

        printf("%s\n", line);
        // free(line);
    }
    int index = 0;
    Columns *el, *tmp;
    HASH_SORT(col0, sort_by_count);

    HASH_ITER(hh, col0, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    HASH_SORT(col1, sort_by_count);
    HASH_ITER(hh, col1, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    HASH_SORT(col2, sort_by_count);
    HASH_ITER(hh, col2, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    HASH_SORT(col3, sort_by_count);
    HASH_ITER(hh, col3, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    HASH_SORT(col4, sort_by_count);
    HASH_ITER(hh, col4, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    HASH_SORT(col5, sort_by_count);
    HASH_ITER(hh, col5, el, tmp) {
        answer[index] = el->key;
        index++;
        break;
    }
    answer[index] = '\0';
    printf("answer: %s\n", answer);
}
