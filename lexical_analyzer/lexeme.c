/*
 * lexeme.c
 *
 *  Created on: January 24, 2019
 *      Author: Alex Lay
 */

#include <stdio.h>
#include <stdlib.h>
#include "lexeme.h"
#include "types/m_string.h"
#include "types/real.h"
#include "types/int.h"
#include "types.h"

struct lexeme {
  String *type; // Integer, Real, String, etc.
  Integer *lineNumber;
  // different possible value types
  String *string;
  Integer *integer;
  Real *real;
};
// constructors
// for singular lexemes
Lexeme *newLexeme(char *t, int ln) {
  Lexeme *p = malloc(sizeof(Lexeme));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->type = newString(t);
  p->lineNumber = newINT(ln);
}
// for [type,string]
Lexeme *newLexemeString(char *t, char *s, int ln) {
  Lexeme *p = malloc(sizeof(Lexeme));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->type = newString(t);
  p->lineNumber = newINT(ln);
  p->string = newString(s);
}

Lexeme *newLexemeInt(int i, int ln) {
  Lexeme *p = malloc(sizeof(Lexeme));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->type = newString(INTEGER);
  p->lineNumber = newINT(ln);
  p->integer = newINT(i);
}

Lexeme *newLexemeReal(double r, int ln) {
  Lexeme *p = malloc(sizeof(Lexeme));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->type = newString(REAL);
  p->lineNumber = newINT(ln);
  p->real = newReal(r);
}

// accessors
char *getLexemeType(Lexeme *l) {
  return getString(l->type);
}

int getLexemeLineNumber(Lexeme *l) {
  return getINT(l->lineNumber);
}

char *getLexemeString(Lexeme *l) {
  if(l->string == NULL) {
    printf("Error cannot call getLexemeString on lexeme with no string.\n");
    exit(1);
  }
  return getString(l->string);
}

int getLexemeInt(Lexeme *l) {
  if(l->integer == NULL) {
    printf("Error cannot call getLexemeInt on lexeme with no int.\n");
    exit(1);
  }
  return getINT(l->integer);
}

double getLexemeReal(Lexeme *l) {
  if(l->real == NULL) {
    printf("Error cannot call getLexemeReal on lexeme with no real.\n");
    exit(1);
  }
  return getReal(l->real);
}

// print function
void printLexeme(FILE *fp, Lexeme *l) {
  if(l->string != NULL) {
    displayString(fp, l->type);
    fprintf(fp, " ");
    displayString(fp, l->string);
  }
  else if(l->integer != NULL) {
    displayString(fp, l->type);
    fprintf(fp, " ");
    displayINT(fp, l->integer);
  }
  else if(l->real != NULL) {
    displayString(fp, l->type);
    fprintf(fp, " ");
    displayReal(fp, l->real);
  }
  else {
    displayString(fp, l->type);
  }
  fprintf(fp, "\n");
}
