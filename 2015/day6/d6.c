#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    fp = fopen("p1.txt", "rb");
    if (fp == NULL)
    {
        perror("Can't open file");
        return 1;
    }
    // Get file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp); // reset back to beginning

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL)
    {
        perror("Can't allocate memory");
        fclose(fp);
        return 1;
    }
    // Read file contents into buffer
    fread(buffer, sizeof(char), fileSize, fp);
    buffer[fileSize] = '\0'; // Null-terminate the string

    // Do something with the buffer, e.g., print its contents
    printf("%s", buffer);

    // Clean up
    free(buffer);
    fclose(fp);
    return 0;
}