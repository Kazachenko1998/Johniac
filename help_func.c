#include <mem.h>
#include <stdlib.h>
#include "help_func.h"
#include "constant.h"

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
        com[i] = (char) " ";
    fgets(command, 100, fp);//читаем очередную строку
    if (debag) {
        printf(command);
        for (i = 0; i < _R_DATA; i++)
            printf("%2.3f; ", registerData[i]);
    }
    _curi = 0;
    printf(command);
    for (i = 0; i < strlen(command); i++) {

        if (command[i] != ' ') {
            numbcom[i] = command[i];
            _curi++;
        } else break;
    }
    _curi++;
    for (i = _curi; i < strlen(command); i++)
        com[i - _curi] = command[i];
    com[i - _curi] = '\0';
    _x = atoi(com);
    printf(numbcom);
    int ans = sw(numbcom);
    fprintf(out, "Ac: %2.3f R: %i x: %i\n", _Ac, _R, _x);
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
    _Ac = 0;
    _Ac += _x;
    return 0;
}

int func_sub() {
    _Ac = 0;
    _Ac -= _x;
    return 0;
}

int func_M() {
    _Ac = 0;
    _Ac += abs(_x);
    return 0;
}

int func_minM() {
    _Ac = 0;
    _Ac -= abs(_x);
    return 0;
}

int func_h() {
    _Ac += _x;
    return 0;
}

int func_hmin() {
    _Ac -= _x;
    return 0;
}

int func_hm() {
    _Ac += abs(_x);
    return 0;
}

int func_hminM() {
    _Ac -= abs(_x);
    return 0;
}

int func_Rr() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    registerData[_R] = 0;
    registerData[_R] += _x;
    return 0;
}

int func_A() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    _Ac = 0;
    _Ac = registerData[_R];
    return 0;
}

int func_X() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    _Ac = 0;
    registerData[_R] *= _x;
    return 0;
}

int func_minmin() {
    if (_R < _L_DATA || _R > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    registerData[_R] = 0;
    registerData[_R] = _Ac / _x;
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
    if (_Ac > 0) _R = _x;
    return 0;
}

int func_Cc_() {
    if (_Ac <= 0) _R = _x;
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

    if (_R < _L_DATA + 11 || _R > _R_DATA || _x < _L_DATA + 11 || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    for (int i = 0; i < 12; i++) {
        registerData[_R - 11 + i] = registerData[_x - 11 + i];
    }
    return 0;
}

int func_Sp_() {
    if (_R < _L_DATA || _R > _R_DATA - 11 || _x < _L_DATA + 11 || _x > _R_DATA) {
        printf("Exception in code: Index of bound.");
        return 10;
    }
    for (int i = 0; i < 12; i++) {
        registerData[_R + i] = registerData[_x - 11 + i];
    }
    return 0;
}

int func_L() {
    _Ac = _Ac * 2;
    return 0;
}

int func_R() {
    _Ac = _Ac / 2;
    return 0;
}