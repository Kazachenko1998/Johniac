#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auto_type.h"
#include <stdbool.h>
#include "j_core.h"
#include "j_double.h"
#include "j_message.h"
#include "j_commands.h"
#include "j_applied_functions.h"

#define PANIC 666
#define MEMORY_SIZE (_R_DATA + 1)
typedef enum j_state {
    J_RUN, J_EMPTY, J_FAIL
} j_state;

int running_count_of_steps(j_core *);

int full_running(j_core *);

int run_code_step_by_step(j_core *);

int run_code_step_by_step_with_printing_results(j_core *);

char state_key[2];

char user_answer[10];

int main(int argc, char *args[]) {
    var current_state = J_RUN;
    var core = new_j_core();
    while (true) {
        if (!init_core(core, args, argc)) {

            var file_name = args[1];
            send_file_is_not_found(file_name);

            if (!init_core_by_default(core)) {
                return PANIC;
            }

        }


        if (current_state != J_EMPTY) {
            print_j_commands();
        }
        fgets(user_answer, 10, stdin);
        //Полное выполнение кода
        if (is_full_command(user_answer)) {
            if (full_running(core) != 0) current_state = J_FAIL;
        } else if (is_count_command(user_answer)) {      //выполнение определенного числа шагов
            if (running_count_of_steps(core) != 0) current_state = J_FAIL;
        } else if (is_step_by_step_command(user_answer)) {        //выполнить код пошагово
            if (run_code_step_by_step(core) != 0) current_state = J_FAIL;
        } else if (is_step_by_step_with_debug_command(user_answer)) {   //выполнить код пошагово с выводом результата
            if (run_code_step_by_step_with_printing_results(core) != 0) current_state = J_FAIL;
        } else if (is_exit_command(user_answer)) {
            //----------------------------------------------------------------------------------------------------------
            //Garbage collector:
            free_j_core_materials(core);
            free(core);
            //----------------------------------------------------------------------------------------------------------
            return 0;
        } else if (is_help_command(user_answer)) {
            current_state = J_FAIL;
        } else if (is_empty_string(user_answer)) {
            current_state = J_EMPTY;
        } else {
            printf("Not found command_chunk\n");
            current_state = J_FAIL;
        }
        if (current_state == J_RUN) {
            write_j_state_in_file(core);
            printf("You code is successfully completed!\n");
        }
        if (current_state == J_FAIL) {
            current_state = J_RUN;
        }
        //--------------------------------------------------------------------------------------------------------------
        //Garbage collector:
        free_j_core_materials(core);
        //----------------------------------------------------------------------------------------------------------
    }
}

int StrToInt(const char *s) {
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 — отрицательное
    if (s[i] == '-') {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39) {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return (temp);
}

int running_count_of_steps(j_core *constant) {
    printf("Input count of steps \n");
    char *string = malloc(sizeof(char) * 100);
    memset(string, 0, sizeof(char) * 100);
    fgets(string, 10, stdin);
    int countSteps = StrToInt(string);
    while (countSteps > 0) {
        int result = pars(0, constant);
        if (result != 0) return result;
        countSteps--;
    }
    return 0;
}

int full_running(j_core *constant) {
    while (!feof(constant->input_file_ref)) {
        int result = pars(0, constant);
        if (result != 0) return result;
    }
    return 0;
}

int run_code_step_by_step(j_core *constant) {
    while (!feof(constant->input_file_ref)) {

        printf("s - next step \n");
        printf("f - run to end \n");
        printf("q - exit \n");

        fgets(state_key, 2, stdin);

        if (strcmp(state_key, _WHITHOUT) == 0) {
            int result = pars(0, constant);
            if (result != 0) return result;
        }
        // break;
        if (strcmp(state_key, _EXIT) == 0) {
            return 0;
        }//завершаем работу программы
        if (strcmp(state_key, _FULL) == 0) {
            while (!feof(constant->input_file_ref)) {
                int result = pars(0, constant);
                if (result != 0) return result;
            }
        }
    }
    return 0;
}

int run_code_step_by_step_with_printing_results(j_core *constant) {
    while (!feof(constant->input_file_ref)) {
        printf("w - write memory \n");
        printf("s - not write memory \n");
        printf("f - run to end \n");
        printf("q - exit \n");

        fgets(state_key, sizeof(state_key), stdin);

        if (strcmp(state_key, _WHITH) == 0) {// Space- следующая команда
            {
                int result = pars(2, constant);
                if (result != 0) return result;
                printf(" Ac: %i/%i R: %i; ", constant->accumulator->numerator, constant->accumulator->denominator,
                       constant->_pointer);
            }
        }
        if (strcmp(state_key, _WHITHOUT) == 0) {
            int result = pars(1, constant);
            if (result != 0) return result;
            printf(" Ac: %i/%i R: %i; ", constant->accumulator->numerator, constant->accumulator->denominator,
                   constant->_pointer);
        }
        if (strcmp(state_key, _EXIT) == 0) {//Esc - прекратить выполнение программы
            return 0;
        }
        if (strcmp(state_key, _FULL) == 0) {
            while (!feof(constant->input_file_ref)) {
                int result = pars(1, constant);
                if (result != 0) return result;
            }
        }
    }
    return 0;
}