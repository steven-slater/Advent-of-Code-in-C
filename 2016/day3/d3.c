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
    int edgea, edgeb, edgec;
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
        edgea = side;
        objctr++;
        token = strtok(NULL, " ");
        while (token != NULL) {

            side = atoi(token);
            if (objctr % 3 == 1) {
                edgeb = side;

            } else {
                edgec = side;
            }
            objctr++;
            token = strtok(NULL, " ");
        }
        if (edgea + edgeb > edgec && edgeb + edgec > edgea &&
            edgea + edgec > edgeb) {
            trictr++;
        }
    }
    printf("%d", trictr);
    return 0;
}