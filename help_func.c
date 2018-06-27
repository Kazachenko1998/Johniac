#include <stdlib.h>
#include "help_func.h"
#include "constant.h"
#include <string.h>

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

char *numbcom;
char *com;
char *command;
int _curi;
int _x;
constant *constantThis;

int pars(int debag, constant *constant) {
    com = malloc(sizeof(char) * 100);
    command = malloc(sizeof(char) * 10);
    numbcom = malloc(sizeof(char) * 100);
    memset(command, 0, sizeof(char) * 10);
    memset(numbcom, 0, sizeof(char) * 100);
    memset(com, 0, sizeof(char) * 100);
    free(command);
    free(numbcom);
    free(com);
    constantThis = constant;
    unsigned int i = 0;
    for (i = 0; i < 10; i++)
        com[i] = ' ';
    fgets(command, 100, constant->fp);//читаем очередную строку
    if (debag > 0) {
        printf(command);
        for (i = 0; i < _R_DATA + 1; i++) {
            if (debag > 1)
                printf("%i/%i - %i ;", constant->registerData[i]->num, constant->registerData[i]->den, i);
            fprintf(constant->out, "%i/%i - %i ;", constant->registerData[i]->num,
                    constant->registerData[i]->den, i);
        }
    }
    _curi = 0;
    printf("%s\n", command);
    for (i = 0; i < strlen(command); i++) {

        if (command[i] != ' ' && command[i] != '\n' && command[i] != '\0') {
            numbcom[i] = command[i];
            _curi++;
        } else break;
    }
    _curi++;
    for (i = _curi; i < strlen(command); i++) {
        if (('0' <= command[i] && command[i] <= '9') || command[i] == '-' || command[i] == ' ' || command[i] == '\n' ||
            command[i] == '\0')
            com[i - _curi] = command[i];
        else {
            printf("Exception in code: Unsupported number.");
            return 665;
        }
    }

    com[i - _curi] = '\0';
    _x = atoi(com);

    int ans = sw(numbcom);
    printf("Ac: %i/%i, data[%i]: %i/%i, com: %s", constant->_Ac->num, constant->_Ac->den,
           constant->_R, constant->registerData[constant->_R]->num,
           constant->registerData[constant->_R]->den, command);
//    fopen_s((FILE **) constant->out, "output.txt", "a");

    fprintf(constant->out, "Ac: %i/%i, data[%i]: %i/%i, com: %s\n", constant->_Ac->num, constant->_Ac->den,
            constant->_R, constant->registerData[constant->_R]->num,
            constant->registerData[constant->_R]->den, command);
    fclose(constant->out);
    fopen_s((FILE **) constant->out, "output.txt", "a");
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
        printf("Exception in code: Unsupported command.");
        return 666;
    }
}

////////////////////////////////////////////////////////////////


int func_add() {
    putInt(constantThis->_Ac, 0);
    addInt(constantThis->_Ac, _x);
    return 0;
}

int func_sub() {
    putInt(constantThis->_Ac, 0);
    subInt(constantThis->_Ac, _x);
    return 0;
}

int func_M() {
    putInt(constantThis->_Ac, 0);
    addInt(constantThis->_Ac, abs(_x));
    return 0;
}

int func_minM() {
    putInt(constantThis->_Ac, 0);
    subInt(constantThis->_Ac, abs(_x));
    return 0;
}

int func_h() {
    addInt(constantThis->_Ac, _x);
    return 0;
}

int func_hmin() {
    subInt(constantThis->_Ac, _x);
    return 0;
}

int func_hm() {
    addInt(constantThis->_Ac, abs(_x));
    return 0;
}

int func_hminM() {
    subInt(constantThis->_Ac, abs(_x));
    return 0;
}

int func_Rr() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(constantThis->registerData[constantThis->_R], 0);
    addInt(constantThis->registerData[constantThis->_R], _x);
    return 0;
}

int func_A() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(constantThis->_Ac, 0);
    constantThis->_Ac = constantThis->registerData[constantThis->_R];
    return 0;
}

int func_X() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(constantThis->_Ac, 0);
    multInt(constantThis->registerData[constantThis->_R], _x);
    return 0;
}

int func_minmin() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(constantThis->registerData[constantThis->_R], 0);
    devInt(constantThis->_Ac, _x);
    constantThis->registerData[constantThis->_R] = constantThis->_Ac;
    return 0;
}

int func_C() {
    constantThis->_R--;
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_C_() {
    constantThis->_R++;
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_Cc() {
    if (constantThis->_Ac->num > 0) constantThis->_R = _x;
    return 0;
}

int func_Cc_() {
    if (constantThis->_Ac->num <= 0) constantThis->_R = _x;
    return 0;
}

int func_S() {
    constantThis->_R = _x;
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    constantThis->registerData[_x] = constantThis->_Ac;
    return 0;
}

int func_Sp() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    constantThis->registerData[constantThis->_R]->num = constantThis->registerData[_x]->num;

    return 0;
}

int func_Sp_() {
    if (constantThis->_R < _L_DATA || constantThis->_R > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    constantThis->registerData[constantThis->_R]->den = constantThis->registerData[_x]->den;

    return 0;
}

int func_L() {
    multInt(constantThis->_Ac, 2);
    return 0;
}

int func_R() {
    devInt(constantThis->_Ac, 2);
    return 0;
}