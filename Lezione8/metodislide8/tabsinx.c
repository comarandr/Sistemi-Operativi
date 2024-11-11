#include <stdio.h>
#include <math.h>

#define N_CAMPIONI 10

int main(){
    float valori [N_CAMPIONI] = {0.0};
    float step = 2 * M_PI / N_CAMPIONI; //M_PI è una costante definita in math.h, linker necessita flag -lm

    for(int i = 0; i < N_CAMPIONI; i++){
        valori[i] = sin(i * step);
    }

    for (int i = 0; i < N_CAMPIONI; i++){
        printf("sin(%1.3f) = %1.3f\n", i * step, valori[i]);
    }

    return 0;
}