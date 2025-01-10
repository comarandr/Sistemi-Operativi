### C SHEET

#### compilazione semplice

il file deve avere estensione .c

`$clang programma.c` genera file a.out  
`$ .\a.out` esegue il file  

altrimenti posso rinominare il file a.out con  
`$ clang file.c -o nome`  
`$ .\nome`  

4 fasi: pre-processing, compilazione (C &rarr; assembler), assemblaggio (assembler &rarr; binario), linking

visualizzare il codice assembly (post compilazione):
`$ clang -s file.c`
`$ cat file.s`

visualizzare file oggetto (post assembklaggio):

`$ clang -c file.c`
si genera un file `file.o`, non apribile con un editor di testo 

posso compilare per stadi, per esempio:

`$ clang add.c -c`
`$ clang main.c -c`
`$ clang add.o main.o -o add`

#### progetto c e compilazione separata

Un unico file dovrà contenere la funzione `main()`.
Per chiamare una funzione definita in un file diverso la _dichiarazione_ deve essere visibile. Analogamente anche per costanti, tipi, ecc
Di norma le dichiarazioni vengono inserite negli header che:

- contengono esclusivamente le dichiarazioni  
- file incluso con `include <file.h>` o `include "file.h"`
- il file header deve essere incluso sia nel file.c contenente le definizioni delle funzioni, sia negli altri file
- il file.c di definizione se include l'header corrispondente non ha bisogno della dichiarazione
- poiché più inclusioni dello stesso header non vanno bene, per evitare ripetizioni tra file:
    + `#ifdef`: if defined, codice incluso se prima è stata definita la costante  
    + `#ifndef`: if not defined, codice escluso se prima è stata definita la costante  

esempio ifdef

```c
#define SIMBOLO
#ifdef SIMBOLO //se definito
    codice...
#endif
```

esempio ifndef (header che si accorga nel caso venga definito più volte, buona pratica)

```c
#ifndef ADD_H__ //se non è definito, in questo 
#define ADD_H__ //definisci
int add(int x, int y);
//resto del corpo del file header
#endif
```

#### grafo dipendenze e makefile

`make` si occupa di gestire compilazione dei programmi c. Il grafo delle dipendenze viene codificato in un file di testo chiamato `Makefile`

sintassi:

```c
target : source file(s)
    command
```

nota, command deve essere preceduto da \<tab>. In caso di source più recente i target (dipendenti) vengono aggiornati eseguendo i comandi specificati nelle regole del Makefile
esempio di makefile:

```c
add: add.o main.o
    clang add.o main.o -o add
add.o: add.h add.c
    clang -c add.c
main.o: add.h main.c
    clang -c main.c
```

inovcando `make` viene interpretato il Makefile e compilato il programma. 

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
- operatori aritmetici: +, -, *, / (parte intera), % (modulo), ++, --
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

nota %% quoting del carattere % in printf su visual studio

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

`int i = 2;`
`int *p = 0;`: un puntatore di valore 0
`&i` : indirizzo della variabile i
`&p` : indirizzo del puntatore p
`int *p = &1;`: il puntatore p = indirizzo di i
`int *p = i;`: il puntatore assume valore i(=2);
`int x = *p;`: x è uguale a contenuto nell' indirizzo di p, se p non è un registro  

**NOTA:**

```C
int a[10][20]; //alloca spazio per 200 interi (10 x 20)
int *b[10]; //alloca spazio per 10 puntatori a intero

a[i][j] e b[i][j] denotano due int, ma b[i] può puntare a un array di lunghezza diversa
```

#### puntatory e array

alcuni comportamenti utili:

