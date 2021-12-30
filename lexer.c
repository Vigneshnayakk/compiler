#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

struct {
  char * pos;
  int line;
}scanner;

struct token scan(){
  // handle whitespaces, tabs and comments
  for(;;){
    switch(*scanner.pos){
      case ' ': case '\t': case '\r':
        scanner.pos++;
        break;
      case '`':
        if(*(scanner.pos+1) == '`'){
          while(*scanner.pos != '\n')
            scanner.pos++;
          break;
        }
      default:
        goto done_checking_ws;
    }
  }
  done_checking_ws:
  switch(*scanner.pos){
    case '\0':
      return (struct token){.type= T_EOF, .value = "\0", .line= scanner.line};
    case '(':
      scanner.pos++;
      return (struct token){.type = T_LPAR, .value = "(", .line= scanner.line};
    case ')':
      scanner.pos++;
      return (struct token){.type= T_RPAR, .value = ")", .line= scanner.line};
    case '+':
      scanner.pos++;
      return (struct token){.type = T_PLUS, .value= "+", .line= scanner.line};
    case '-':
      scanner.pos++;
      return (struct token){.type = T_MINUS, .value= "-", .line= scanner.line};
    case '=':
      scanner.pos++;
      return (struct token){.type = T_EQ, .value="=", .line= scanner.line};
    case '\n':
      scanner.pos++;
      scanner.line++;
      int l = scanner.line - 1;
      while(*scanner.pos == '\n'){
        scanner.pos++;
        scanner.line++;
      }
      return (struct token){.type= T_SEP, .value= "\n", .line= l};
    default:

      if(isalpha(*scanner.pos) || *scanner.pos == '_'){
        char * start = scanner.pos;
        while(isalpha(*scanner.pos) || *scanner.pos == '_')
          scanner.pos++;

        size_t len = sizeof(char) * (scanner.pos - start);

        char * value = (char*) malloc(len+1);
        memcpy(value,start,len);
        value[len] = '\0';

        if(strcmp(value,"var") == 0)
          return (struct token){.type= T_VAR, .value= value, .line= scanner.line};
        
        if(strcmp(value,"while") == 0)
          return (struct token){.type = T_WHILE, .value = value, .line= scanner.line};

        if(strcmp(value,"do") == 0)
          return (struct token){.type = T_DO, .value = value,
           .line = scanner.line};

        if(strcmp(value,"end") == 0)
          return (struct token){.type = T_END, .value = value,
           .line = scanner.line};

        if(strcmp(value,"display") == 0)
          return (struct token){.type = T_PRINT, .value = value, .line = scanner.line};
        
        return (struct token){.type = T_ID, .value= value, .line = scanner.line};

      }
      if(isdigit(*scanner.pos)){
        char *start = scanner.pos;
        while(isdigit(*scanner.pos))
          scanner.pos++;
        size_t len = sizeof(char) * (scanner.pos - start);
        char * value = (char*) malloc(len+1);
        value[len] = '\0';
        memcpy(value,start,len);
        return (struct token){.type = T_NUM, .value = value, .line = scanner.line};
      }
      printf("Unknown token %c at line %d\n", *scanner.pos,scanner.line);
      exit(1);
    }
  }

void initScanner(char * f){
  scanner.pos = f;
  scanner.line = 1;
}

void printToken(struct token t){
  static char* names[] = {"VAR", "WHILE", "DO", "END", "PRINT", "ID", "NUM", "LPAR", "RPAR", "PLUS", "MINUS", "EQUALS", "NEWLINE", "EOF"}; 
  printf("Token{ type=%s, value=%s, line=%d }\n", names[t.type], t.value, t.line);
}
