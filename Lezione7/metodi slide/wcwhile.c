//il seguente programma implementa le funzionalità del comando wc -c
#include <stdio.h>

int main(){
    long nc = 0;
    while(getchar() != EOF){
        ++nc;
    }
    printf("%ld\n", nc);
    return 0;
}