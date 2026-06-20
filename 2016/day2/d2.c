#include "../uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWSTART 1
#define COLSTART 1
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
printGrid(int grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int index = 1;
    int grid[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = index;
            index++;
        }
    }
    printGrid(grid);
    char loc[50];
    char cloc[25];
    char rloc[25];
    Entry *found;
    bool notdone = true;
    FILE *fp = fopen("s1.txt", "rb");
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer;
    buffer = calloc(1, filesize + 1);
    fread(buffer, sizeof(char), filesize, fp);
    buffer[filesize] = '\0';
    long fileindex = 0;
    char line[25];
    int resindex = 0;
    char direction = 'U'; // U D L R up down left right
    char prevdirection = 'U';
    int amount = 0;
    int linectr = 0;
    int tottomove = 0;
    int row = ROWSTART;
    int col = COLSTART;
    index = 0;
    int answer[5];
    while (fileindex < filesize) {
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }
        while (fileindex < filesize && buffer[fileindex] != '\n' &&
               buffer[fileindex] != '\r') {
            line[index++] = buffer[fileindex++];
        }
        line[index] = '\0';
        index = 0;
        printf("%s\n", line);
        direction = line[index];
        int len = strlen(line);
        while (index < len) {
            switch (direction) {
            case 'U':
                if (row == 0)
                    break;
                row--; /* code */
                break;
            case 'D':
                row++;
                if (row == 3)
                    row--;
                break;
                break;
            case 'L':
                if (col == 0)
                    break;
                col--;
                break;
            case 'R':
                col++;
                if (col == 3)
                    col--;
                break;

                break;

            default:
                break;
            }
            index++;
            if (index == len)
                break;
            else
                direction = line[index];
        }
        answer[resindex++] = grid[row][col];
        index = 0;
        // printf("%d ", grid[row][col]);
        printf("%d\n", answer[resindex - 1]);
    }
    for (int k = 0; k < 4; k++) {
        printf("%d", answer[k]);
    }
    return 0;
}
