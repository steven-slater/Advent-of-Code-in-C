#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
        return 1;
    }
    int totals = 0;
    int twos = 0;
    int threes = 0;
    char *alph = "abcdefghijklmnopqrstuvwxyz";
    int alpha[52];
    char buffer[64];
    while (fgets(buffer, 28, fp) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        for (int i = 0; i < 52; i++) {
            alpha[i] = 0;
        }
        int len = strlen(buffer);
        char *test = calloc(len, sizeof(char));
        strcpy(test, buffer);
        printf("%s\n", test);
        for (int i = 0; i < len; i++) {
            char c = test[i];
            for (int j = 0; j < 26; j++) {
                if (c == alph[j]) {
                    alpha[j]++;
                    break;
                }
            }
        }
        for (int k = 0; k < 52; k++) {
            if (alpha[k] == 2) {
                twos++;
                break;
            }
        }
        for (int k = 0; k < 52; k++) {
            if (alpha[k] == 3) {
                threes++;
                break;
            }
        }
    }
    printf("%d\n", twos * threes);
    return 0;
}