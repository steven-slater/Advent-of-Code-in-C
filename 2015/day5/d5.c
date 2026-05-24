#include <stdio.h>
#include "uthash.h"
typedef struct
{
    char key[50];
    int value;
    UT_hash_handle hh; // makes this struct hashable
} Entry;

Entry *table = NULL;
void printTable(Entry *table) {
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp) {
        printf("key: '%s' value: %d\n", current->key, current->value);
    }
    printf("---\n");  // set breakpoint on this line
}
int main()
{
    FILE *fp = fopen("s1.txt", "r");
    if (fp == NULL)
    {
        perror("Can't open file");
        return 1;
    }
    // Get file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp); // reset back to beginning

    // Allocate buffer based on file size (+1 for null terminator)
    char *buffer = malloc(fileSize + 1);

    while (fgets(buffer, fileSize + 1, fp))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        size_t length = strlen(buffer);

        char *ptr = calloc(length + 1, sizeof(char));
        int count = 0;
        for (int i = 0; i < length; i++)
        {
            ptr[i] = buffer[i];
        }
        for (int i = 0; i < length; i++)
        {
            char c[2] = {ptr[i], '\0'};
            Entry *found;
            HASH_FIND_STR(table, c, found);
            if (found)
            {
                found->value++;
            }
            else
            {
                Entry *entry = calloc(1, sizeof(Entry));
                snprintf(entry->key, sizeof(entry->key), "%c", ptr[i]);
                entry->value = 1;
                HASH_ADD_STR(table, key, entry);
            }
            printf("%c", ptr[i]);
            printTable(table);
        }
        printf("\n");
    }
    // Print all entries
    Entry *current, *tmp;
    HASH_ITER(hh, table, current, tmp)
    {
        printf("'%s': %d\n", current->key, current->value);
        HASH_DEL(table, current); // remove from table
        free(current);            // free memory
    }
    free(buffer);
    // free(ptr);
    fclose(fp);
    return 0;
}