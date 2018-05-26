#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <conio.h>
#include <stdbool.h>


double Ac = 0;
int x, R = 0;
char *com;
char *command;
double *registerData;
FILE *fp, *out;
int countSteps = 0, key, i;
int curi = 0;
char answer[255], numbcom[255];

int sw(char *numbcom);

int pars(FILE *fp, int debag);

int main() {
    com = malloc(sizeof(char) * 10);
    command = malloc(sizeof(char) * 10);
    registerData = malloc(sizeof(double) * 1024);
    memset(registerData, 0, sizeof(registerData));
    fp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    stop:;
    printf("Choose way of running program: \n"
           " fr       Full running \n"
           " rfors    Running count of steps \n"
           " sbs      Run code step by step \n"
           " sbs -deb Run code step by step with printing results \n"
           " exit     exit from program");
    gets(answer);
    if (strcmp(answer, "fr") == 0) {//полное выполнение кода
        while (!feof(fp)) {
            if (pars(fp, 0) != 0) goto fail;
        }
    } else if (strcmp(answer, "rfors") == 0) { //выполнение определенного числа шагов
        printf("Input count of steps \n");
        scanf("%d", &countSteps);
        while (countSteps > 0) {
            if (pars(fp, 0) != 0) goto fail;
            countSteps--;
        }
    } else if (strcmp(answer, "sbs") == 0) { //выполнить код пошагово
        while (1) {
            printf("Press the SPACE... \n");
            key = getch();
            switch (key) {
                case 32:// Space- следующая команда
                    if (pars(fp, 0) != 0) goto fail;
                    break;
                case 27://Esc - прекратить выполнение программы
                    break;//завершаем работу программы
                default:
                    while (!feof(fp)) {
                        if (pars(fp, 0) != 0) goto fail;
                    }
                    break;
            }
            if (key == 27) break;
        }
    } else if (strcmp(answer, "sbs -deb") == 0) { //выполнить код пошагово с выводом результата
        while (!feof(fp)) {
            printf("Press the SPACE... \n");
            key = getch();
            switch (key) {
                case 32:
                    // Space- следующая команда
                    if (pars(fp, 1) != 0) goto fail;
                    printf("Ac: %2.3f R: %2.3f \n", Ac, R);
                    break;
                case 27://Esc - прекратить выполнение программы
                    break;//завершаем работу программы
                default:
                    while (!feof(fp)) {
                        if (pars(fp, 0) != 0) goto fail;
                    }
                    break;
            }
            if (key == 27) break;
        }
    } else if (strcmp(answer, "exit") == 0) return 0;
    else {
        printf("Not found command\n");
        goto stop;
    }
    fclose(fp);
    fclose(out);
    printf("You code completed successful. Press any button");
    getch();
    return 0;

    fail:;
    getch();
    return 0;
}


//function
int pars(FILE *fp, int debag) {
    for (i = 0; i < 10; i++)
        com[i] = ' ';
    fgets(command, 100, fp);//читаем очередную строку
    if (debag) {
        printf(command);
        for (i = 0; i<1024; i++)
        printf("%2.3f; ", registerData[i]);
    }
    curi = 0;
    for (int i = 0; i < strlen(command); i++)
        if (command[i] != ' ') {
            numbcom[curi++] = command[i];
            com[curi++] = command[i];
        } else break;
    com[curi] = '\0';
    curi++;
    for (int i = curi; i < strlen(command); i++)
        com[i - curi] = command[i];
    com[i - curi] = '\0';
    x = atoi(com);
    int ans = sw(numbcom);
    fprintf(out, "Ac: %2.3f R: %i x: %i\n", Ac, R, x);
    fclose(out);
    out = fopen("output.txt", "a");
    return ans;
}

int sw(char *numbcom) {
    if (strcmp(numbcom, "") == 0) {
        Ac = 0;
        Ac += x;
        return 0;
    } else if (strcmp(numbcom, "-") == 0) {
        Ac = 0;
        Ac -= x;
        return 0;
    } else if (strcmp(numbcom, "M") == 0) {
        Ac = 0;
        Ac += abs(x);
        return 0;
    } else if (strcmp(numbcom, "-M") == 0) {
        Ac = 0;
        Ac -= abs(x);
        return 0;
    }
    if (strcmp(numbcom, "h") == 0) {
        Ac += x;
        return 0;
    }
    if (strcmp(numbcom, "h-") == 0) {
        Ac -= x;
        return 0;
    }
    if (strcmp(numbcom, "hM") == 0) {
        Ac += abs(x);
        return 0;
    }
    if (strcmp(numbcom, "h-M") == 0) {
        Ac -= abs(x);
        return 0;
    }

    if (strcmp(numbcom, "R") == 0) {
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        registerData[R] = 0;
        registerData[R] += x;
        return 0;
    }
    if (strcmp(numbcom, "A") == 0) {
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        Ac = 0;
        Ac = registerData[R];
        return 0;
    }
    if (strcmp(numbcom, "X") == 0) {
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        x = (int) (x * registerData[R]);
        Ac = 0;
        registerData[R] = x;
        return 0;
    }
    if (strcmp(numbcom, "--") == 0) {
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        registerData[R] = 0;
        registerData[R] = Ac / x;
        return 0;
    }
    if (strcmp(numbcom, "C") == 0) {
        R--;
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        return 0;
    }
    if (strcmp(numbcom, "C'") == 0) {
        R++;
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        return 0;
    }
    if (strcmp(numbcom, "Cc") == 0) {
        if (Ac > 0) R = x - 1;
        return 0;
    }
    if (strcmp(numbcom, "Cc'") == 0) {
        if (Ac > 0) R = x + 1;
        return 0;
    }
    if (strcmp(numbcom, "S") == 0) {
        registerData[x] = Ac;
        R = x;
        if (R < 0 || R > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        return 0;
    }
    if (strcmp(numbcom, "Sp") == 0) {
        if (R < 11 || R > 1023 || x < 11 || x > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        for (i = 0; i < 12; i++) {
            registerData[R - 11 + i] = registerData[x - 11 + i];
        }
        return 0;
    }
    if (strcmp(numbcom, "Sp'") == 0) {
        if (R < 0 || R > 1012 || x < 11 || x > 1023) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        for (i = 0; i < 12; i++) {
            registerData[R + i] = registerData[x - 11 + i];
        }
        return 0;
    }
    if (strcmp(numbcom, "L") == 0) {
        Ac = Ac * 2;
        return 0;
    }
    if (strcmp(numbcom, "R") == 0) {
        Ac = Ac / 2;
        return 0;
    } else {
        printf("Exception in code: Unsupported command.");
        return 666;
    }
}


