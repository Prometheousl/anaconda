/*
 * types.c
 *
 *  Created on: Jan 24, 2019
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

// single character tokens
char *OPEN_BRACKET = "OPEN_BRACKET";
char *CLOSE_BRACKET = "CLOSE_BRACKET";
char *OPEN_PAREN = "OPEN_PAREN";
char *CLOSE_PAREN = "CLOSE_PAREN";
char *COMMA = "COMMA";
char *COLON = "COLON";
char *DOT = "DOT";
char *PLUS = "PLUS";
char *ASSIGN = "ASSIGN";
char *MINUS = "MINUS";
char *TIMES = "TIMES";
char *DIVIDE = "DIVIDE";
char *LESS_THAN = "LESS_THAN";
char *GREATER_THAN = "GREATER_THAN";
// bad characters
char *UNKNOWN = "UNKNOWN";
char *BAD_NUMBER = "BAD_NUMBER";
// keywords
char *IF = "IF";
char *ELSE = "ELSE";
char *WHILE = "WHILE";
char *INCLUDE = "INCLUDE";
char *VAR = "VAR";
char *DEF = "DEF";
char *RETURN = "RETURN";
char *BREAK = "BREAK";
char *END = "END";
char *FOR = "FOR";
char *CLASS = "CLASS";
char *ENDCLASS = "ENDCLASS";
//types
char *INTEGER = "INTEGER";
char *REAL = "REAL";
char *STRING = "STRING";
// variable/identifier
char *ID = "IDENTIFIER";
// misc
char *ENDofINPUT = "ENDofINPUT";
