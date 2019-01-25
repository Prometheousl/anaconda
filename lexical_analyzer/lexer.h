/*
 * lexer.h
 *
 *  Created on: Jan 25, 2019
 *      Author: alexl
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include "lexeme.h"

typedef struct lexer Lexer;

extern Lexer *newLexer(FILE *);
extern Lexeme *lex(Lexer *);


#endif /* LEXER_H_ */
