#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    char *token;
    // char buffer[2050];
    char *buffer;
    long filesize;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);

    printf("%ld\n", filesize);
    buffer = (calloc(filesize + 1, sizeof(char)));
    rewind(fp);
    long bytesRead = fread(buffer, sizeof(char), filesize, fp);

    char next[4];
    int subtot = 0;
    int total = 0;

    buffer[strcspn(buffer, "\r\n")] = '\0';
    int len = strlen(buffer);
    int step = len / 2;
    printf("%s\n", buffer);
    int first = 0;
    char firstc[2];
    // printf("%s\n%d\n", left, strlen(left));
    for (int i = 0; i < len / 2; i++) {

        strncpy(firstc, buffer + i, 1);
        first = atoi(firstc);

        char nextc[2];
        strncpy(nextc, buffer + step + i, 1);
        int next = atoi(nextc);
        printf("%d ? %d %d\n", first, next, subtot);
        if (first == next) {
            subtot += first + next;
        }
    }
    total += subtot;
    subtot = 0;

    printf("%d\n", total);
    return 0;
}