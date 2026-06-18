#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWSTART 5000
#define COLSTART 5000

int compute_distance(int row, int col) {
    return ROWSTART - row + COLSTART - col;
}
int main() {
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
    char line[256];
    int col = 5000;
    int row = 5000;
    char direction = 'N';
    char prevdirection = 'N';
    int amount = 0;
    int linectr = 0;
    while (fileindex < filesize) {
        linectr++;
        int lineindex = 0;
        if (buffer[fileindex] == '\r') {
            row = 5000;
            col = 5000;
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
                col = col + amount;
            } else if (prevdirection == 'S') {
                prevdirection = 'W';
                col = col - amount;
            } else if (prevdirection == 'E') {
                prevdirection = 'S';
                row = row - amount;
            } else if (prevdirection == 'W') {
                prevdirection = 'N';
                row = row + amount;
            }
            break;

        case 'L':
            if (prevdirection == 'S') {
                prevdirection = 'E';
                col = col + amount;
            } else if (prevdirection == 'N') {
                prevdirection = 'W';
                col = col - amount;
            } else if (prevdirection == 'E') {
                prevdirection = 'N';
                row = row + amount;
            } else if (prevdirection == 'W') {
                prevdirection = 'S';
                row = row - amount;
            }
            break;

        default:
            break;
        }
        if (fileindex > 2 && linectr > 2) {
            int distance = compute_distance(row, col);
            printf("%d\n", abs(distance));
        }
    }

    return 0;
}
