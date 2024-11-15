#include <stdio.h>
int main(int argc, char **argv) {
if(argc < 2) {
fprintf(stderr, "Fornire il nome del file\n"); //canale di errore
return 1;
}
char *filename = argv[1];
FILE *file = fopen(filename, "r");
if(!file) {
fprintf(stderr, "Errore nell’apertura del file!\n");
return 2;
}
int n = 0, sum = 0; 
while(fscanf(file, "%d", &n) == 1) { //scanf ritorna numero interi che è riuscita e leggere
sum += n;
} //posso uscire per due motivi
if(!feof(file)) {  //se non sono arrivato alla fine
fprintf(stderr, "Il file non conteneva solo numeri.\n"); //errore
return 3;
}
printf("Somma dei numeri contenuti: %d\n", sum);
return 0;
}
