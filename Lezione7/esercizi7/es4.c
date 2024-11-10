#include <stdio.h>
//Scrivere un programma C che conti il numero di parole immesse sullo standard input
 
int main(){ //le variabili sono passate come valori tra procedure
    int wordCount = 0; // due contatori, n numero di parole, i per controllare se c'è uno spazio
    int inWord = 0;
    for(int c = getchar(); c != EOF; c = getchar()){ //
        if(c ==' ' ){ //|| c == '\t' || c == '\n'){
            if(inWord==1){
                inWord=0;
            }
        }else{
            if(inWord==0){
                wordCount++;
                inWord++;
            }
        }
    }
    printf("\nNumero parole: %d\n", wordCount);
    return 0;
}