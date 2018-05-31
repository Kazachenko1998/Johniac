#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "constant.h"
#include "help_func.h"

int initialization();

int running_count_of_steps();

int full_running();

int run_code_step_by_step();

int run_code_step_by_step_with_printing_results();

int key;
char answer[255];


int main() {
    int runing_state = 1;
    while (runing_state == 1 || runing_state == 3) {

        if (runing_state != 3) {
            initialization();
            printf("\n Choose way of running program: \n"

                   " fr       Full running \n"
                   " rfors    Running count of steps \n"
                   " sbs      Run code step by step \n"
                   " sbs -deb Run code step by step with printing results \n"
                   " exit     exit from program\n");
        }
        gets(answer);                             //fgets - это чтение из файла а не из с консоли)))  но чем это заменить я так и не придумал, хотя можно использовать алфавит вмсето клавишь но так не интересно
        if (strcmp(answer, "fr") == 0) {                //полное выполнение кода
            if (full_running() != 0) runing_state = 2;
        } else if (strcmp(answer, "rfors") == 0) {      //выполнение определенного числа шагов
            if (running_count_of_steps() != 0) runing_state = 2;
        } else if (strcmp(answer, "sbs") == 0) {        //выполнить код пошагово
            if (run_code_step_by_step() != 0) runing_state = 2;
        } else if (strcmp(answer, "sbs -deb") == 0) {   //выполнить код пошагово с выводом результата
            if (run_code_step_by_step_with_printing_results() != 0) runing_state = 2;
        } else if (strcmp(answer, "exit") == 0) {
            return 0;
        } else if (strcmp(answer, "help") == 0 || strcmp(answer, "h") == 0) {
            runing_state = 2;
        } else if (strcmp(answer, "") == 0) {
            runing_state = 3;
        } else {
            printf("Not found command\n");
            runing_state = 2;
        }
        fclose(fp);
        fclose(out);
        if (runing_state == 1) printf("You code completed successful. Press any button");
        if (runing_state == 2) runing_state = 1;
    }
}

int initialization() {
    com = malloc(sizeof(char) * 100);
    command = malloc(sizeof(char) * 10);
    numbcom = malloc(sizeof(char) * 100);
    registerData = malloc(sizeof(double) * (_R_DATA + 1));

    memset(registerData, 0, sizeof(registerData));
    out = fopen("output.txt", "a");
    fp = fopen("input.txt", "r");
}


int running_count_of_steps() {
    printf("Input count of steps \n");
    int countSteps = getch();
    while (countSteps > 0) {
        int result = pars(fp, 0);
        if (result != 0) return result;
        countSteps--;
    }
};

int full_running() {
    while (!feof(fp)) {
        int result = pars(fp, 0);
        if (result != 0) return result;
    }
};

int run_code_step_by_step() {
    while (1) {
        printf("Press the SPACE... \n");
        key = getch();
        switch (key) {
            case _SPACE:// Space- следующая команда
            {
                int result = pars(fp, 0);
                if (result != 0) return result;
            }
                break;
            case _ESC://Esc - прекратить выполнение программы
                return 0;//завершаем работу программы
            case _ENTER:
                while (!feof(fp)) {
                    int result = pars(fp, 0);
                    if (result != 0) return result;
                }
                break;
            default:;
        }
    }
};

int run_code_step_by_step_with_printing_results() {
    while (!feof(fp)) {
        printf("SPACE - write memory \n");
        printf("DOWN - not write memory \n");
        printf("ENTER - run to end \n");

        key = getch();
        switch (key) {
            case _SPACE:// Space- следующая команда
            {
                int result = pars(fp, 1);
                if (result != 0) return result;
                printf("Ac: %2.3f R: %i \n", _Ac, _R);
            }
                break;
            case _DOWN: {
                int result = pars(fp, 0);
                if (result != 0) return result;
                printf("Ac: %2.3f R: %i \n", _Ac, _R);
            }
                break;
            case _ESC://Esc - прекратить выполнение программы
                return 0;
            case _ENTER:
                while (!feof(fp)) {
                    int result = pars(fp, 0);
                    if (result != 0) return result;
                }
                break;
            default:;
        }
    }
};