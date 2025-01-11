#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char *fgetline(char *line, FILE *file);

int main(int argc, char **argv)
{
    if(argc < 3) {
        fprintf(stderr, "Vanno specificati due file in input.\n");
        return 1;
    }

    char *filename1 = argv[1];
    char *filename2 = argv[2];

    FILE *file1 = fopen(filename1, "r");
    if(!file1) {
        fprintf(stderr, "Impossibile aprire il file %s: %s\n",
                        filename1, strerror(errno));
        return 1;
    }

    FILE *file2 = fopen(filename2, "r");
    if(!file2) {
        fprintf(stderr, "Impossibile aprire il file %s: %s\n",
                        filename2, strerror(errno));
        return 1;
    }

    char *line1 = NULL;
    char *line2 = NULL;

    int n = 0;
    do {
        ++n;
        line1 = fgetline(line1, file1);
        line2 = fgetline(line2, file2);
    } while(line1 != NULL && line2 != NULL && strcmp(line1, line2) == 0);

    if(line1 == NULL && line2 == NULL)
        printf("I due file sono identici\n");
    else {
        printf("I file differiscono alla riga %d\n", n);
        if(line1 && line1[0])
            printf("  Riga %d in '%s': %s\n", n, filename1, line1);
        else
            printf("  Riga vuota o file '%s' terminato\n", filename1);

        if(line2 && line2[0])
            printf("  Riga %d in '%s': %s\n", n, filename2, line2);
        else
            printf("  Riga vuota o file '%s' terminato\n", filename2);
    }

    free(line1);
    free(line2);

    return 0;
}

char *fgetline(char *line, FILE *file)
{
    int size = 0;
    int read = 0;

    if(feof(file)) {
        free(line);
        return NULL;
    }

    if(line != NULL)
        size = strlen(line) + 1;

    for(char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file), ++read)
    {
        if(read == size) {
            size = size * 2 + 1;
            line = realloc(line, size);
        }

        line[read] = c;
    }

    line[read] = 0;

    return line;
}
