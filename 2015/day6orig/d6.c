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

    char *buffer = malloc(fileSize + 1); // read entire file
    if (buffer == NULL)
    {
        perror("Can't allocate memory");
        fclose(fp);
        return 1;
    }
    char line[100];
    // Read file contents into buffer
    long bytesRead = fread(buffer, sizeof(char), fileSize, fp);
    buffer[fileSize] = '\0'; // Null-terminate the string
    int lineindex = 0;
    for (int i = 0; i < bytesRead; i++)
    {
        lineindex = 0;
        while (buffer[i] != '\n' && buffer[i] != '\r')
        {
            line[lineindex++] = buffer[i];
            i++;
        }
        line[lineindex] = '\0'; // Null-terminate the line
        printf("%s\n", line);   // Print the line
        i += 1;
    }
    // Do something with the buffer, e.g., print its contents
    printf("%s", buffer);

    // Clean up
    free(buffer);
    fclose(fp);
    return 0;
}