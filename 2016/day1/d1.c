#include "uthash.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    bool notdone = true;
    FILE *fp = fopen("p1.txt", "rb");
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    char *buffer;
    buffer = calloc(1, filesize + 1);
    fread(buffer, sizeof(char), filesize, fp);
    return 0;
}
