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

void printGrid(int grid[1000][1000])
{
    int counter = 0;
    int brightness = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {

            if (grid[i][j])
            {
                counter++;
            }

            brightness += grid[i][j];
        }
        // printf("\n");
    }
    printf("Total lights on: %d\n", counter);
    printf("Total brightness: %d\n", brightness);
}
int lights[1000][1000]; // initialize all lights to off

int main()
{
    bool part2 = true;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            lights[i][j] = 0; // start with all lights off
            // printf("%d", lights[i][j]);
        }
    }

    char *token;
    FILE *fp;
    int coordindex = 0;
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
        token = strtok(line, " ");
        printf("%s\n", token);
        //   while (token != NULL)
        // {
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
            turnon = false;
        }
        else
        {
            toggle = false;
        }

        token = strtok(NULL, ", ");
        printf("colstart: %s\n", token);
        current->colstart = atoi(token);
        token = strtok(NULL, ", ");
        printf("rowstart: %s\n", token);
        current->rowstart = atoi(token);
        token = strtok(NULL, ", ");
        token = strtok(NULL, ", ");
        printf("colend: %s\n", token);
        current->colend = atoi(token);
        token = strtok(NULL, ", ");
        printf("rowend: %s\n", token);
        current->rowend = atoi(token);
        token = strtok(NULL, ", ");

        for (int gridindex = current->rowstart; gridindex <= current->rowend; gridindex++)
        {
            for (int j = current->colstart; j <= current->colend; j++)
            {
                if (toggle)
                {
                    if (part2)
                    {
                        lights[gridindex][j] += 2;
                    }
                    else
                    { //                      printf("%d", lights[gridindex][j]);
                        lights[gridindex][j] = !lights[gridindex][j];
                        //                        printf("%d", lights[gridindex][j]);
                    }
                }
                else
                {
                    if (part2)
                    {
                        if (turnon)
                        {
                            lights[gridindex][j]++;
                        }
                        else
                        {
                            if (lights[gridindex][j] > 0)
                            {
                                lights[gridindex][j]--;
                            }
                        }
                    }
                    else
                    {
                        if (part2 == false)
                        {
                            lights[gridindex][j] = turnon;
                        }
                    }
                }
            }
        }
        free(current);
    }
    // Clean up
    free(buffer);
    printGrid(lights);
    fclose(fp);
    return 0;
}
