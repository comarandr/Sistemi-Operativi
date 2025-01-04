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
- dichiarazione funzione (prototipo): `tipo_ritornato nome_funzione(lista_parametri);`
- dichiarazione di tipo:


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

#### funzioni

Le funzioni vengono prima dichiarate e poi definite tramite l'implementazione

- dichiarazione: "intestazione", tipo nome(argomenti)
- implementazione: corpo

dichiarazione deve precedere la chiamata, se 

#### variabili e passaggio per valore

le funzioni operano su **copie** dei valori degli argomenti, non sugli argomenti stessi. L'unico modo per operare sugli argomenti è passare il loro indirizzo di memoria, tramite _puntatori_.  

- scope: visibilità delle variabili

#### array  

dichiarazione `tipo nome_array[dim] = {valori}`

generalmente uso dei puntatori per accedere agli elementi dell'array o per passare l'array ad una funzione
gli array non vengono passati per valore, ma per riferimento

esempio:

```c
int array[5] = {1,2,3,4,5};
int *pa = &a[0];
printf("%d", *pa); //stampa 1
printf("%d", *(pa+1)); //stampa 2
```

```c
void fill(int *begin, int size, int value) {
 for(int *p=begin;p<begin+size;++p)
 *p=value;
 }
```

è possibile anche dichiarare array multidimensionali:

```c
float matrix[4][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
matrix[1][1] = 2;
```

#### puntatori

variabile che contiene l'**indirizzo di memoria** di un'altra variabile

`tipo *nome_puntatore = valore iniziale;`

ci sono due operatori:

- adress of `&`: ottine un puntatore alla variabile (= indirizzo di memoria)
- dereferenziazione `*`: accesso alla variabile puntata dal puntatore (= valore)

tramite aritmetica dei puntatori posso accedere agli elementi di un array:
*p + i : puntatore avanza di i \* sizeof(T) byte
*(p + i) : p[i]

in quanto variabili, anche i puntatori possono essere elementi di un array
`char *line[42] = {};` array di 42 puntatori a char \*

**NOTA:**
```C
int a[10][20]; //alloca spazio per 200 interi (10 x 20)
int *b[10]; //alloca spazio per 10 puntatori a intero

a[i][j] e b[i][j] denotano due int, ma b[i] può puntare a un array di lunghezza diversa
```

#### stringhe

le stringhe sono array di char, terminate da un carattere nullo '\0'
esempio:  
`char s[] = "ciao";`  
`char s[] = {'c','i','a','o','\0'};`

nota: `char *stringa = "Ciao mondo";` compila ma **NON** è corretto

#### librerie viste a lezione

- stdio.h: standard input/output
- string.h: funzioni per la manipolazione di stringhe

#### argomenti da riga di comando

un programma C può ricevere argomenti da riga di comando, tramite la funzione  `int main(int argc, char **argv)` 

argc: numero di argomenti passati
argv: array di puntatori a carattere, che puntano alle stringhe degli argomenti
primo parametro: nome programma
ultimo elemento (argv[argc]) è NULL

#### scanf e sscanf

```c
int x = 0, y = 0;
scanf("%d %d", &x, &y);
```

posso anche richiedere altri caratteri in input

```c
float real = 0, float imag = 0;
scanf(" ( %f , %f )", &real, &imag);
```

leggere e convertire il valore secondo tipo specificato e ignorarlo:
`scanf("(%f %*c %f)", &real, &imag);`

#### funzioni viste a lezione

getchar: `getchar()` legge carattere dallo standard input
putchar: `putchar(c)` stampa carattere nello standard output  

- funzioni per stringhe

strlen: `int strlen( *char s)` restituisce la lunghezza di una stringa
strncmp: `int strcmp( *char s1, *char s2, unsigned len)` confronto lessicografico di due stringhe (0 uguali, -1 altrimenti)
strcmp: `int strcmp( *char s1, *char s2)` versione meno sicura in quanto manca lunghezza  
strncpy: `char *strncpy( *char dest, *char source, unsigned len)` copia i primi len caratteri di source in dest  
strncat: `char *strncat( *char dest, *char source, unsigned len)` concatena i primi len caratteri di source a dest

printf: `printf "stringa", %1, %2, ...` stampa stringa nello standard output, sostituendo ogni % nella stringa al corrispondente argomento  
scanf: `scanf("formato", &var1, &var2, ...)` legge input da standard input e lo memorizza nelle variabili passate come argomento

sscanf: