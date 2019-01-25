/*
 * lexeme.h
 *
 *  Created on: January 24, 2019
 *      Author: alexl
 */

#ifndef LEXEME_H_
#define LEXEME_H_

#include <stdio.h>

typedef struct lexeme Lexeme;

extern Lexeme *newLexeme(char *, int);
extern Lexeme *newLexemeString(char *t, char *s, int);
extern Lexeme *newLexemeInt(int i, int);
extern Lexeme *newLexemeReal(double r, int);

extern char *getLexemeType(Lexeme *l);
extern int getLexemeLineNumber(Lexeme *l);
extern char *getLexemeString(Lexeme *l);
extern int getLexemeInt(Lexeme *l);
extern double getLexemeReal(Lexeme *l);

extern void printLexeme(FILE *fp, Lexeme *l);

#endif /* LEXEME_H_ */
