#include<stdio.h> //direttive del preprocessore

//scrivere un programma C che stampi il valore della costante simbolica EOF

int main(){ //funzione principale, main è di tipo int
    int x = EOF; //assegnazione della costante EOF alla variabile x
    printf("%d\n", x); //stampa; %d è il placeholder per un intero, x è il valore da stampare
    return 0; //ritorno del valore 0, segnala che il programma è terminato correttamente
}