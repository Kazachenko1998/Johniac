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

int pars(FILE *fp, int debag) {
    memset(command, 0, sizeof(command));
    memset(numbcom, 0, sizeof(numbcom));
    memset(com, 0, sizeof(com));

    int i = 0;
    for (i = 0; i < 10; i++)
        com[i] = ' ';
    fgets(command, 100, fp);//читаем очередную строку
    if (debag > 0) {
        printf(command);
        for (i = 0; i < _R_DATA + 1; i++) {
           if (debag > 1) printf("%i/%i - %i ;", registerData[i]->num, registerData[i]->den, i);
            fprintf(out, "%i/%i - %i ;", registerData[i]->num, registerData[i]->den, i);
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
    fprintf(out, "Ac: %i/%i, data[%i]: %i/%i, com: %s\n", _Ac->num, _Ac->den, _R, registerData[_R]->num,
            registerData[_R]->den, command);
    fclose(out);
    out = fopen("output.txt", "a");
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
    putInt(_Ac, 0);
    addInt(_Ac, _x);
    return 0;
}

int func_sub() {
    putInt(_Ac, 0);
    subInt(_Ac, _x);
    return 0;
}

int func_M() {
    putInt(_Ac, 0);
    addInt(_Ac, abs(_x));
    return 0;
}

int func_minM() {
    putInt(_Ac, 0);
    subInt(_Ac, abs(_x));
    return 0;
}

int func_h() {
    addInt(_Ac, _x);
    return 0;
}

int func_hmin() {
    subInt(_Ac, _x);
    return 0;
}

int func_hm() {
    addInt(_Ac, abs(_x));
    return 0;
}

int func_hminM() {
    subInt(_Ac, abs(_x));
    return 0;
}

int func_Rr() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(registerData[_R], 0);
    addInt(registerData[_R], _x);
    return 0;
}

int func_A() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(_Ac, 0);
    _Ac = registerData[_R];
    return 0;
}

int func_X() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(_Ac, 0);
    multInt(registerData[_R], _x);
    return 0;
}

int func_minmin() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    putInt(registerData[_R], 0);
    devInt(_Ac, _x);
    registerData[_R] = _Ac;
    return 0;
}

int func_C() {
    _R--;
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_C_() {
    _R++;
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    return 0;
}

int func_Cc() {
    if (_Ac->num > 0) _R = _x;
    return 0;
}

int func_Cc_() {
    if (_Ac->num <= 0) _R = _x;
    return 0;
}

int func_S() {
    _R = _x;
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    registerData[_x] = _Ac;
    return 0;
}

int func_Sp() {
    if (_R < _L_DATA || _R > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    registerData[_R]->num = registerData[_x]->num;

    return 0;
}

int func_Sp_() {
    if (_R < _L_DATA || _R > _R_DATA || _x < _L_DATA || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    registerData[_R]->den = registerData[_x]->den;

    return 0;
}

int func_L() {
    multInt(_Ac, 2);
    return 0;
}

int func_R() {
    devInt(_Ac, 2);
    return 0;
}