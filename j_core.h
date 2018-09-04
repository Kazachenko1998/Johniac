#ifndef RUN_CONSTANT_H
#define RUN_CONSTANT_H

#include <stdio.h>

#define _WHITH "w"
#define _EXIT "q"
#define _WHITHOUT "s"
#define _FULL "f"
#define _R_DATA 1023
#define _L_DATA 0

typedef struct j_core {
    int _pointer;
    struct j_double **double_array;
    struct j_double *accumulator;
    FILE *input_file_ref;
    FILE *output_file_ref;
    char *output_file_name;
} j_core;

struct j_core *new_j_core();

_Bool init_core(struct j_core *, char **args, int argc);

_Bool init_core_by_default(struct j_core *core );

void write_j_state_in_file(struct j_core *core);

void free_j_core_materials(struct j_core *core);

#endif