#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <conio.h>
int main() {
    FILE *fp, *out;
    int answer = 0, countSteps = 0, key, i, numbcom, x;
    char *command = malloc(sizeof(char) * 100), *com = malloc(sizeof(char) * 10);
    double Ac = 0, R = 0;
    int curi = 0;
    fp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    printf("Choose way of running program: \n 1. Full running \n 2. Running count of steps \n 3. Run kode step by step \n 4. Run kod step by step with printing results \n");
    scanf("%d", &answer);
    switch (answer) {
        case 1://полное выполнение кода
            while (!feof(fp)) {
                for (i = 0; i < 10; i++)
                    com[i] = (char) " ";
                fgets(command, 100, fp);//читаем очередную строку
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
                switch (numbcom) {
                    case 1:
                        Ac = 0;
                        Ac += x;
                        break;
                    case 2:
                        Ac = 0;
                        Ac -= x;
                        break;
                    case 3:
                        Ac = 0;
                        Ac += abs(x);
                        break;
                    case 4:
                        Ac = 0;
                        Ac -= abs(x);
                        break;
                    case 5:
                        Ac += x;
                        break;
                    case 6:
                        Ac -= x;
                        break;
                    case 7:
                        Ac += abs(x);
                        break;
                    case 8:
                        Ac -= abs(x);
                        break;
                    case 9:
                        R = 0;
                        R += x;
                        break;
                    case 10:
                        Ac = 0;
                        Ac = R;
                        break;
                    case 11:
                        x = x * R;
                        Ac = 0;
                        R = x;
                        break;
                    case 12:
                        R = 0;
                        R = Ac / x;
                        break;
                    case 15:
                        x = ~x;
                        break;
                    case 16:
                        x = x;
                        break;
                }
            }
            fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
            fclose(out);
            break;
        case 2: //выполнение определенного числа шагов
            printf("Input count of steps \n");
            scanf("%d", &countSteps);
            while (countSteps > 0) {
                for (i = 0; i < 10; i++)
                    com[i] = " ";
                fgets(command, 100, fp);//читаем очередную строку
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
                switch (numbcom) {
                    case 1:
                        Ac = 0;
                        Ac += x;
                        break;
                    case 2:
                        Ac = 0;
                        Ac -= x;
                        break;
                    case 3:
                        Ac = 0;
                        Ac += abs(x);
                        break;
                    case 4:
                        Ac = 0;
                        Ac -= abs(x);
                        break;
                    case 5:
                        Ac += x;
                        break;
                    case 6:
                        Ac -= x;
                        break;
                    case 7:
                        Ac += abs(x);
                        break;
                    case 8:
                        Ac -= abs(x);
                        break;
                    case 9:
                        R = 0;
                        R += x;
                        break;
                    case 10:
                        Ac = 0;
                        Ac = R;
                        break;
                    case 11:
                        x = x * R;
                        Ac = 0;
                        R = x;
                        break;
                    case 12:
                        R = 0;
                        R = Ac / x;
                        break;
                    case 15:
                        x = ~x;
                        break;
                    case 16:
                        x = x;
                        break;
                }
                countSteps--;
            }
            fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
            fclose(out);
            break;
        case 3: //выполнить код пошагово
            while (1) {
                printf("Press the button... \n");
                key = getch();
                switch (key) {
                    case 32:// Space- следующая команда
                        for (i = 0; i < 10; i++)
                            com[i] = " ";
                        fgets(command, 100, fp);//читаем очередную строку
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
                        switch (numbcom) {
                            case 1:
                                Ac = 0;
                                Ac += x;
                                break;
                            case 2:
                                Ac = 0;
                                Ac -= x;
                                break;
                            case 3:
                                Ac = 0;
                                Ac += abs(x);
                                break;
                            case 4:
                                Ac = 0;
                                Ac -= abs(x);
                                break;
                            case 5:
                                Ac += x;
                                break;
                            case 6:
                                Ac -= x;
                                break;
                            case 7:
                                Ac += abs(x);
                                break;
                            case 8:
                                Ac -= abs(x);
                                break;
                            case 9:
                                R = 0;
                                R += x;
                                break;
                            case 10:
                                Ac = 0;
                                Ac = R;
                                break;
                            case 11:
                                x = x * R;
                                Ac = 0;
                                R = x;
                                break;
                            case 12:
                                R = 0;
                                R = Ac / x;
                                break;
                            case 15:
                                x = ~x;
                                break;
                            case 16:
                                x = x;
                                break;
                        }
                        break;
                    case 13://Enter - выполнить программу до конца
                        while (!feof(fp)) {
                            for (i = 0; i < 10; i++)
                                com[i] = " ";
                            fgets(command, 100, fp);//читаем очередную строку
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
                            switch (numbcom) {
                                case 1:
                                    Ac = 0;
                                    Ac += x;
                                    break;
                                case 2:
                                    Ac = 0;
                                    Ac -= x;
                                    break;
                                case 3:
                                    Ac = 0;
                                    Ac += abs(x);
                                    break;
                                case 4:
                                    Ac = 0;
                                    Ac -= abs(x);
                                    break;
                                case 5:
                                    Ac += x;
                                    break;
                                case 6:
                                    Ac -= x;
                                    break;
                                case 7:
                                    Ac += abs(x);
                                    break;
                                case 8:
                                    Ac -= abs(x);
                                    break;
                                case 9:
                                    R = 0;
                                    R += x;
                                    break;
                                case 10:
                                    Ac = 0;
                                    Ac = R;
                                    break;
                                case 11:
                                    x = x * R;
                                    Ac = 0;
                                    R = x;
                                    break;
                                case 12:
                                    R = 0;
                                    R = Ac / x;
                                    break;
                                case 15:
                                    x = ~x;
                                    break;
                                case 16:
                                    x = x;
                                    break;
                            }
                        }
                        fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
                        fclose(out);
                        return 0;
                        break;
                    case 27://Esc - прекратить выполнение программы
                        return 0;//завершаем работу программы
                        break;
                }
            }
            break;
        case 4: //выполнить код пошагово с выводом результата
            while (1) {
                printf("Press the button... \n");
                key = getch();
                switch (key) {
                    case 32:// Space- следующая команда
                        for (i = 0; i < 10; i++)
                            com[i] = " ";
                        fgets(command, 100, fp);//читаем очередную строку
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
                        switch (numbcom) {
                            case 1:
                                Ac = 0;
                                Ac += x;
                                break;
                            case 2:
                                Ac = 0;
                                Ac -= x;
                                break;
                            case 3:
                                Ac = 0;
                                Ac += abs(x);
                                break;
                            case 4:
                                Ac = 0;
                                Ac -= abs(x);
                                break;
                            case 5:
                                Ac += x;
                                break;
                            case 6:
                                Ac -= x;
                                break;
                            case 7:
                                Ac += abs(x);
                                break;
                            case 8:
                                Ac -= abs(x);
                                break;
                            case 9:
                                R = 0;
                                R += x;
                                break;
                            case 10:
                                Ac = 0;
                                Ac = R;
                                break;
                            case 11:
                                x = x * R;
                                Ac = 0;
                                R = x;
                                break;
                            case 12:
                                R = 0;
                                R = Ac / x;
                                break;
                            case 15:
                                x = ~x;
                                break;
                            case 16:
                                x = x;
                                break;
                        }
                        fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
                        fclose(out);
                        out = fopen("output.txt", "a");
                        break;
                    case 13://Enter - выполнить программу до конца
                        while (!feof(fp)) {
                            for (i = 0; i < 10; i++)
                                com[i] = " ";
                            fgets(command, 100, fp);//читаем очередную строку
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
                            switch (numbcom) {
                                case 1:
                                    Ac = 0;
                                    Ac += x;
                                    break;
                                case 2:
                                    Ac = 0;
                                    Ac -= x;
                                    break;
                                case 3:
                                    Ac = 0;
                                    Ac += abs(x);
                                    break;
                                case 4:
                                    Ac = 0;
                                    Ac -= abs(x);
                                    break;
                                case 5:
                                    Ac += x;
                                    break;
                                case 6:
                                    Ac -= x;
                                    break;
                                case 7:
                                    Ac += abs(x);
                                    break;
                                case 8:
                                    Ac -= abs(x);
                                    break;
                                case 9:
                                    R = 0;
                                    R += x;
                                    break;
                                case 10:
                                    Ac = 0;
                                    Ac = R;
                                    break;
                                case 11:
                                    x = x * R;
                                    Ac = 0;
                                    R = x;
                                    break;
                                case 12:
                                    R = 0;
                                    R = Ac / x;
                                    break;
                                case 15:
                                    x = ~x;
                                    break;
                                case 16:
                                    x = x;
                                    break;
                            }
                            fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
                            fclose(out);
                            out = fopen("output.txt", "a");
                        }
                        fprintf(out, "Ac: %2.3f R: %2.3f \n", Ac, R);
                        fclose(out);
                        return 0;
                        break;
                    case 27://Esc - прекратить выполнение программы
                        return 0;//завершаем работу программы
                        break;
                }
            }
            break;
    }
    fclose(fp);
    fclose(out);
    return 0;
}