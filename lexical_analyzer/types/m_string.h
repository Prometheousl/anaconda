/*
 * String.h
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>

typedef struct STR String;

extern String *newString(char *);
extern char *getString(String *);
extern char *setString(String *,char *);
extern void displayString(FILE *,void *);

#endif /* STRING_H_ */
