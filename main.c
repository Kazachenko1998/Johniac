#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <conio.h>
#include <stdbool.h>


double Ac = 0, R = 0;
int x;
char *com;
char *command;
FILE *fp, *out;
int countSteps = 0, key, i, numbcom;
int curi = 0;
char answer[255];

int sw(int numbcom) {
    switch (numbcom) {
        case 1:
            Ac = 0;
            Ac += x;
            return 0;
        case 2:
            Ac = 0;
            Ac -= x;
            return 0;
        case 3:
            Ac = 0;
            Ac += abs(x);
            return 0;
        case 4:
            Ac = 0;
            Ac -= abs(x);
            return 0;
        case 5:
            Ac += x;
            return 0;
        case 6:
            Ac -= x;
            return 0;
        case 7:
            Ac += abs(x);
            return 0;
        case 8:
            Ac -= abs(x);
            return 0;
        case 9:
            R = 0;
            R += x;
            return 0;
        case 10:
            Ac = 0;
            Ac = R;
            return 0;
        case 11:
            x = (int) (x * R);
            Ac = 0;
            R = x;
            return 0;
        case 12:
            R = 0;
            R = Ac / x;
            return 0;
        case 15:
            x = ~x;
            return 0;
        case 16:
            return 0;
        case 18:
            Ac = Ac * 2;
            return 0;
        case 19:
            Ac = Ac * 2;
            return 0;
        case 20:
            Ac = Ac * 2;
            return 0;
        case 21:
            Ac = Ac / 2;
            return 0;
        default:
            printf("Exception: Unsupported command.");
            return 666;
    }
}

int pars(FILE *fp, int debag) {
    for (i = 0; i < 10; i++)
        com[i] = (char) " ";
    fgets(command, 100, fp);//читаем очередную строку
    if (debag) printf(command);
    curi = 0;
    for (int i = 0; i < strlen(command); i++)
        if (command[i] >= '0' && command[i] <= '9')
            com[curi++] = command[i];
        else break;
    com[curi] = '\0';
    curi++;
    numbcom = atoi(com);
    for (int i = curi; i < strlen(command); i++)
        com[i - curi] = command[i];
    com[i - curi] = '\0';
    x = atoi(com);
    int ans = sw(numbcom);
    fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
    fclose(out);
    out = fopen("output.txt", "a");
    return ans;
}

int main() {
    com = malloc(sizeof(char) * 10);
    command = malloc(sizeof(char) * 10);
    fp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    stop:;
    printf("Choose way of running program: \n"
           " fr     Full running \n"
           " rfors  Running count of steps \n"
           " sbs    Run code step by step \n"
           " sbsdeb Run code step by step with printing results \n");
    gets(answer);
    if (strcmp(answer, "fr") == 0) {//полное выполнение кода
        while (!feof(fp)) {
            if (pars(fp, 0) == 666) goto fail;
        }
    } else if (strcmp(answer, "rfors") == 0) { //выполнение определенного числа шагов
        printf("Input count of steps \n");
        scanf("%d", &countSteps);
        while (countSteps > 0) {
            if (pars(fp, 0) == 666) goto fail;
            countSteps--;
        }
    } else if (strcmp(answer, "sbs") == 0) { //выполнить код пошагово
        while (1) {
            printf("Press the SPACE... \n");
            key = getch();
            switch (key) {
                case 32:// Space- следующая команда
                    if (pars(fp, 0) == 666) goto fail;
                    break;
                case 27://Esc - прекратить выполнение программы
                    break;//завершаем работу программы
                default:
                    while (!feof(fp)) {
                        if (pars(fp, 0) == 666) goto fail;
                    }
                    break;
            }
            if (key == 27) break;
        }
    } else if (strcmp(answer, "sbsdeb") == 0) { //выполнить код пошагово с выводом результата
        while (!feof(fp)) {
            printf("Press the SPACE... \n");
            key = getch();
            switch (key) {
                case 32:
                    // Space- следующая команда
                    if (pars(fp, 0) == 666) goto fail;
                    printf("Ac: %2.3f R: %2.3f \n", Ac, R);
                    break;
                case 27://Esc - прекратить выполнение программы
                    break;//завершаем работу программы
                default:
                    while (!feof(fp)) {
                        if (pars(fp, 0) == 666) goto fail;
                    }
                    break;
            }
            if (key == 27) break;
        }
    } else
        printf("not found command");
        goto stop;

    fclose(fp);
    fclose(out);
    printf("You code completed successful. Press any button");
    getch();
    return 0;

    fail:;
    getch();
    return 0;
}