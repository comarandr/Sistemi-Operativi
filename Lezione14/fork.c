#include <stdio.h>
#include <unistd.h>
int main()
{
printf("Un solo processo con PID %d.\n", (int)getpid());
printf("Chiamata a fork...\n");
pid_t pid=fork();
if(pid == 0)
printf("Sono il processo figlio (PID: %d).\n", (int)getpid());
else if(pid > 0)
printf("Sono il genitore del processo con PID %d.\n",pid);
else
fprintf(stderr,
"Si e’ verificato un errore nella chiamata a fork.\n");
return 0;
}
