#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAXLENGTH 80

#include "common.h"

int main()
{
  // apro il socket per la comunicazione
  int sock = socket(AF_LOCAL, SOCK_STREAM, 0); //socket locale affidabile, 0 lascia all'OS scelta protocollo
  check(sock, 1, "socket()"); //richiamo alla check, definita in common.c

  // imposto l'indirizzo
  struct sockaddr_un addr = { //struttura per collegarsi al server
    .sun_family = AF_LOCAL, //famiglia indirizzi, compatibile al tipo di socket
    .sun_path = SOCKADDR //percorso address, su common .h percorso a tmp
  };

  // mi connetto al server

  int connected = connect(sock, (struct sockaddr *)&addr, sizeof addr); //argomenti: socket, puntatore alla struttura che specifica indirizzo a cui collegarsi, byte struttura
  check(connected, 2, "connect()");//controllo se c'è stato un errore o meno

  /*
   * ricezione e stampa a video del messaggio di benvenuto del server
   */

  // ricevo la lunghezza del messaggio
  int greetlen = 0; //puntatore
  int read = recv(sock, &greetlen, sizeof(greetlen), 0); //andiamo a leggere, possiamo usare read semplice senza ultimo argomento, passiamo puntatore intero
  check(read, 3, "connessione al server interrotta"); //

  // ricevo il messaggio
  char *greet = malloc(greetlen); //associo area di memoria
  read = recv(sock, greet, greetlen, 0); //greetlen byte, 
  check(read, 3, "connessione al server interrotta"); //errore

  // stampo il messaggio
  printf("%s", greet);
  free(greet);


  // acquisizione dei dati da standard input
  char *line = NULL;
  while(1) { //ciclo indefinito
    line = freadline(stdin, line);//linea su standard input, quello che utente digita finirà su null
    if(!line)//finché non c'è nulla in input, che rompe ciclo
      goto close; //serve a saltare a un'etichetta, potevo scrivere anche break
//goto salta ovunque, rompe buona programmazione, crea disordine
    /* invio e ricezione della stringa */
    int sent = send(sock, line, strlen(line) + 1, 0);//inviamo strlen(line) +1 terminatore a line
    check(sent, 4, "send()");

    int read = recv(sock, line, strlen(line) + 1, 0); //mettiamo risultato in line, strlen+1 (terminatore)
    check(read, 5, "recv()");

    printf("%s\n", line);
  }

close:
  /* chiusura della connessione */
  close(sock);
  return 0;
}
