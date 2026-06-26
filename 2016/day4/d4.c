#include "uthash.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
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
    FILE *fout = fopen("out.txt", "wb+");
    if (fout == NULL) {
        perror("fopen");
    }
    int counter = 0;
    int checksum = 0;
    char *buffer;
    long filesize = 0;
    long fileindex = 0;
    char *line;
    int lineindex = 0;
    char *token;
    char numb[25];
    char *id;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    buffer = (char *)malloc(filesize + 1);
    fread(buffer, 1, filesize, fp);
    while (fileindex < filesize) {
        lineindex = 0;
        table = NULL;
        line = calloc(256, sizeof(char));

        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }

        while (buffer[fileindex] != '\n' && fileindex < filesize &&
               buffer[fileindex] != '\0' && buffer[fileindex] != '\r') {
            line[lineindex++] = buffer[fileindex++];
        }

        line[lineindex] = '\0';
        int len = strlen(line);
        printf("%s is %d bytes\n", line, len);
        //     fprintf(fout, "%s\n", line);
        for (int i = 0; i < len; i++) {
            char key = line[i];
            while (isdigit(key) == false) {
                //  printf("%c", key);
                if (key == '-') {
                    i++;
                    key = line[i];
                    continue;
                }
                Letter *found;

                HASH_FIND(hh, table, &key, sizeof(char), found);
                if (!found) {
                    Letter *letter = calloc(1, sizeof(Letter));
                    letter->key = key;
                    // letter->key[1] = '\0';
                    letter->count++;
                    HASH_ADD(hh, table, key, sizeof(char), letter);
                } else {
                    found->count++;
                }
                i++;
                key = line[i];
            }
            printTable(table);
            // printf("\n");
            int index = 0;
            HASH_SORT(table, sort_by_count);
            char *used = calloc(100, sizeof(char));
            Letter *el, *tmp;
            HASH_ITER(hh, table, el, tmp) {

                used[index++] = el->key;
                //    printf("Key: %s, Count: %d\n", el->key, el->count);
            }
            index = 0;
            while (key != '[') {
                numb[index++] = key;
                i++;
                key = line[i];
            }
            numb[index] = '\0';
            int num = atoi(numb);
            i++;
            key = line[i];
            num %= 26;
            index = 0;
            bool failed = false;

            while (key != ']') {
                while (index < 5) {
                    char c = used[index];

                    if (line[i] != c) {
                        printf("%s is not a room\n", line);
                        i++;
                        failed = true;
                        break;
                    }
                    index++;
                    i++;
                }

                if (!failed) {
                    checksum += atoi(numb);
                    key = line[i];
                    counter++;
                    //     printf("%d\n", counter);
                    printf("VALID ROOM: %s\n", line);
                    fprintf(fout, "%s\n", line);
                }
                if (failed) {
                    i = len;
                    break;
                }
            }
        }
    }
    fflush(fout);
    fclose(fout);
    fclose(fp);
    fp = fopen("out.txt", "rb");
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    buffer = (char *)malloc(filesize + 1);
    long bytesread = fread(buffer, 1, filesize, fp);

    char *alph = "abcdefghijklmnopqrstuvwxyz";
    printf("Checksum of valid rooms: %d\n", checksum);
    fileindex = 0;
    while (fileindex < filesize) {
        lineindex = 0;
        table = NULL;
        line = calloc(256, sizeof(char));
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }

        while (buffer[fileindex] != '\n' && fileindex < filesize &&
               buffer[fileindex] != '\0' && buffer[fileindex] != '\r') {
            line[lineindex++] = buffer[fileindex++];
        }
        int llen = strlen(line);
        char *answer = calloc(llen, sizeof(char));
        int alptr = 0;
        // int index = 0;
        int positions[256];
        int count = 0;
        counter = 0;
        char *ptr = line;
        while ((ptr = strchr(ptr, '-')) != NULL) {
            positions[count++] = ptr - line;
            counter++;
            ptr++; // move past this '-' so strchr doesn't find it again
        }
        count = 0;
        printf("%s is %d bytes\n", line, llen);
        token = strtok(line, "-");
        char *name = calloc(llen, sizeof(char));
        strcpy(name, token);
        strcat(name, " ");
        while (token != NULL) {
            token = strtok(NULL, "-");
            if (isdigit(token[0]) == false) {
                strcat(name, token);
                strcat(name, " ");
            } else {
                id = calloc(llen, sizeof(char));

                strcpy(id, token);
                token = strtok(id, "[]");
                strcpy(id, token);
                break;
            }
            // token = strtok(NULL, "-");
        }

        int dash = 0;
        int spaceindex = positions[dash];
        int namelen = strlen(name);
        for (int i = 0; i < namelen; i++) {
            // if (i == spaceindex) {
            //     answer[spaceindex] = ' ';
            //     dash++;
            //     spaceindex = positions[dash];
            //     printf("%s", answer);
            // }

            char key = name[i];
            if (key == ' ') {
                answer[i] = ' ';
                continue;
            }
            for (int q = 0; q < 26; q++) {
                if (key == alph[q]) {
                    alptr = q;

                    int number = atoi(id);
                    int tnum = alptr * number;
                    tnum %= 26;
                    answer[i] = alph[(alptr + number) % 26];

                    break;
                }
            }
        }
        printf("%s\n", answer);
        free(line);
        free(answer);
        free(name);
        free(id);
    }
    return 0;
}