/*
 * errors.c
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "lexeme.h"

/**
 * Prints to the standard out
 * if an error occurred then exits w/non-zero error code
 */
void Error(char *error) {
  fprintf(stdout,"An error occured: %s",error);
  exit(-1);
 }
// prints the error message for a bad lexeme
void ErrorLexeme(Lexeme *l) {
  fprintf(stdout,"An error occurred with reading a  lexeme at line %d: %s",
    getLexemeLineNumber(l),getLexemeType(l));

  if(getLexemeString(l) != NULL) {
    fprintf(stdout,"The offending character/string is: %s",
      getLexemeString(l));
  }
  exit(-1);
}
