#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
// Apriamo in scrittura, appendendo, creando il file se non esite
int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0644); //apro in modalità scrittura, alla fine, se file non esiste creiamo, permessi ottale (0 iniziale)
char contents[13] = "Hello World\n"; //carattere in più, ne scriviamo 12, il tredicesimo è il \0 è il terminatore
write(fd, contents, 12); //fd rappresenta file aperto. NON SCRIVERE TERMINATORE in un file
close(fd); 
return 0;
}
