/*
 * int.h
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#ifndef INT_H_
#define INT_H_

#include <stdio.h>

typedef struct INT Integer;

extern Integer *newINT(int);
extern int getINT(Integer *);
extern int setINT(Integer *,int);
extern void displayINT(FILE *,void *);

#endif /* INT_H_ */
