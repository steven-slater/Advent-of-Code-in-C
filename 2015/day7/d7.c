#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char *buffer;
    FILE *fp;
    fp = fopen("s1.txt", "rb");
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
    char operator[2];
    char *token;
    int amt = 0;
    int regx = 0;
    int regy = 0;
    while (fileindex < fileSize) {
        int lineIndex = 0;
        if (buffer[fileindex] == '\n' || buffer[fileindex] == '\r') {
            fileindex++;
        }
        while (fileindex < fileSize && buffer[fileindex] != '\n' &&
               buffer[fileindex] != '\r') {
            line[lineIndex++] = buffer[fileindex++];
        }
        line[lineIndex] = '\0';
        int len = strlen(line);

        printf("%s %ld\n", line, len);

        token = strtok(line, " ");
        printf("first token: %s\n", token);
        char c = token[0];
        if (isdigit(c)) {
            amt = atoi(token);
            printf("%d\n", amt);
            token = strtok(NULL, ">");
            printf("second token: %s\n", token);
            token = strtok(NULL, " ");
            printf("third token: %s\n", token);
        } else {
            operator[0] = c;
            operator[1] = '\0';
            printf("first char is not digit\n");
        }

        if (fileindex < fileSize && buffer[fileindex] == '\n') {
            fileindex++;
        }
    }
    return 0;
}