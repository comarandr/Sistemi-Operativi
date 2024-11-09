#include<stdio.h>

int main(){
    float fahr = 0; //dichiarazione variabile fahr
    printf("Tabella Fahrenheit-Celsius\n"); //stampa prima linea (titolo)

    while(fahr <= 300) { //ciclo while
        float celsius = (5.0 / 9.0) * (fahr - 32.0); //calcolo celsius
        printf("%3.0f °F -> %6.1f °C\n", fahr, celsius); // [% = argomento] [NumCifreInt.NumCifreDecimale] [Tipo] , [argomento]
        fahr = fahr + 20;
    }
    return 0;
}