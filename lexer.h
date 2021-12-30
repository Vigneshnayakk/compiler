#ifndef lexer_h
#define lexer_h

struct token{
  enum tokentype{
  T_VAR,
  T_WHILE,
  T_DO,
  T_END,
  T_PRINT,
  T_ID,
  T_NUM,
  T_LPAR,
  T_RPAR,
  T_PLUS,
  T_MINUS,
  T_EQ,
  T_SEP,
  T_EOF
} type;
  char * value;
  int line;
};

struct token scan(void);
void initScanner(char *);
void printToken(struct token);

#endif
