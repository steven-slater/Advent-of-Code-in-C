#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str = "1113222113";
    // strcpy(str, "211");
    // strcpy(str, "1");
    printf("Number: %s\n", str);
    int howmany = 1;
    int current = 0;
    int buffcounter = 0;

    char *buffer = calloc(1000000, sizeof(char));
    int buffindex = 0;
    while (buffcounter < 40) {
        if (buffcounter == 18) {
            printf("Halfway there!\n");
        }
        for (int i = 0; i < strlen(str); i++) {
            current = str[i] - '0';
            int next = str[i + 1] - '0';
            if (current == next) {
                while (current == next) {
                    howmany++;
                    i++;
                    next = str[i + 1] - '0';
                }
            }
            if (howmany == 1) {
                buffer[buffindex++] = howmany + '0';
                buffer[buffindex++] = current + '0';
                // buffer[buffindex] = '\0';
                continue;
            }
            printf("Current: %d loc: %d howmany: %d\n", current, i, howmany);
            buffer[buffindex++] = howmany + '0';
            buffer[buffindex++] = current + '0';
            // buffer[buffindex] = '\0';
            howmany = 1;
        }
        strcpy(str, buffer);
        printf("Len: %lu\n", strlen(str));
        buffcounter++;
        free(buffer);
        buffer = calloc(1000000, sizeof(char));
        buffindex = 0;
    }
    return 0;
}