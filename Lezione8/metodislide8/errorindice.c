#include <stdio.h>

int main(){
    int risposta = 42;
    int valori[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //Azzeriamo l'array
    for(int i = 0; i <= 10; i++){
        valori[i] = 0;
    }

    printf("La risposta è: %d\n", risposta);
    return 0;
}