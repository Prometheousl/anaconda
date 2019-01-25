#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "errors.h"

char *FileName = "";

int main(int argc,char **argv) {
  if (argc == 1) Error("Not enough arguments!\n");
  else FileName = argv[1];

  Lexer *lexer = newLexer(FileName);
  Lexeme *lexeme = NULL;

  lexeme = lex(lexer);
  while(getLexemeType(lexeme) != ENDofINPUT) {
    printLexeme(stdout,lexeme);
    lexeme = lex(lexer);
  }

  return 0;
}
