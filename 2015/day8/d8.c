#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fp;
    fp = fopen("s1.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    char *buffer = (char *)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Error allocating memory\n");
        fclose(fp);
        return 1;
    }

    fread(buffer, sizeof(char), file_size, fp);
    char line[100];
    int file_pos = 0;
    while (file_pos < file_size) {
        int lineindex = 0;

        // Read the line until we hit a newline or the end of the file
        while (file_pos < file_size && buffer[file_pos] != '\n' &&
               buffer[file_pos] != '\r') {
            line[lineindex++] = buffer[file_pos++];
        }

        // Null-terminate the string immediately
        line[lineindex] = '\0';
        int len = strlen(line);
        printf("%s is %d characters long\n", line, len);
        for (int i = 0; i < len; i++) {
            //            printf("%c ", line[i]);
            if (line[i] == '\\') {
                printf("(backslash) at index %d\n", i - 1);
            }
        }
        // Skip ALL trailing newline/return characters (\n, \r, or \r\n)
        while (file_pos < file_size &&
               (buffer[file_pos] == '\n' || buffer[file_pos] == '\r')) {
            file_pos++;
        }
    }

    free(buffer);
    fclose(fp);
    return 0;
}