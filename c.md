### C SHEET

#### compilazione

`$clang programma.c` genera file a.out  
`$ .\a.out` esegue il file  

altrimenti posso rinominare il file a.out con  
`$ clang file.c -o nome`  
`$ .\nome`  

il file deve avere estensione .c

#### direttive pre processing

`#`: direttive del processore, a _inizio_ del programma

`#define`: serve a definire una costante o una funzione
`#include`: serve a preprocessare un file con determinate funzioni  

Es: `#include <stdio.h>`
Esempi di file di libreria visti a lezione:

- stdio.h: standard input/output  

- definire una costante `#define NOME valore`
- includere file `#include <nome.h>`  

#### tipi presenti in c

char, short int, int, long int, float, double, unsigned int (anche long / short)

conversioni mediante:

- promozioni: char &rarr; short &rarr; int &rarr; long int &rarr; float &rarr; double
- cast: (tipo) variabile

particolarità:  

- le stringhe sono considerate array di char
- non esiste il tipo bool, costrutti si aspettano espressioni intere (0 = falso)  
- struct...

#### sintassi di base

- dichiarazione variabili:
- costrutti di controllo e cicli (if,for,while, switch)
- operatori aritmetici: +, -, *, /, %, ++, --
- operatori di confronto: < > <= >= == != 
- operatori logici: && (and), || (or), ! (not)
- costanti

costrutti
for(dichiarazione e inizio indice; condizione fine; passo): termina quando condizione fine = 0
while(condizione): se condizione uguale a 0 termina, altrimenti continua

specificatori di formato:

- `%d`: intero
- `%f`: float
- `%c`: char
- `%s`: stringa
- `%p`: puntatore
- `%x`: esadecimale
- `%2.3f`: float con almeno 2 cifre intere e 3cifre decimali (formato)  

sequenze di escape:

- \n newline
- \t Tab
- \\\ singola backslash  '\\'
- \" doppi apici

#### struttura del programma

```c
#include ...

int main(){
    blocco di codice
    return 0;
}
```

#### funzioni non primitive

printf: `printf "stringa", %1, %2, ...` stampa stringa nello standard output, sostituendo ogni % nella stringa al corrispondente argomento  
getchar: `getchar()` legge carattere dallo standard input
putchar: `putchar(c)` stampa carattere nello standard output  