```c
#define SIZE 4
int a[SIZE]={10,20,30,40}
int *p = &a[0]; //importanza dichiarazione puntatore con presenza &variabile

printf("%d",*p); -> ritorna 10
printf("%d",*p+1); -> ritorna 11
printf("%d", *(p+1)); -> ritorna 20

printf("%d", p); -> ritorna un errato
printf("%d", &p); -> ritorna un valore errato
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

`$ nome_programma argv[1] argv[2] ...`
`$ somma -s`

argc: numero di argomenti passati (il primo è la chiamata, non serve contarli)
argv: array di puntatori a carattere, che puntano alle stringhe degli argomenti
primo parametro: nome programma
ultimo elemento (argv[argc]) è NULL

#### scanf e sscanf

Di default gli spazi bianchi tra due valori in input vengono ignorati

```c
int x = 0, y = 0;
scanf("%d %d", &x, &y);
```

posso anche richiedere altri caratteri in input, che vengono richiesti ma ignorati in lettura

```c
float real = 0, float imag = 0;
scanf("( %f , %f )", &real, &imag);
```

`$ "(3.14, 0)"`

leggere e convertire il valore secondo tipo specificato e ignorarlo:
`scanf("(%f %*c %f)", &real, &imag);`

#### allocazione dinamica

funzione malloc `void *malloc(unsigned n);` argomentto numero di byte da allocare, ritorna il puntatore all'inizio dell'area di memoria (di qualsiasi tipo)  

funzione sizeof() `sizeof(tipo)` ritorna il numero di memoria dedicata per una singola istanza del tipo (es. un byte per un char e via dicendo)

la funzione free() `free(*puntatore)` serve a liberare la memoria allocata dinamicamente con malloc, in quanto la memoria allocata dinamicamente non ha uno scope preciso, rimanendo allocata

#### strutture

Sono un **tipo di dato** aggregato, che raggruppa variabili di tipo diverso in un'unica identità. Analoghe ai tipi base (quindi possono essere contenute in un array e possono esserci puntatori del tipo struttura)  

dichiarazione di una struttura

```c
struct name{
    tipo nome1;//istanza 1
    tipo nome2;//istanza 2
    ...
}

essendo come 
struct name p = { componente1, componente2, ...} //varaibile di tipo struct
```

L'accesso alle componenti delle struct può avvenire in due modi:

- tramite puntatore alle componenti: `(puntatore).componente`
- stessa cosa ma tramite _operatore dedicato_: `puntatorestruttura->componente`, (s->var)

Esempio:

```c
//dichiarazione di una struttura
struct point{ 
    float x;
    float y;
};
//dichiarazione di una variabile
struct point p = {3, 4};

//operazioni
printf("%f, %f\n", p.x, p.y);
scanf("{ %f, %f }", &p.x, &p.y);

//esempio funzione
float abs(struct point p){
    return sqrt(p.x * p.x + p.y * p.y); }

//puntatore a strutture e accesso
struct point *pp = &p;

printf("%f %f\n", pp->x, pp->y); //Equivalente alla seguente
printf("%f %f\n", (*pp).x, (*pp).y);

