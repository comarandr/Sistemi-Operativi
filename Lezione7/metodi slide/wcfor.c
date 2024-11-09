//implementa il wc -c di Unix
#include <stdio.h>

int main(){
    long nc = 0;
    for(; getchar() != EOF; ++nc);
    pritnf("%ld\n", nc);
    return 0;
}