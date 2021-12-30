// read from source code file
#include<stdio.h>
#include<stdlib.h>
#include "lexer.c"

char * readFile(char * f){
  char * buffer = NULL;
  int stringSize = 0;
  int readSize = 0;
  FILE * fp = fopen(f,"r");
  if(f){
    fseek(fp,0,SEEK_END);
    stringSize = ftell(fp);
    fseek(fp,0,SEEK_SET);

    buffer = (char *) malloc(sizeof(char) * stringSize+1);
    buffer[stringSize] = '\0';

    readSize = fread(buffer,sizeof(char),stringSize,fp);
    if(stringSize != readSize){
      free(buffer);
      printf("\nNo enough memory!!\n");
      exit(1);
    }
    fclose(fp);
    return buffer;
  }else
  printf("\nCannot open file\n");
  exit(1);
}
int main(){
  char * filename = "source.cp";
  char * buffer  = readFile(filename);
  initScanner(buffer);
  printToken(scan());
  printToken(scan());
  printToken(scan());
  printToken(scan());
  printToken(scan());
  return 0;
}


