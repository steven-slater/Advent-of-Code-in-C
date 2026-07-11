#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"
typedef struct {
    int x;
    int y;
} PointKey;
typedef struct {
    PointKey key;
    bool state;
    UT_hash_handle hh;
} PointMap;

PointMap *grid = NULL;
void add_location(int x, int y, bool state) {
    PointMap *item;

    // RULE 2: Use calloc (or memset) to guarantee all hidden padding bytes are
    // 0
    item = calloc(1, sizeof(PointMap));
    if (!item)
        return;

    item->key.x = x;
    item->key.y = y;
    item->state = state;
    // strncpy(item->location_name, name, sizeof(item->location_name) - 1);

    // HASH_ADD(handle, head, key_field_name, key_length_in_bytes, item_ptr)
    HASH_ADD(hh, grid, key, sizeof(PointKey), item);
}
/**
 * Looks up an element using an inline composite coordinate key
 */
PointMap *find_location(int x, int y) {
    PointMap *result = NULL;

    // Create a temporary key lookup block and zero it out completely
    PointKey lookup_key;
    memset(&lookup_key, 0, sizeof(PointKey));
    lookup_key.x = x;
    lookup_key.y = y;

    // HASH_FIND(handle, head, ptr_to_lookup_key, key_length_in_bytes, out_ptr)
    HASH_FIND(hh, grid, &lookup_key, sizeof(PointKey), result);
    return result;
}
void turn_on_pixels(int wide, int tall) {
    PointMap *result;
    for (int i = 0; i < tall; i++) {
        for (int j = 0; j < wide; j++) {
            result = find_location(i, j);
            result->state = 1;
            printf("%d", result->state);
        }
        printf("\n");
    }
}
void print_grid(int wide, int tall) {
    PointMap *result;
    printf("\n");
    for (int i = 0; i < tall; i++) {
        for (int j = 0; j < wide; j++) {
            result = find_location(i, j);
            if (result != NULL) {
                printf("%d", result->state);
            } else {
                printf("Error at: (%d %d)", i, j);
            }
        }
        printf("\n");
    }
}
int main() {
    int ROWMAX = 3;
    int COLMAX = 7;
    int row = 0;
    int col = 0;
    int grid[7][3];
    // add_location(10, 20, 1);
    // add_location(5, -12, 1);
    // add_location(0, 0, 1);

    // Search for a specific coordinate tuple
    // int search_x = 5;
    // int search_y = -12;
    // PointMap *found = find_location(search_x, search_y);

    // if (found) {
    //     printf("Found location at (%d, %d): %d\n", search_x, search_y,
    //            found->state);
    // } else {
    //     printf("Location (%d, %d) not discovered.\n", search_x, search_y);
    // }

    for (int i = 0; i < ROWMAX; i++) {
        for (int j = 0; j < COLMAX; j++) {
            add_location(i, j, 0);
        }
    }
    print_grid(COLMAX, ROWMAX);
    FILE *fp = fopen("s1.txt", "rb");
    long filesize = 0;
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    char *buffer = calloc(filesize + 1, sizeof(char));
    long bytesread = fread(buffer, sizeof(char), filesize, fp);
    if (bytesread != filesize) {
        perror("fread");
    }
    fclose(fp);
    char *token;
    long fileindex = 0;
    int lineindex = 0;
    char temp[256];
    int linectr = 0;
    int amount = 0;

    while (fileindex < filesize) {
        char *line = calloc(512, sizeof(char));
        int lineindex = 0;
        while (buffer[fileindex] == '\r' || buffer[fileindex] == '\n') {
            fileindex++;
        }
        while (fileindex < filesize && buffer[fileindex] != '\r' &&
               buffer[fileindex] != '\n') {
            line[lineindex++] = buffer[fileindex++];
        }
        line[lineindex] = '\0';
        printf("%s\n", line);
        int len = strlen(line);
        lineindex = 0;
        int tokctr = 0;
        token = strtok(line, " ");

        while (token != NULL) {
            tokctr++;
            token = strtok(NULL, " ");
            if (token == NULL) {
                continue;
            }
            if (isdigit((unsigned char)token[0])) {
                // RECT command, turn on pixels
                int successfully_parsed = sscanf(token, "%dx%d", &col, &row);
                printf("%dx%d\n", col, row);
                turn_on_pixels(col, row);
                print_grid(COLMAX, ROWMAX);
            } else {
                printf("ROTATE");
                // col or row?
                switch (token[0]) {
                case 'c':
                    /* code */
                    break;

                default:
                    break;
                }
                token = strtok(NULL, " ");
            }
        }
    }
}