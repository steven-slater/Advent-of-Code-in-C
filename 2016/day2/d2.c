#include "../uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWSTART 2
#define COLSTART 0

printGrid(char grid[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}
int main() {
    FILE *gp = fopen("g1.txt", "rb");

    fseek(gp, 0, SEEK_END);
    long filesize = ftell(gp);
    rewind(gp);
    char *buffer;
    buffer = calloc(1, filesize + 1);
    fread(buffer, sizeof(char), filesize, gp);
    buffer[filesize] = '\0';
    long fileindex = 0;
    char *line = calloc(1, filesize + 1);
    int index = 0;
    int rindex = 0;
    int cindex = 0;
    char grid[5][5];
    while (fileindex < filesize) {
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }
        while (fileindex < filesize && buffer[fileindex] != '\0') {
            while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
                fileindex++;
            }
            line[index++] = buffer[fileindex++];

            grid[rindex][cindex] = line[index - 1];
            printf("%c", grid[rindex][cindex]);
            cindex++;
            if (cindex >= 5) {
                rindex++;
                printf("\n");
            }
            cindex %= 5;
        }
        free(line);
    }

    printGrid(grid);

    bool notdone = true;
    FILE *fp = fopen("p1.txt", "rb");
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    buffer = calloc(1, filesize + 1);
    fread(buffer, sizeof(char), filesize, fp);
    buffer[filesize] = '\0';
    fileindex = 0;

    //    char line[filesize];
    int resindex = 0;
    char direction = 'U'; // U D L R up down left right
    char prevdirection = 'U';
    line = calloc(1, 5000); // 4999 avail
    int row = ROWSTART;
    int col = COLSTART;
    index = 0;
    char *answer = calloc(1, 5000);
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
                if (grid[row - 1][col] == '0')
                    break;

                row--; /* code */
                break;
            case 'D':

                if (row == 4)
                    break;

                if (grid[row + 1][col] == '0')
                    break;

                row++;
                break;

            case 'L':
                if (col == 0)
                    break;
                if (grid[row][col - 1] == '0')
                    break;

                col--;
                break;
            case 'R':
                if (col >= 4)
                    break;
                if (grid[row][col + 1] == '0')
                    break;

                col++;

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
        printf("%c\n", answer[resindex - 1]);
    }
    int k = 0;
    while (answer[k] != '\0') {
        printf("%c", answer[k++]);
    }
    return 0;
}
