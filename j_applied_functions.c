#include <stdlib.h>
#include <string.h>
#include "j_core.h"
#include "j_double.h"
#include <stdio.h>

int func_add();

int func_sub();

int func_minM();

int func_M();

int func_h();

int func_hmin();

int func_hm();

int func_hminM();

int func_Rr();

int func_A();

int func_X();

int func_minmin();

int func_C();

int func_C_();

int func_Cc();

int func_Cc_();

int func_S();

int func_Sp();

int func_R();

int func_L();

int func_Sp_();

int sw(char *numbcom);

#define J_APPLIED_DEBUG

#define J_APPLIED_TAG ""

char *command_value;

char *command_line;

char *command_chunk;

unsigned int pointer;

int _x;

j_core *local_core;

int pars(int debug, j_core *core) {
    command_line = calloc(100, sizeof(char));
    command_chunk = calloc(100, sizeof(char));
    command_value = calloc(100, sizeof(char));
    local_core = core;
    unsigned int i = 0;
    fgets(command_chunk, 100, core->input_file_ref); //читаем очередную строку
    pointer = 0;
    printf("Command:%s", command_chunk);
    if (debug > 0) {
        for (i = 0; i < _R_DATA + 1; i++) {
            if (debug > 1) {
                printf("%i/%i - %i ;", core->double_array[i]->numerator, core->double_array[i]->denominator, i);
            }
            fprintf(
                    core->output_file_ref,
                    "%i/%i - %i ;",
                    core->double_array[i]->numerator,
                    core->double_array[i]->denominator,
                    i
            );
        }
    }
    for (i = 0; i < strlen(command_chunk); i++) {
        if (command_chunk[i] != ' ' && command_chunk[i] != '\n' && command_chunk[i] != '\0') {
            command_value[i] = command_chunk[i];
            pointer++;
        } else break;
    }
    pointer++;
    for (i = pointer; i < strlen(command_chunk); i++) {
        if (('0' <= command_chunk[i] && command_chunk[i] <= '9') || command_chunk[i] == '-' ||
            command_chunk[i] == ' ' || command_chunk[i] == '\n' ||
            command_chunk[i] == '\0')
            command_line[i - pointer] = command_chunk[i];
        else {
            printf("Exception in code: Unsupported number.");
            return 665;
        }
    }

    command_line[i - pointer] = '\0';
    _x = atoi(command_line);

    int ans = sw(command_value);
    printf("Ac: %i/%i, data[%i]: %i/%i, command_line: %s", core->accumulator->numerator, core->accumulator->denominator,
           core->_pointer, core->double_array[core->_pointer]->numerator,
           core->double_array[core->_pointer]->denominator, command_chunk);
    fprintf(core->output_file_ref, "Ac: %i/%i, data[%i]: %i/%i, command_line: %s\n", core->accumulator->numerator,
            core->accumulator->denominator,
            core->_pointer, core->double_array[core->_pointer]->numerator,
            core->double_array[core->_pointer]->denominator, command_chunk);
    fclose(core->output_file_ref);
    fopen_s((FILE **) core->output_file_ref, core->output_file_name, "a");

    return ans;
}

int sw(char *numbcom) {
    if (strcmp(numbcom, "") == 0) {
        return func_add();
    } else if (strcmp(numbcom, "-") == 0) {
        return func_sub();
    } else if (strcmp(numbcom, "M") == 0) {
        return func_M();
    } else if (strcmp(numbcom, "-M") == 0) {
        return func_minM();
    } else if (strcmp(numbcom, "h") == 0) {
        return func_h();
    } else if (strcmp(numbcom, "h-") == 0) {
        return func_hmin();
    } else if (strcmp(numbcom, "hM") == 0) {
        return func_hm();
    } else if (strcmp(numbcom, "h-M") == 0) {
        return func_hminM();
    } else if (strcmp(numbcom, "Rr") == 0) {
        return func_Rr();
    } else if (strcmp(numbcom, "A") == 0) {
        return func_A();
    } else if (strcmp(numbcom, "X") == 0) {
        return func_X();
    } else if (strcmp(numbcom, "--") == 0) {
        return func_minmin();
    } else if (strcmp(numbcom, "C") == 0) {
        return func_C();
    } else if (strcmp(numbcom, "C'") == 0) {
        return func_C_();
    } else if (strcmp(numbcom, "Cc") == 0) {
        return func_Cc();
    } else if (strcmp(numbcom, "Cc'") == 0) {
        return func_Cc_();
    } else if (strcmp(numbcom, "S") == 0) {
        return func_S();
    } else if (strcmp(numbcom, "Sp") == 0) {
        return func_Sp();
    } else if (strcmp(numbcom, "Sp'") == 0) {
        return func_Sp_();
    } else if (strcmp(numbcom, "L") == 0) {
        return func_L();
    } else if (strcmp(numbcom, "R") == 0) {
        return func_R();
    } else {
        printf("Exception in code: Unsupported command_chunk.");
        return 666;
    }
}

////////////////////////////////////////////////////////////////


int func_add() {
    put_int(local_core->accumulator, 0);
    add_int(local_core->accumulator, _x);
    return 0;
}

int func_sub() {
    put_int(local_core->accumulator, 0);
    sub_int(local_core->accumulator, _x);
    return 0;
}

int func_M() {
    put_int(local_core->accumulator, 0);
    add_int(local_core->accumulator, abs(_x));
    return 0;
}

int func_minM() {
    put_int(local_core->accumulator, 0);
    sub_int(local_core->accumulator, abs(_x));
    return 0;
}

int func_h() {
    add_int(local_core->accumulator, _x);
    return 0;
}

int func_hmin() {
    sub_int(local_core->accumulator, _x);
    return 0;
}

int func_hm() {
    add_int(local_core->accumulator, abs(_x));
    return 0;
}

int func_hminM() {
    sub_int(local_core->accumulator, abs(_x));
    return 0;
}

int func_Rr() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    put_int(local_core->double_array[local_core->_pointer], 0);
    add_int(local_core->double_array[local_core->_pointer], _x);
    return 0;
}

int func_A() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    put_int(local_core->accumulator, 0);
    local_core->accumulator = local_core->double_array[local_core->_pointer];
    return 0;
}

int func_X() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    put_int(local_core->accumulator, 0);
    multiply_int(local_core->double_array[local_core->_pointer], _x);
    return 0;
}

int func_minmin() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    put_int(local_core->double_array[local_core->_pointer], 0);
    divide_int(local_core->accumulator, _x);
    local_core->double_array[local_core->_pointer] = local_core->accumulator;
    return 0;
}

int func_C() {
    local_core->_pointer--;
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_C_() {
    local_core->_pointer++;
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_Cc() {
    if (local_core->accumulator->numerator > 0) local_core->_pointer = _x;
    return 0;
}

int func_Cc_() {
    if (local_core->accumulator->numerator <= 0) local_core->_pointer = _x;
    return 0;
}

int func_S() {
    local_core->_pointer = _x;
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    local_core->double_array[_x] = local_core->accumulator;
    return 0;
}

int func_Sp() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    local_core->double_array[local_core->_pointer]->numerator = local_core->double_array[_x]->numerator;

    return 0;
}

int func_Sp_() {
    if (local_core->_pointer < _L_DATA || local_core->_pointer > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    local_core->double_array[local_core->_pointer]->denominator = local_core->double_array[_x]->denominator;

    return 0;
}

int func_L() {
    multiply_int(local_core->accumulator, 2);
    return 0;
}

int func_R() {
    divide_int(local_core->accumulator, 2);
    return 0;
}