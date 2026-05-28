#include <stdio.h>
#include "uthash.h"
typedef struct
{
    char key[50];
    int value;
    int index;
    UT_hash_handle hh; // makes this struct hashable
} Entry;

Entry *table = NULL;
void printTable(Entry *table)
{
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp)
    {
        printf("key: '%s' value: %d\n", current->key, current->value);
    }
    printf("---\n"); // set breakpoint on this line
}
int main()
{
    FILE *fp = fopen("p1.txt", "rb");
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
    // printf("fileSize: %ld\n", fileSize);
    // printf("buffer ptr: %p\n", (void *)buffer);      // NULL means malloc failed
    long bytesRead = fread(buffer, 1, fileSize, fp); // swap args: 1, fileSize
    // printf("bytesRead: %ld\n", bytesRead);
    // printf("feof: %d, ferror: %d\n", feof(fp), ferror(fp));

    fclose(fp);
    char *vowels = "aeiouAEIOU";
    char *naughty = "ab|cd|pq|xy";
    char firstnaughty[4] = {'a', 'c', 'p', 'x'};
    char *vowelPtr = NULL;
    char *line = NULL;
    int nicestrings = 0;
    int lineIndex = 0;

    for (int fileIndex = 0; lineIndex < fileSize; fileIndex++)
    {
        int count = 0;
        // if (fileIndex + lineIndex >= 520)
        // {
        //     printf("fileIndex: %d, lineIndex: %d\n", fileIndex, lineIndex);
        // }
        line = calloc(17, sizeof(char));
        for (int k = 0; k < 17; k++)
        {
            line[k] = buffer[lineIndex++];
        }
        line[strcspn(line, "\r\n")] = '\0'; // Remove newline characters from the line
                                            //        line[16] = '\0';
        printf("%s\n", line);
        lineIndex += 1; // skip newline character
        vowelPtr = NULL;
        //  nicestrings = 0;
        // while (fgets(buffer, fileSize + 1, fp))
        //{
        int vowelCount = 0;
        int doublesCount = 0;
        size_t length = strlen(line);

        for (int i = 0; i < length; i++)
        {
            if (fileIndex + lineIndex >= 540 && i >= 5)
            {
                printf("i: %d %c %s\n", i, line[i], line);
            }
            char c[2] = {line[i], '\0'};
            if (c[0] == firstnaughty[0] && line[i + 1] == 'b' ||
                c[0] == firstnaughty[1] && line[i + 1] == 'd' ||
                c[0] == firstnaughty[2] && line[i + 1] == 'q' ||
                c[0] == firstnaughty[3] && line[i + 1] == 'y')
            {
                printf("Naughty string: '%s'\n", line);
                count++;
                break;
            }
            if (vowelPtr = strchr(vowels, line[i]))
            {
                vowelCount++;
            }
            Entry *found;
            HASH_FIND_STR(table, c, found);
            if (found)
            {
                if (found->index == i - 1)
                {
                    doublesCount++;
                    found->index++;
                }
                else
                {
                    found->index++;
                }
            }
            else
            {
                Entry *entry = calloc(1, sizeof(Entry));
                snprintf(entry->key, sizeof(entry->key), "%c", line[i]);
                entry->value = 1;
                entry->index = i;
                HASH_ADD_STR(table, key, entry);
            }
            //  printf("%c\n", line[i]);
            // printTable(table);
        }
        if (vowelCount >= 3 && doublesCount >= 1 && count == 0)
        {
            printf("Nice string: '%s'\n", line);
            // printTable(table);
            nicestrings++;
        }
        free(line);
        Entry *current, *tmp;
        HASH_ITER(hh, table, current, tmp)
        {
            //  printf("'%s': %d\n", current->key, current->value);
            HASH_DEL(table, current); // remove from table
            free(current);            // free memory
        }
    }
    printf("Number of nice strings: %d\n", nicestrings);
    // free(buffer);

    return 0;
}