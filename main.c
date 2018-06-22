#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"
#include "help_func.h"

int initialization();

int running_count_of_steps();

int full_running();

int run_code_step_by_step();

int run_code_step_by_step_with_printing_results();

char key[2];
char answer[255];


int main() {
    int runing_state = 1;
    while (1) {
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
        if (runing_state == 1) printf("You code completed successful");
        if (runing_state == 2) runing_state = 1;
    }
}

int initialization() {
    com = malloc(sizeof(char) * 100);
    command = malloc(sizeof(char) * 10);
    numbcom = malloc(sizeof(char) * 100);
    registerData = malloc(sizeof(double_john) * (_R_DATA + 1));
    _Ac = malloc(sizeof(double_john));
    _Ac->num = 0;
    _Ac->den = 1;

    memset(registerData, 0, sizeof(registerData));
    for (int i = 0; i < _R_DATA + 1; i++) {
        double_john *john = malloc(sizeof(double_john));
        john->num = 0;
        john->den = 1;
        registerData[i] = john;
    }
    out = fopen("output.txt", "a");
    fp = fopen("input.txt", "r");
}


int StrToInt(char *s) {
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

int running_count_of_steps() {
    printf("Input count of steps \n");
    char *string = malloc(sizeof(char) * 100);
    memset(string, 0, sizeof(string));
    fgets(string, 10, stdin);
    int countSteps = StrToInt(string);
    while (countSteps > 0) {
        int result = pars(fp, 0);
        if (result != 0) return result;
        countSteps--;
    }
    return 0;
};

int full_running() {
    while (!feof(fp)) {
        int result = pars(fp, 0);
        if (result != 0) return result;
    }
    return 0;
};

int run_code_step_by_step() {
    while (!feof(fp)) {

        printf("s - next step \n");
        printf("f - run to end \n");
        printf("q - exit \n");

        fgets(key, 2, stdin);

        if (strcmp(key, _WHITHOUT) == 0) {
            int result = pars(fp, 0);
            if (result != 0) return result;
        }
        // break;
        if (strcmp(key, _EXIT) == 0) {
            return 0;
        }//завершаем работу программы
        if (strcmp(key, _FULL) == 0) {
            while (!feof(fp)) {
                int result = pars(fp, 0);
                if (result != 0) return result;
            }
        }
    }
    return 0;
};

int run_code_step_by_step_with_printing_results() {
    while (!feof(fp)) {
        printf("w - write memory \n");
        printf("s - not write memory \n");
        printf("f - run to end \n");
        printf("q - exit \n");

        fgets(key, sizeof(key), stdin);

        if (strcmp(key, _WHITH) == 0) {// Space- следующая команда
            {
                int result = pars(fp, 1);
                if (result != 0) return result;
                printf(" Ac: %i/%i R: %i; ", _Ac->num, _Ac->den, _R);
            }
        }
        if (strcmp(key, _WHITHOUT) == 0) {
            int result = pars(fp, 0);
            if (result != 0) return result;
            printf(" Ac: %i/%i R: %i; ", _Ac->num, _Ac->den, _R);
        }
        if (strcmp(key, _EXIT) == 0) {//Esc - прекратить выполнение программы
            return 0;
        }
        if (strcmp(key, _FULL) == 0) {
            while (!feof(fp)) {
                int result = pars(fp, 0);
                if (result != 0) return result;
            }
        }

    }
    return 0;
};