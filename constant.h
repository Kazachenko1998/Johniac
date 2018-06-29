#ifndef RUN_CONSTANT_H


#include <stdio.h>
#include "double_john.h"

#define _WHITH "w"
#define _EXIT "q"
#define _WHITHOUT "s"
#define _FULL "f"
#define _R_DATA 1023
#define _L_DATA 0

typedef struct constant {

    int _R;

    double_john **registerData;
    double_john *_Ac;
    FILE *fp, *out;
    char *name_out;
} constant;

//extern double_john _Ac;
#define RUN_CONSTANT_H
#endif