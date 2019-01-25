/*
 * errors.h
 *
 *  Created on: Jan 24 2019
 *      Author: alexl
 */

#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdio.h>
#include "lexeme.h"

extern void Error(char *error);
extern void ErrorLexeme(Lexeme *l);

#endif
