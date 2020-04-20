#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial (void *);

int main (int argc, char *argv[]) {
  if (argc < 2){
    printf ("Debe ingresar al menos un número\n");
    return 1;
  }

  pthread_t tid[argc - 1];
  void *resT[argc -1];


  for (int i = 0; i < argc - 1; i++) {
    int num = atoi(argv[i+1]);

    pthread_create(&tid[i], NULL, factorial, ((void *) &num));

  }

  for (int i = 0; i < argc - 1; i++) {
    pthread_join(tid[i], &resT[i]);

    printf ("El factorial de %s es %lld\n", argv[i+1], (long long int)resT[i]);
  }
  
  return 0;
}

void *factorial (void *m) {
  int n = *(int *) m;
  
  long long int resultado= 1;
  int num;

  for (num= 2; num<= n; num++) {
    resultado= resultado*num;
  }
  return (void *)resultado;
}