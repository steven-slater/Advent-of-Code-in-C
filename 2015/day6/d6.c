#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct
{
    int rowstart;
    int colstart;
    int rowend;
    int colend;
} Coords;
int main()
{
    Coords coords[1000];
    char *token;
    FILE *fp;
    char *options;
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
    char line[100]; // buffer for each line
    // Read file contents into buffer
    long bytesRead = fread(buffer, sizeof(char), fileSize, fp);
    buffer[fileSize] = '\0'; // Null-terminate the string
    int lineindex = 0;
    bool turnon = true;
    bool toggle = false;
    for (int i = 0; i < bytesRead; i++)
    {
        Coords *current = malloc(sizeof(Coords));

        lineindex = 0;
        while (buffer[i] != '\n' && buffer[i] != '\r')
        {
            line[lineindex++] = buffer[i];
            i++;
        }
        line[lineindex] = '\0'; // Null-terminate the line
        lineindex = 0;
        // printf("%s\n", line);
        token = strtok(line, ", ");
        printf("%s\n", token);
        while (token != NULL)
        {
            stricmp("toggle", token) == 0 ? toggle = true : false;

            token = strtok(NULL, ", ");
            printf("colstart: %s\n", token);
            current->colstart = atoi(token);
            token = strtok(NULL, ", ");
            printf("colend: %s\n", token);
            current->colend = atoi(token);
            token = strtok(NULL, " ");
            token = strtok(NULL, ", ");
            printf("rowstart: %s\n", token);
            current->rowstart = atoi(token);
            token = strtok(NULL, ", ");
            printf("rowend: %s\n", token);
            current->rowend = atoi(token);
        }
        free(current);
    }
    // Do something with the buffer, e.g., print its contents
    printf("%s", buffer);

    // Clean up
    free(buffer);
    fclose(fp);
    return 0;
}
