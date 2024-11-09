#include<stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(){
    for(float fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf("%3.0f °F -> %6.1f °C\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
    return 0;
    
}