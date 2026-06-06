#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fp;
    fp = fopen("test.txt", "rb"); // rb always
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
    long totalstrinsize = 0;
    long totalinmemsize = 0;
    long grandototalinmemsize = 0;
    while (file_pos < file_size) {
        int lineindex = 0;

        // Read the line until we hit a newline or the end of the file
        while (file_pos < file_size && buffer[file_pos] != '\n' &&
               buffer[file_pos] != '\r') {
            line[lineindex++] = buffer[file_pos++];
        }
        totalinmemsize = 0;
        // Null-terminate the string immediately
        line[lineindex] = '\0';
        int len = strlen(line);

        totalinmemsize += len - 2;

        //    printf("%s is %d characters long\n", line, len);
        //    printf("Subtract 2 for quotes: %ld\n", totalinmemsize);
        for (int i = 0; i < len; i++) {
            if (line[i] == '\\') {

                if (line[i + 1] == 'x') {
                    totalinmemsize -= 3; // \xNN is 4 characters in the file but
                    i += 3;              // represents 1 character in memory
                    //                  printf("Subtract 3 for hex escape:
                    //                  %d\n", totalinmemsize);
                    continue;
                }

                if (line[i + 1] == '\\') {
                    totalinmemsize -= 1; // \\ is 2 characters in the file but
                                         // represents 1 character in memory
                    i += 1;
                    //                    printf("Subtract 1 for backslash:
                    //                    %d\n", totalinmemsize);
                    continue;
                } else {
                    totalinmemsize -= 1;
                    i += 1;
                    //  printf("Subtract 1 for regular escape: %d\n",
                    //  totalinmemsize);
                }
            }
        }
        grandototalinmemsize += totalinmemsize;
        totalstrinsize += len;
        // Skip ALL trailing newline/return characters (\n, \r, or \r\n)
        while (file_pos < file_size &&
               (buffer[file_pos] == '\n' || buffer[file_pos] == '\r')) {
            file_pos++;
        }
    }
    long finalt = totalstrinsize - grandototalinmemsize;
    printf("Total string size: %ld\n", totalstrinsize);
    printf("Total in-memory size: %ld\n", grandototalinmemsize);
    printf("Difference: %ld\n", finalt);
    free(buffer);
    fclose(fp);
    return 0;
}