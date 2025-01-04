#include <stdio.h>
//il problema di questo codice è che non va a capo quando incontra un a capo

int main(){
    int c = getchar();
    while(c != EOF){
        if(c == ' ' || c == '\n' || c == '\t'){ //risolto aggiungendo un or
            printf("\n");
            c = getchar();
        }
        else{
            printf("-");
            c = getchar();
        }
    }
    printf("\n");
    return 0;
}