/*
 * real.c
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "real.h"

struct real {
    double value;
};

Real *
newReal(double x) {
    Real *p = malloc(sizeof(Real));
    if (p == 0) {
    	fprintf(stderr,"out of memory\n"); exit(1);
    }
    p->value = x;
    return p;
}

double
getReal(Real *v) {
    return v->value;
}

double
setReal(Real *v,double x) {
    double old = v->value;
    v->value = x;
    return old;
    }

void
displayReal(FILE *fp,void *v) {
    fprintf(fp,"%f",getReal(v));
}