```


#### funzioni viste a lezione

getchar: `getchar()` legge carattere dallo standard input
putchar: `putchar(c)` stampa carattere nello standard output  

strlen: `int strlen( *char s)` restituisce la lunghezza di una stringa
strncmp: `int strcmp( *char s1, *char s2, unsigned len)` confronto lessicografico di due stringhe (0 uguali, -1 altrimenti)
strcmp: `int strcmp( *char s1, *char s2)` versione meno sicura in quanto manca lunghezza  
strncpy: `char *strncpy( *char dest, *char source, unsigned len)` copia i primi len caratteri di source in dest  
strncat: `char *strncat( *char dest, *char source, unsigned len)` concatena i primi len caratteri di source a dest

printf: `printf "stringa", %1, %2, ...` stampa stringa nello standard output, sostituendo ogni % nella stringa al corrispondente argomento  
scanf: `scanf("formato", &var1, &var2, ...)` legge input da standard input e lo memorizza nelle variabili passate come argomento

sscanf: `sscanf(stringa, "formato", &var1, &var2, ... )` legge da stringa fornita come parametro invece che da standard input  
sprintf: `sprintf(stringa, "formato", var1, var2, ...)` stampa su una stringa invece che su standard output
snprintf: `snprintf(stringa, dimensione, "formato", var1, var2, ...)` ulteriore argomento lunghezza massima stringa (consigliata)

malloc: `void *malloc(unsigned n);` serve ad allocare n byte contigui, void * è un puntatore di qualsiasi tipo
free: `free(puntatore-malloc);` serve a liberare la memoria allocata con malloc (buona norma usarlo sempre)
realloc: `void *realloc(void *ptr, unsigned new_size);` funzione ritorna un nuovo puntatore
calloc: `void *calloc(unsigned count, unsigned size);` alloca della memoria azzerandola precedentemente  

fopen(): `FILE *fopen(char *name, char *mode);` restituisce il puntatore del file su cui operare. \*mode può essere: "r", "w", "a", "rb", "wb"
fclose(): `int fclose(FILE *fp);` chiude il file pointer (buona norma utilizzarlo sempre)

fprintf(): `int fprintf(FILE *fp, char *format, ...);` analogo a printf()  
fscanf(): `int fscanf(FILE *fp, char *format, ...);` analogo a scanf()  
fgetc():`int fgetc(FILE *fp);` analogo a getchar()
fputc():`int fputc(int c, FILE *fp);` analogo a putchar()

feof(): `int feof(FILE *fp);` restituisce vero (n > 0) se lettura è arrivata alla fine
ferror(): `int ferror(FILE *fp);` restituisce vero (n > 0)

sterror(): `*char strerror(errno);` ritorna stringa di descrizione corrispondente al valore di errno, cioè al tipo di errore
pererror():

fseek(): `int fseek(FILE *fp, long offset, int whence);` imposta la posizione attuale a _offset_ byte da posizione _whence_ che può essere: SEEK_SET (inizio file), SEEK_CUR (posizione corrente), SEEK_END (fine file)
ftell(): `int ftell(FILE *file);` restituisce posizione attuale

open()
creat()
close()
read()
write()
lseek()
unlink()
fcntl()
chmod()


### PROGRAMMAZIONE DI SISTEMA

Un processo interagisce con sistema operativo tramite chiamate di sistema. Al programmatore sono fornite funzioni, di tipo:

- ISO C
- POSIX

#### accesso ai file

prima di leggere/scrivere bisogna _aprire_ un file:

```c
FILE *fopen(char *name, char *mode);
```

\*name = nome del file, *mode = stringa modalità "r" (reading), "w" (writing), "a" (append)  

ottenuto il puntatore di tipo FILE\*, possiamo usarlo per operare sul file con fprintf(),fscanf(),fgetc(),fputc()...

per _chiudere_ un file:

```c
int fclose(FILE *fp);
```

NOTA: esistono tre file pointer standard già aperti e pronti all'uso:

- `stdout`: standard output &rarr; _printf("str")_ equivale a _fprintf(stdout, "str")_
- `stdin`: standard input  &rarr; _scanf(\*char, "formato", ...)_ equivale a _fscanf(stdin, "formato", ...)_
- `stderr`: standard error  

#### gestione degli errori

tramite feof() e ferror() distinguo i casi in cui c'è un errore in lettura rispetto al caso in cui il file è terminato.
Per distinguere quale errore, le funzioni impostano la variabile globale errno, in errno.h si trovano le costanti corrispondenti ai possibili errori riportati dalle funzioni stnadard (EACCES E EISDIR)  

tramite la funzione strerror() posso ottenere una stringa di descrizione dell'errore

```c
fprintf(stderr," descrizione errore:%s\n", strerror(errno));
```

anche la funzione pererror() agisce analogamente

#### posizionamento in lettura/scrittura

lettura e scrittura avvengono in modo sequenziale (inizio &rarr; fine)  

```c
int fseek( FILE *file, long offset, int whence)
```

es. `fseek(file, 0, SEEK_SET)`; fa tornare all'inizio del file

la funzione `ftell()` restituisce posizione corrente

#### input/output binario

fopen(char* nome_file, "rb" ): reading binary, apre il file in lettura binaria (output)
fopen(char *nome_file, "wb" ): writing binary, apre il file in scrittura binaria (input)

per I/O binario si usano funzioni apposite:

lettura:

```c
size_t fread(void *ptr, size_t size, size_t nitems, FILE *file );
```

legge size\*nitems byte dal file e scrive nella memoria puntata da ptr

scrittura:

```c
size_t fwrite(void *ptr, size_t size, size_t nitems, FILE *file);
```
scrive sul file size\*nitems byte dalla memoria puntata da ptr

### FUNZIONI POSIX

- permettono di scrivere/leggere da fonti diverse: pipe,socket
- funzioni POSIX effettuano direttamente le system call, ISO adottano un buffer interno
- permettono di gestire permessi, link e altri attributi dei file


