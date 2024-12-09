#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
int main(int argc, char **argv)
{
if(argc < 2) {
fprintf(stderr, "Specificare il PID di un processo\n");
return 1;
}
char *endptr = NULL;
pid_t pid = strtoll(argv[1], &endptr, 10);
if(*endptr != 0) {
fprintf(stderr, "Specificare il PID di un processo\n");
return 1;
}
if(kill(pid, SIGKILL) == -1) {
fprintf(stderr, "Impossibile uccidere il processo %d: %s\n", pid,
strerror(errno));
return 2;
}
return 0;
}
