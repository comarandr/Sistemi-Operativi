/*
 * Questo programma imita il comportamento del comando 'su' di UNIX.
 * L'uso dalla riga di comando è il seguente:
 *
 * su user cmd arg1 ... argn
 *
 * Il programma lanciato in questo modo esegue il comando 'cmd arg1 ... argn'
 * con l'identità dell'utente 'user', che può essere specificato sia per nome
 * che tramite l'UID.
 *
 * Perché il programma funzioni occorre che il proprietario del file eseguibile
 * sia 'root' e che siano impostati i bit SetUID e SetGID. Ciò si può ottenere * con i comandi:
 *
 * $ sudo chown 0:0 ./su
 * $ sudo chmod ug+s ./su
 *
 */

#include <stdio.h> // printf()
#include <stdlib.h> // per strtol()
#include <ctype.h> // per isdigit()
#include <unistd.h> // per getuid()/getgid()/ecc...
#include <pwd.h> // per getpwnam() e getpwuid()

int main(int argc, char **argv)
{
  if(argc < 3) {
    fprintf(stderr,
      "Specificare il nome di un utente e il comando da lanciare.\n");
    return 1;
  }

  // diamo un nome al nostro primo e secondo argomento da riga di comando
  char *user = argv[1];
  char *cmd = argv[2];

  // Otteniamo l'array da passare ad execvp() per gli argomenti da riga di
  // comando del programma da lanciare, a partire dal nostro stesso argv.
  char **argvcmd = argv + 2;

  // Otteniamo dal sistema le informazioni sull'utente richiesto
  struct passwd *pwd = NULL;
  if(isdigit(user[0]))
    pwd = getpwuid(strtol(user, NULL, 10));
  else
    pwd = getpwnam(user);

  if(pwd == NULL) {
    fprintf(stderr, "L'utente %s non esiste", user);
    return 1;
  }

  // Stampo i miei ID
  printf("uid=%d, gid=%d, euid=%d, egid=%d\n",
         getuid(), getgid(), geteuid(), getegid());

  // Stampo gli ID dell'utente che vogliamo impersonare
  uid_t new_uid = pwd->pw_uid;
  gid_t new_gid = pwd->pw_gid;
  printf("L'uid dell'utente %s è %d\n", user, new_uid);
  printf("Il gid dell'utente %s è %d\n", user, new_gid);

  printf("Cambio i miei euid/egid a quelli dell'utente %s\n", user);

  int err = 0;

  err += seteuid(new_uid);
  err += setegid(new_gid);

  if(err < 0) {
    perror("Impossibile cambiare utente");
    return 1;
  }

  // Ristampo i miei ID
  printf("uid=%d, gid=%d, euid=%d, egid=%d\n",
         getuid(), getgid(), geteuid(), getegid());

  // Eseguo effettivamente il comando
  printf("Eseguo il comando %s...\n", cmd);
  execvp(cmd, argvcmd);
  perror("Chiamata exec() fallita");

  return 1;
}