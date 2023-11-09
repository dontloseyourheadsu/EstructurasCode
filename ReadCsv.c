#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUMNS 4
#define SKIP_ROWS 2

int main() {
    FILE *file = fopen("file.csv", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    char line[1024];
    int sum[MAX_COLUMNS] = {0};
    int row = 0;
    int skip_rows = SKIP_ROWS;
    while (fgets(line, 1024, file)) {
    if (row >= skip_rows + 1) {  // Skip the first row and selected rows
        char *first_part = strtok(line, " ");
        char *second_part = strtok(NULL, " ");
        if (second_part != NULL) {
            char *token = strtok(second_part, ",");
            int column = 0;
            while (token != NULL && column < MAX_COLUMNS) {
                sum[column] += atoi(token);
                token = strtok(NULL, ",");
                column++;
            }
        }
    }
    row++;
}

    fclose(file);

    for (int i = 0; i < MAX_COLUMNS; i++) {
        printf("Sum of column %d: %d\n", i+1, sum[i]);
    }

    return 0;
}