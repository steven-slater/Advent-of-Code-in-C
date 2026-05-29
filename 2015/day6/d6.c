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
Coords coords[1000];
int main()
{
    Coords coords[1000];
    char *token;
    FILE *fp;
    int coordindex = 0;
    fp = fopen("s1.txt", "rb");
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
    bool turnon = false;
    bool toggle = false;
    int i = 0;
    while (i < bytesRead)
    {
        if (buffer[i] == '\n' || buffer[i] == '\r')
        {
            i++;
        }

        Coords *current = malloc(sizeof(Coords));

        lineindex = 0;
        while (i < bytesRead && buffer[i] != '\n' && buffer[i] != '\r')
        {
            line[lineindex++] = buffer[i];
            i++;
        }
        line[lineindex] = '\0'; // Null-terminate the line
        if (lineindex == 0)
        {
            continue;
        }
        // printf("%s\n", line);
        token = strtok(line, ", ");
        printf("%s\n", token);
        while (token != NULL)
        {
            int comp = stricmp("turn", token);
            if (comp == 0)
            {
                token = strtok(NULL, ", ");
                printf("%s\n", token);
                if (stricmp("on", token) == 0)
                {
                    turnon = true;
                }
                else
                {
                    turnon = false;
                }
            }

            comp = stricmp("toggle", token);
            if (comp == 0)
            {
                toggle = true;
            }
            else
            {
                toggle = false;
            }

            token = strtok(NULL, ", ");
            printf("colstart: %s\n", token);
            current->colstart = atoi(token);
            token = strtok(NULL, ", ");
            printf("colend: %s\n", token);
            current->colend = atoi(token);
            token = strtok(NULL, ", ");
            token = strtok(NULL, ", ");
            printf("rowstart: %s\n", token);
            current->rowstart = atoi(token);
            token = strtok(NULL, ", ");
            printf("rowend: %s\n", token);
            current->rowend = atoi(token);
            token = strtok(NULL, ", ");
        }
        coords[coordindex++] = *current;
        //  free(current);
    }
    // Do something with the buffer, e.g., print its contents
    for (int j = 0; j < coordindex; j++)
    {
        Coords c = coords[j];
        printf("Row start: %d, Col start: %d, Row end: %d, Col end: %d\n", c.rowstart, c.colstart, c.rowend, c.colend);
    }
    //    printf("%s", buffer);

    // Clean up
    free(buffer);
    free(coords);
    fclose(fp);
    return 0;
}
