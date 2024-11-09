//Scrivere un programma C che conti il numero di spazi, tab e newline (whitespace characters) presenti nei caratteri immessi sullo standard input

#include <stdio.h> //direttove di precompilazione

int main(){ //principale
    int space = 0;
    int tab = 0;
    int newline = 0;
    int c = getchar(); //leggo il primo carattere
    while(c != EOF){ //finchè non arrivo alla fine del file
        if(c == ' '){ //se il carattere è uno spazio
            space++; //incremento il contatore degli spazi
        }else if(c == '\t'){ //se il carattere è un tab
            tab++; //incremento il contatore dei tab
        }else if(c == '\n'){ //se il carattere è un newline
            newline++; //incremento il contatore dei newline
        }
        getchar(); //leggo il prossimo carattere
    }
    printf("Spazi: %d\nTabulazioni: %d\nNewline: %d\n", space, tab, newline);
 return 0; //ritorno 0
}