#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MSGSIZE 14
int main() {
int pipes[2] = { };
if(pipe(pipes) == -1) {
perror("pipe call");
return 1;
}
char msg[MSGSIZE] = { };
pid_t pid = fork();
switch(pid) {
case -1:
perror("fork call");
return 2;
case 0: // processo figlio
close(pipes[0]); // chiude l’altro capo
write(pipes[1], "Hello, world!", MSGSIZE);
break;
default: // processo padre
close(pipes[1]); // chiude l’altro capo
read(pipes[0], msg, MSGSIZE);//ricevuto messaggio dalla pipe
printf("%s\n", msg);
wait(NULL);
}
return 0;
}
//esempio di transito da un processo a un altro, non necessario chiudere
//i descrittori
