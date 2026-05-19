#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fp = fopen("s1.txt", "r");
  char buffer[100];

  if (fp == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  char *parts[3] = {NULL, NULL, NULL}; // Good practice: initialize to NULL
  char delim[] = "x";
  int index = 0;

  // 1. READ THE FILE FIRST
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    // Clean the trailing newline if it exists so it doesn't mess up parts[2]
    buffer[strcspn(buffer, "\n")] = '\0';

    size_t length = strlen(buffer);
    printf("Raw length: %zu\n", length);

    // 2. NOW TOKENIZE THE LOADED BUFFER
    char *token = strtok(buffer, delim);
    while (token != NULL && index < 3)
    {
      parts[index] = token;
      index++;
      token = strtok(NULL, delim);
    }

    // 3. PRINT THE RESULTS
    for (int i = 0; i < index; i++)
    {
      printf("Part %d: %s\n", i + 1, parts[i]);
    }
  }

  fclose(fp); // Don't forget to close your file!
  return 0;
}