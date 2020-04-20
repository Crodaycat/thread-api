#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial (void *);

int main (int argc, char *argv[]) {
  if (argc < 3){
    printf ("Debe ingresar dos números para cálcular el factorial\n");
    return 1;
  }

  pthread_t t1, t2;
  void *resT1, *resT2;

  int firstNumber = atoi(argv[1]);
  int secondNumber = atoi(argv[2]);

  pthread_create(&t1, NULL, factorial, ((void *) &firstNumber));
  pthread_create(&t2, NULL, factorial, ((void *) &secondNumber));

  pthread_join(t1, &resT1);
  pthread_join(t2, &resT2);

  printf ("El factorial de %d es %lld\n", firstNumber, (long long int)resT1);
  printf ("El factorial de %d es %lld\n", secondNumber, (long long int)resT2);
  
  return 0;
}

void *factorial (void *m) {
  int n = *(int *) m;
  
  long long int resultado= 1;
  int num;

  for (num= 2; num<= n; num++) {
    resultado= resultado*num;
    printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
    sleep (random()%3);
  }
  return (void *)resultado;
}