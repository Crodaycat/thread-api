#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>

void *getFileVector(void*);
int getFileLinesCount(char*);

typedef struct gfvArgsStrct {
  char *fileName;
  int fromLine;
  int toLine;
  long res;
} gfvArgs;

int main(int argc, char *argv[]) {
  
  //Se suma 1 para que cuente la última línea
  int fileLines = getFileLinesCount(argv[1]) + 1; 
  int finalLineT1 = fileLines/2;

  gfvArgs argsT1, argsT2;

  argsT1.fileName = argv[1];
  argsT1.fromLine = 1;
  argsT1.toLine = finalLineT1;
  argsT2.res = 0;

  argsT2.fileName = argv[1];
  argsT2.fromLine = finalLineT1 + 1;
  argsT2.toLine = fileLines;
  argsT2.res = 0;

  time_t start, end;
  start = time(NULL);
  

  pthread_t t1, t2;

  pthread_create(&t1, NULL, getFileVector, ((void *) &argsT2));
  pthread_create(&t2, NULL, getFileVector, ((void *) &argsT1));

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  end = time(NULL);
  double seconds = ((double) (end - start));

  printf("End: %ld \n", end);
  printf("Start: %ld \n", start);

  long sum =  argsT1.res + argsT2.res;

  printf("La suma del vector es: %ld se tardó %lf segundos \n", sum, seconds);

  return 0;
}

void *getFileVector(void *arguments) {
  gfvArgs *args = (gfvArgs *)arguments;

  char *buffer = NULL;
  size_t bufferSize = 0;
  ssize_t lineSize;
  long sum = 0;

  FILE *fp = fopen(args->fileName, "r");
  
  if (fp == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", args->fileName );
    exit(1);
  }

  int lineCount=1;
  char c;
  while (lineCount < args->fromLine && (c=fgetc(fp)) != EOF) {
    if (c=='\n')
      lineCount++;
  }

  lineSize = getline(&buffer, &bufferSize, fp);

  while (lineSize >= 0 && lineCount <= args->toLine) {
    int readedNumber = atoi(buffer);

    sum += readedNumber;

    lineSize = getline(&buffer, &bufferSize, fp);
    lineCount++;
  }

  args->res = sum;

  fclose(fp);

  return (void*) NULL;
}

int getFileLinesCount(char* fileName) {
  FILE *fp = fopen(fileName, "r");
  
  int lineCount = 0;

  if (fp == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", fileName );
    exit(1);
  }

  char c;

  for (c = getc(fp); c != EOF; c = getc(fp)) 
    if (c == '\n')
      lineCount++; 
      
  fclose(fp);

  return lineCount;
}