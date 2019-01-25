/*
 * String.c
 *
 *  Created on: Sep 6, 2017
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "m_string.h"

struct STR {
    char *value;
    };

String *
newString(char *x) {
    String *p = malloc(sizeof(String));
    if (p == 0) {
    	fprintf(stderr,"out of memory\n"); exit(1);
    }
    p->value = x;
    return p;
    }

char *
getString(String *v) {
    return v->value;
    }

char *
setString(String *v,char *x) {
    char *old = v->value;
    v->value = x;
    return old;
    }

void
displayString(FILE *fp,void *v) {
    fprintf(fp,"%s",getString(v));
}
