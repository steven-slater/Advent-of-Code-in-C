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
    char buffer[2050];
    char key[4];
    int weight;
    char next[4];
    int subtot = 0;
    int total = 0;
    while (fgets(buffer, 2037, fp) != '\0') {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        int len = strlen(buffer);
        int first = 0;
        char firstc[2];
        printf("%s\n", buffer);
        for (int i = 0; i < len; i++) {
            if (i == len - 1) {
                // check last against first
                strncpy(firstc, buffer, 1);
                first = atoi(firstc);
                char lastc[2];
                strncpy(lastc, buffer + (len - 1), 1);
                int last = atoi(lastc);
                if (first == last) {
                    subtot += first;
                }
                continue;
            }

            strncpy(firstc, buffer + i, 1);
            first = atoi(firstc);

            char nextc[2];
            strncpy(nextc, buffer + 1 + i, 1);
            int next = atoi(nextc);
            if (first == next) {
                subtot += first;
            }
        }
        total += subtot;
        subtot = 0;
    }
    printf("%d\n", total);
    return 0;
}