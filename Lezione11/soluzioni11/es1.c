#include <stdio.h>
#include <math.h>
//nota, se compilo senza il comando -lm ottengo errori di ld con linker dinamico. pacchetto matematico
struct complex {
  float real;
  float imag;
};

float my_cabs(struct complex c);
float angle(struct complex c);
struct complex from_polar(float abs, float angle);

float my_cabs(struct complex c) { //calcola il modulo
  return sqrt(c.real * c.real + c.imag * c.imag);
}

float angle(struct complex c) { //usa arcotangente, restituisce l'angolo ~ più versioni 
  return atan2(c.imag, c.real);
}

struct complex from_polar(float abs, float angle) { //va a restituire le coordinate 
  struct complex c = { };

  c.real = abs * cos(angle);
  c.imag = abs * sin(angle);

  return c;
}

int main() //codice per testare il tutto
{
  float abs = 0, phi = 0;

  printf("Dammi il modulo e l'angolo: ");
  scanf("%f %f", &abs, &phi); //modulo in abs, phi angolo

  struct complex c = from_polar(abs, phi); //struttura c con parte reale e immaginaria

  printf("In coordinate cartesiane risulta: %.2f + i%.2f\n", c.real, c.imag);
  printf("Riconvertito in polare risulta: M = %.2f, arg = %.2f\n",
         my_cabs(c), angle(c)); //riconverto in coordinate polari

  return 0;
}

