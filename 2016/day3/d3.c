#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer = malloc(filesize + 1);
    fread(buffer, 1, filesize, fp);
    char *line;
    char *temp;
    //    char temp[256];
    int fileindex = 0;
    int lineindex = 0;
    int trictr = 0;
    int edgea1, edgeb1, edgec1;
    int edgea2, edgeb2, edgec2;
    int edgea3, edgeb3, edgec3;
    char *token;
    int objctr = 0;
    while (fileindex < filesize) {
        temp = calloc(25, sizeof(char));
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r' ||
               buffer[fileindex] == ' ') {
            fileindex++;
        }

        while (buffer[fileindex] != '\n' && fileindex < filesize &&
               buffer[fileindex] != '\0') {
            temp[lineindex++] = buffer[fileindex++];
        }

        temp[lineindex] = '\0';
        lineindex = 0;
        int len = strlen(temp);
        line = malloc(strlen(temp) + 1);
        strcpy(line, temp);
        // line = calloc(1, sizeof(temp));
        token = strtok(temp, " ");
        int side = atoi(token);
        edgea1 = side;
        objctr++;
        token = strtok(NULL, " ");
        while (token != NULL) {

            side = atoi(token);
            if (objctr % 3 == 1) {
                edgeb1 = side;

            } else {
                edgec1 = side;
            }
            objctr++;
            token = strtok(NULL, " ");
        }
        if (edgea1 + edgeb1 > edgec1 && edgeb1 + edgec1 > edgea1 &&
            edgea1 + edgec1 > edgeb1) {
            trictr++;
        }
    }
    printf("%d", trictr);
    // part 2
    fileindex = 0;
    int howmany = 9;
    trictr = 0;
    while (fileindex < filesize) {

        temp = calloc(25, sizeof(char));
        while (buffer[fileindex] == '\n' || buffer[fileindex] == '\r' ||
               buffer[fileindex] == ' ') {
            fileindex++;
        }

        while (buffer[fileindex] != '\n' && fileindex < filesize &&
               buffer[fileindex] != '\0') {
            temp[lineindex++] = buffer[fileindex++];
        }

        if (temp[lineindex - 1] == '\r')
            temp[lineindex - 1] = '\0';
        lineindex = 0;
        int len = strlen(temp);
        line = malloc(len + 1);
        strcpy(line, temp);
        line[len] = '\0';
        token = strtok(line, " ");
        int side = atoi(token);
        if (objctr % 9 == 0) {
            edgea1 = side;
            objctr++;
            token = strtok(NULL, " ");
        }

        while (token != NULL) {

            side = atoi(token);
            objctr %= 9;
            switch (objctr) {
            case 1:
                edgeb1 = side;

                break;
            case 2:
                edgec1 = side;
                break;

            case 3:
                edgea2 = side;
                break;
            case 4:
                edgeb2 = side;
                break;
            case 5:
                edgec2 = side;
                break;
            case 6:
                edgea3 = side;
                break;
            case 7:
                edgeb3 = side;
                break;
            case 8:
                edgec3 = side;
                break;
            }
            objctr++;
            token = strtok(NULL, " ");

            if (objctr == 9) {

                if (edgea1 + edgea2 > edgea3 && edgea1 + edgea3 > edgea2 &&
                    edgea2 + edgea3 > edgea1) {
                    trictr++;
                }

                if (edgeb1 + edgeb2 > edgeb3 && edgeb2 + edgeb3 > edgeb1 &&
                    edgeb1 + edgeb3 > edgeb2) {
                    trictr++;
                }
                if (edgec3 + edgec1 > edgec2 && edgec2 + edgec3 > edgec1 &&
                    edgec1 + edgec2 > edgec3) {
                    trictr++;
                }
                edgea1 = edgea2 = edgea3 = edgeb1 = edgeb2 = edgeb3 = edgec1 =
                    edgec2 = edgec3 = 0;
            }
        }
    }
    printf("\n%d", trictr);
    return 0;
}