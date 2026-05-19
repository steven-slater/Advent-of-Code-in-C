#include <stdio.h>
#include <string.h>
// int compare_str(const void *a, const void *b)
// {
//   return strcmp(*(const char **)a, *(const char **)b); // ascending (A-Z)
// }
int compare_int(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b); // ascending
                                  // return (*(int*)b - *(int*)a); // descending
}
int main()
{
  FILE *fp = fopen("s1.txt", "r");
  char buffer[100];
  int pints[3];
  if (fp == NULL)
  {
    perror("Error opening file");
    return 1;
  }
  int grandtotal = 0;
  int part2total = 0;
  char *parts[3] = {NULL, NULL, NULL}; // Good practice: initialize to NULL
  char delim[] = "x";
  int index = 0;
  int smallest = 0;
  // 1. READ THE FILE FIRST
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    // Clean the trailing newline
    buffer[strcspn(buffer, "\n")] = '\0';

    size_t length = strlen(buffer);
    //    printf("Raw length: %zu\n", length);

    // get the tokens
    char *token = strtok(buffer, delim);
    while (token != NULL && index < 3)
    {
      if (index > 0)
      {
        if (pints[index - 1] > atoi(token))
        {
          smallest = index;
        }
      }
      //    printf("%s ", token);
      pints[index] = atoi(token);
      parts[index] = token;
      index++;
      token = strtok(NULL, delim);
    }

    // Calculate

    index = 0;
    // parts.sort(parts, parts + 3); // Sort the dimensions to easily find the smallest
    // pints.sort(pints, pints + 3); // Sort the dimensions to easily find the smallest
    //  qsort(parts, 3, sizeof(char *), compare_str);

    qsort(pints, 3, sizeof(int), compare_int);
    int lxw = pints[0] * pints[1];
    int lxh = pints[0] * pints[2];
    int wxh = pints[1] * pints[2];
    // for part 2
    int perimeter = pints[0] * 2 + pints[1] * 2;
    int bow = pints[0] * pints[1] * pints[2];
    int ribbon = bow + perimeter;
    // end part 2

    int smallest_area = lxw < lxh ? (lxw < wxh ? lxw : wxh) : (lxh < wxh ? lxh : wxh);
    int total_area = 2 * (lxw + lxh + wxh) + smallest_area;
    // printf("Total area: %d\n", total_area);
    grandtotal += total_area;
    part2total += ribbon;
    // printf("Running grand total: %d\n", grandtotal);
  }
  fclose(fp);
  printf("Final: %d\n", grandtotal);
  printf("Part 2 total: %d\n", part2total);
  return 0;
}