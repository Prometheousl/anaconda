/*
 * int.c
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "int.h"

struct INT {
    int value;
    };

Integer *
newINT(int x) {
    Integer *p = malloc(sizeof(Integer));
    if (p == 0) {
    	fprintf(stderr,"out of memory\n"); exit(1);
    }
    p->value = x;
    return p;
    }

int
getINT(Integer *v) {
    return v->value;
    }

int
setINT(Integer *v,int x) {
    int old = v->value;
    v->value = x;
    return old;
    }

void
displayINT(FILE *fp,void *v) {
    fprintf(fp,"%d",getINT(v));
}
