#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void *getFileVector(char*);

int main(int argc, char *argv[]) {

  time_t start, end;
  start = time(NULL);

  getFileVector(argv[1]);
  
  end = time(NULL);

  double seconds = ((double) (end - start));

  printf("Se tardó %lf segundos \n", seconds);

  return 0;
}

void *getFileVector(char* fileName) {
  char *buffer = NULL;
  size_t bufferSize = 0;
  ssize_t lineSize;
  long sum = 0;

  FILE *fp = fopen(fileName, "r");
  
  if (fp == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", fileName );
    exit(1);
  }

  lineSize = getline(&buffer, &bufferSize, fp);

  while (lineSize >= 0) {
    int readedNumber = atoi(buffer);

    sum += readedNumber;

    lineSize = getline(&buffer, &bufferSize, fp);
  }

  printf("La suma de los elementos del vector del archivo es: %ld\n", sum );

  fclose(fp);

  return (void*) NULL;
}