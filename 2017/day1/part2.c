#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("s1.txt", "rb");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    char *token;
    char buffer[2050];
    char left[1050];
    char right[1050];
    char key[4];
    int weight;
    char next[4];
    int subtot = 0;
    int total = 0;
    while (fgets(buffer, 2037, fp) != '\0') {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        int len = strlen(buffer);
        strncpy(left, buffer, (len / 2) + 1);
        left[(len / 2)] = '\0';
        strncpy(right, buffer + (len / 2), ((len / 2) + 1));
        int first = 0;
        char firstc[2];
        printf("%s\n", left);
        for (int i = 0; i < len / 2; i++) {
            // if (i == len - 1) {
            //     // check last against first
            //     strncpy(firstc, left + i, 1);
            //     first = atoi(firstc);
            //     char lastc[2];
            //     strncpy(lastc, right + i, 1);
            //     int last = atoi(lastc);
            //     if (first == last) {
            //         subtot += first;
            //     }
            //     continue;
            // }

            strncpy(firstc, left + i, 1);
            first = atoi(firstc);

            char nextc[2];
            strncpy(nextc, right + i, 1);
            int next = atoi(nextc);
            if (first == next) {
                subtot += first + next;
            }
        }
        total += subtot;
        subtot = 0;
    }
    printf("%d\n", total);
    return 0;
}