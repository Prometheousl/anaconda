/*
 * types.h
 *
 *  Created on: January 24, 2019
 *      Author: alexl
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>

// single extern character tokens
extern char *OPEN_BRACKET;
extern char *CLOSE_BRACKET;
extern char *OPEN_PAREN;
extern char *CLOSE_PAREN;
extern char *COMMA;
extern char *COLON;
extern char *DOT;
extern char *PLUS;
extern char *ASSIGN;
extern char *MINUS;
extern char *TIMES;
extern char *DIVIDE;
extern char *LESS_THAN;
extern char *GREATER_THAN;
// bad extern characters
extern char *UNKNOWN;
extern char *BAD_NUMBER;
// keywords
extern char *IF;
extern char *ELSE;
extern char *WHILE;
extern char *INCLUDE;
extern char *VAR;
extern char *DEF;
extern char *RETURN;
extern char *BREAK;
extern char *END;
extern char *FOR;
extern char *CLASS;
extern char *ENDCLASS;
//types
extern char *INTEGER;
extern char *REAL;
extern char *STRING;
// variable/identifier
extern char *ID;
// misc
extern char *ENDofINPUT;

#endif
