#include "j_core.h"
#include "j_double.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MEMORY_SIZE (_R_DATA + 1)

#define START_NUMERATOR 0

#define START_DENOMINATOR 1

j_core *new_j_core() {
    j_core *core = calloc(1, sizeof(core));
    core->input_file_ref = calloc(1, sizeof(FILE));
    core->output_file_ref = calloc(1, sizeof(FILE));
    core->output_file_name = calloc(100, sizeof(char));
    core->_pointer = 0;
    return core;
}

_Bool init_core(j_core *core, char **args, int argc) {
    core->double_array = calloc(MEMORY_SIZE, sizeof(j_double));
    core->accumulator = new_j_double(START_NUMERATOR, START_DENOMINATOR);
    core->_pointer = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        core->double_array[i] = new_j_double(START_NUMERATOR, START_DENOMINATOR);
    }
    if (argc != 3) {
        return false;
    }
    core->input_file_ref = fopen(args[1], "r");
    if (!core->input_file_ref) {
        return false;
    }
    char *output_file_name = args[2];
    core->output_file_name = output_file_name;
    core->output_file_ref = fopen(output_file_name, "a");
    return true;
}

_Bool init_core_by_default(j_core *core) {
    core->output_file_ref = fopen("output.txt", "a");
    core->output_file_name = "output.txt";
    core->input_file_ref = fopen("input.txt", "r");
    _Bool are_files_opened = core->output_file_ref && core->input_file_ref;
    if (!are_files_opened) {
        printf("EXCEPTION in open default files");
    }
    return are_files_opened;
}

void write_j_state_in_file(j_core *core) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        fprintf(
                core->output_file_ref,
                "%i/%i - %i ;",
                core->double_array[i]->numerator,
                core->double_array[i]->denominator,
                i
        );
    }
}

void free_j_core_materials(j_core *core) {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        free_j_double(core->double_array[i]);
    }
    free_j_double(core->accumulator);
    free(core->double_array);
    fclose(core->input_file_ref);
    fclose(core->output_file_ref);
    free(core->output_file_ref);
    free(core->input_file_ref);
}
