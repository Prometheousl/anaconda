/*
 * real.h
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#ifndef REAL_H_
#define REAL_H_

#include <stdio.h>

typedef struct real Real;

extern Real *newReal(double);
extern double getReal(Real *);
extern double setReal(Real *,double);
extern void displayReal(FILE *,void *);

#endif /* REAL_H_ */
