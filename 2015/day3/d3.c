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
    int n = length;

    int x = fileSize / 2, y = fileSize / 2;
    int xR = fileSize / 2, yR = fileSize / 2;
    int needed = snprintf(NULL, 0, "%d%d", x, y);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            count++;
        }
        char *key = calloc(needed + 1, sizeof(char)); // +1 for null terminator
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
        i++;
        char *keyR = calloc(needed + 1, sizeof(char)); // +1 for null terminator
        snprintf(keyR, needed + 1, "%d%d", xR, yR);
        char *currentCoordR = keyR;

        // printf("currentCoord: %s\n", currentCoord);
        inserted = 0;
        for (int j = 0; j < t; j++)
        {
            int res = strcmp(visited[j], ".");
            // printf("visited: %s\n", visited[j]);

            if (res == 0)
            {
                visited[j] = currentCoordR;
                count++;
                inserted = 1;
                printf("inserted: %s\n", visited[j]);
                break;
            }
            else if (strcmp(visited[j], currentCoordR) == 0)
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
            free(keyR);
        }

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
    }
    count = 0;
    for (int k = 0; k < t; k++)
    {
        int res = strcmp(visited[k], ".");
        // printf("visited: %s\n", visited[k]);

        if (res == 0)
        {
            break;
        }
        else
        {
            count++;
        }
    }
    // if (count == 1)
    // {
    //     count++;
    // }
    printf("count: %d\n", count);
    return 0;
}