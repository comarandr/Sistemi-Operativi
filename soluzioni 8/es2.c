#include <stdio.h>

int lg(int);
int lg2(int);
int power(int, int);

int main() 
{
  for(int i=1; i<=1000000; i=i*10) {
    printf("lg10(%7d)=%d\n", i, lg(i));
  }

  return 0;
} 

int power(int m, int n) // definizione
{
   int p = 1;
   for (int i = 0; i < n; ++i)
      p = p * m;
   return p; // restituisce il valore di p al chiamante
}

// Versione che riutilizza power()
int lg(int n) 
{
  int result = 0;
  for(int m = 0; power(10, m) <= n; ++m) {
     result = m;
  }

  return result;
}

// Versione che calcola tutto insieme senza riutilizzare power()
int lg2(int n)
{
  int result = 0;
  int pow = 1;
  
  for(int m = 0; pow <= n; ++m, pow = pow * 10) {
    result = m;
  }

  return result;
}


