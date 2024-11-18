#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
printf("Esecuzione di ls...\n");
execl("/bin/ls", "ls", "-l", NULL);
perror("La chiamata di execl ha generato un errore");
return 1;
}
