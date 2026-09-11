#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS 27
#define ROWS 250
int compare_rows(const void *a, const void *b) {
    const char (*pa)[COLS] = a;
    const char (*pb)[COLS] = b;
    return strcmp(*pa, *pb);
}
int main(void) {
    FILE *fp = fopen("p1.txt", "rb");
    if (fp == NULL) {
        perror("Can't open file");
        return 1;
    }
    int totals = 0;
    int twos = 0;
    int threes = 0;
    const char *alph = "abcdefghijklmnopqrstuvwxyz";
    int alpha[26];
    char buffer[64];
    char firstw[28];
    char nextw[28];
    int index = 0;
    char start[28];
    char end[28];
    char grid[250][27];
    while (fgets(buffer, COLS + 3, fp) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        snprintf(grid[index++], sizeof(grid[0]), "%s", buffer);
    }
    qsort(grid, ROWS, sizeof(grid[0]), compare_rows);
    for (int i = 0; i < index; i++) {
        for (int i = 0; i < 26; i++) {
            firstw[i] = '\0';
            nextw[i] = '\0';
        }
        char answer[27];
        strcpy(start, grid[i]);
        for (int j = i + 1; j < index; j++) {
            strcpy(end, grid[j]);
            int df = 0;
            // for (int k = 0; k < strlen(start); k++) {
            //     for (int j = 0; j < 26; j++) {
            //         char c = start[k];
            //         if (c == alph[j]) {
            //             firstw[j]++;
            //             break;
            //         }
            //     }
            //     for (int j = 0; j < 26; j++) {
            //         char c = end[k];
            //         if (c == alph[j]) {
            //             nextw[j]++;
            //             break;
            //         }
            //     }
            // }
            // // check for < 1 diff
            // totals = 0;
            // for (int p = 0; p < strlen(firstw); p++) {
            //     if (firstw[p] == nextw[p]) {
            //         totals++;
            //     }
            // }

            int ndx = 0;
            char *ans = calloc(strlen(start), sizeof(char));
            int len = strlen(start);
            printf("%s == %s\n", start, end);
            for (int z = 0; z <= strlen(start); z++) {
                if (start[z] == end[z]) {
                    ans[ndx++] = start[z];
                    answer[ndx - 1] = start[z];
                } else {
                    df++;
                    if (df > 1) {
                        j = index;
                        free(ans);
                        break;
                    }
                }
            }
            if (df == 1) {
                printf("%s\n", ans);
            }
        }
    }

    printf("%d\n", twos * threes);
    return 0;
}