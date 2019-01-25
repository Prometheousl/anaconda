/*
 * real.h
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdio.h>
#include "lexeme.h"

extern void Error(char *error);
extern void ErrorLexeme(Lexeme *l);

#endif
