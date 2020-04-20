#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void *getFileVector(char*);

int main(int argc, char *argv[]) {
  
  getFileVector(argv[1]);

  return 0;
}

void *getFileVector(char* fileName) {
  char *buffer = NULL;
  size_t bufferSize = 0;
  ssize_t lineSize;
  int sum = 0;

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

  printf("La suma de los elementos del vector del archivo es: %d\n", sum );

  fclose(fp);

  return (void*) NULL;
}