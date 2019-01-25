/*
 * scanner.c
 *
 *  Created on: January 24, 2019
 *  Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "errors.h"

char *FileName; // The specified file name

/** Takes in a file name as an argument from the
  * command line.
  * Then parses that file, creating lexemes for
  * every token. It then displays those lexemes.
  */
int main(int argc,char **argv) {
  if (argc == 1) Error("Not enough arguments!\n");
  else FileName = argv[1];

  FILE *fp = fopen(FileName, "r");
  if(fp == NULL) Error("Error in opening file.");

  Lexer *lexer = newLexer(fp);
  Lexeme *lexeme = NULL;

  lexeme = lex(lexer);
  while(getLexemeType(lexeme) != ENDofINPUT) {
    printLexeme(stdout,lexeme);
    lexeme = lex(lexer);
  }
  printLexeme(stdout,lexeme); // ENDofINPUT

  fclose(fp);

  return 0;
}
