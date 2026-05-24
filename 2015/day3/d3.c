#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int t = 5000;
    char *visited[5000] = {NULL};
    for (int i = 0; i < t; i++)
    {
        visited[i] = ".";
    }

    // Coord *visited = calloc(t, sizeof(Coord));
    FILE *fp = fopen("p1.txt", "r");

    // Get file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp); // reset back to beginning

    // Allocate buffer based on file size (+1 for null terminator)
    char *buffer = malloc(fileSize + 1);

    fgets(buffer, fileSize + 1, fp);
    buffer[strcspn(buffer, "\n")] = '\0';
    size_t length = strlen(buffer);

    char *ptr = calloc(length + 1, sizeof(char));
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        ptr[i] = buffer[i];
    }
    // Coord *temp = realloc(visited, t * sizeof(Coord));
    // visited = temp;
    int num_of_instructions = length;
    int x, y = 0;
    int xR, yR = 0;
    if (fileSize < 1000)
    {
        x = 500, y = 500;

        xR = 500, yR = 500;
    }
    else
    {
        x = fileSize / 2, y = fileSize / 2;
        xR = fileSize / 2, yR = fileSize / 2;
    }
    int needed = snprintf(NULL, 0, "%d%d", x, y);
    char *key = calloc(needed + 1, sizeof(char)); // +1 for null terminator
    snprintf(key, needed + 1, "%d%d", x, y);

    for (int i = 0; i < num_of_instructions; i++)
    {
        if (i == 0)
        {

            visited[0] = key;
            count++;
            printf("inserted: %s\n", visited[0]);
        }

        char current = ptr[i];

        switch (current)
        {
        case '^':
            x--;
            break;
        case '>':
            y++;
            break;
        case 'v':
            x++;
            break;
        case '<':
            y--;
            break;
        }
        key = calloc(needed + 1, sizeof(char)); // +1 for null terminator
        snprintf(key, needed + 1, "%d%d", x, y);
        //      printf("key: %s\n", key);
        char *currentCoord = key;
        // printf("currentCoord: %s\n", currentCoord);
        int inserted = 0;
        for (int j = 0; j < t; j++)
        {
            int res = strcmp(visited[j], ".");
            // printf("visited: %s\n", visited[j]);

            if (res == 0)
            {
                visited[j] = currentCoord;
                count++;
                inserted = 1;
                printf("inserted: %s\n", visited[j]);
                break;
            }
            else if (strcmp(visited[j], currentCoord) == 0)
            { // already visited, skip
                printf("duplicate: %s\n", currentCoord);
                break;
            }
            else
            {
                continue;
            }
        }

        if (!inserted)
        {
            free(key);
        }

        i++;
        current = ptr[i];

        switch (current)
        {
        case '^':
            xR--;
            break;
        case '>':
            yR++;
            break;
        case 'v':
            xR++;
            break;
        case '<':
            yR--;
            break;
        }
        key = calloc(needed + 1, sizeof(char)); // +1 for null terminator
        snprintf(key, needed + 1, "%d%d", xR, yR);
        //      printf("key: %s\n", key);
        currentCoord = key;
        for (int j = 0; j < t; j++)
        {
            int res = strcmp(visited[j], ".");
            // printf("visited: %s\n", visited[j]);

            if (res == 0)
            {
                visited[j] = currentCoord;
                count++;
                inserted = 1;
                printf("inserted: %s\n", visited[j]);
                break;
            }
            else if (strcmp(visited[j], currentCoord) == 0)
            { // already visited, skip
                printf("duplicate: %s\n", currentCoord);
                break;
            }
            else
            {
                continue;
            }
        }

        if (!inserted)
        {
            free(key);
        }
    }

    printf("count: %d\n", count);
    return 0;
}