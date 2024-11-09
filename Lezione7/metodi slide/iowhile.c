#include <stdio.h>
//implementano una versione semplificata del comando cat
int main(){
    int c = getchar(); //legge carattere da una stringa
    while(c != EOF){ //se c non è uguale a EOF
        putchar(c); //stampa c
        c = getchar(); //legge un altro carattere
    }
    return 0; //terminato con successo
}