#include <stdio.h>
#include <string.h>
#include <errno.h>
int main(int argc, char **argv) {
if(argc < 2) {
fprintf(stderr, "Specificare il nome di un file\n");
return 1;
}
FILE *file = fopen(argv[1], "r");
if(file == NULL) {
fprintf(stderr, "%s: Impossibile aprire %s: %s\n",
argv[0], argv[1], strerror(errno));
return 2;
}
return 0;
}
