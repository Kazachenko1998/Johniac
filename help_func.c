#include <mem.h>
#include <stdlib.h>
#include "help_func.h"
#include "constant.h"


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
    int ans = sw(numbcom);
    fprintf(out, "Ac: %2.3f R: %i x: %i\n", _Ac, _R, _x);
    fclose(out);
    out = fopen("output.txt", "a");
    return ans;
}


int sw(char *numbcom) {
    int i = 0;
    if (strcmp(numbcom, "") == 0) {
        _Ac = 0;
        _Ac += _x;
        return 0;
    } else if (strcmp(numbcom, "-") == 0) {
        _Ac = 0;
        _Ac -= _x;
        return 0;
    } else if (strcmp(numbcom, "M") == 0) {
        _Ac = 0;
        _Ac += abs(_x);
        return 0;
    } else if (strcmp(numbcom, "-M") == 0) {
        _Ac = 0;
        _Ac -= abs(_x);
        return 0;
    } else if (strcmp(numbcom, "h") == 0) {
        _Ac += _x;
        return 0;
    } else if (strcmp(numbcom, "h-") == 0) {
        _Ac -= _x;
        return 0;
    } else if (strcmp(numbcom, "hM") == 0) {
        _Ac += abs(_x);
        return 0;
    } else if (strcmp(numbcom, "h-M") == 0) {
        _Ac -= abs(_x);
        return 0;
    } else if (strcmp(numbcom, "R") == 0) {
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        registerData[_R] = 0;
        registerData[_R] += _x;
        return 0;
    } else if (strcmp(numbcom, "A") == 0) {
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        _Ac = 0;
        _Ac = registerData[_R];
        return 0;
    } else if (strcmp(numbcom, "X") == 0) {
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        _Ac = 0;
        registerData[_R] *= _x;
        return 0;
    } else if (strcmp(numbcom, "--") == 0) {
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        registerData[_R] = 0;
        registerData[_R] = _Ac / _x;
        return 0;
    } else if (strcmp(numbcom, "C") == 0) {
        _R--;
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        return 0;
    } else if (strcmp(numbcom, "C'") == 0) {
        _R++;
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        return 0;
    } else if (strcmp(numbcom, "Cc") == 0) {
        if (_Ac > 0) _R = _x;
        return 0;
    } else if (strcmp(numbcom, "Cc'") == 0) {
        if (_Ac <= 0) _R = _x;
        return 0;
    } else if (strcmp(numbcom, "S") == 0) {
        _R = _x;
        if (_R < _L_DATA || _R > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        registerData[_x] = _Ac;


        return 0;
    } else if (strcmp(numbcom, "Sp") == 0) {
        if (_R < 11 || _R > _R_DATA || _x < 11 || _x > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        for (i = 0; i < 12; i++) {
            registerData[_R - 11 + i] = registerData[_x - 11 + i];
        }
        return 0;
    } else if (strcmp(numbcom, "Sp'") == 0) {
        if (_R < _L_DATA || _R > 1012 || _x < 11 || _x > _R_DATA) {
            printf("Exception in code: Index of bound.");
            return 10;
        }
        for (i = 0; i < 12; i++) {
            registerData[_R + i] = registerData[_x - 11 + i];
        }
        return 0;
    } else if (strcmp(numbcom, "L") == 0) {
        _Ac = _Ac * 2;
        return 0;
    } else if (strcmp(numbcom, "R") == 0) {
        _Ac = _Ac / 2;
        return 0;
    } else {
        printf("Exception in code: Unsupported command.");
        return 666;
    }
}
