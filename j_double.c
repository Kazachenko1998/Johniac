#include <stdio.h>
#include <stdlib.h>
#include "j_double.h"

j_double *new_j_double(int num, int den) {
    j_double *value = calloc(1, sizeof(j_double));
    value->denominator = den;
    value->numerator = num;
    return value;
}

void put_int(j_double *this, int num) {
    this->numerator = num;
    this->denominator = 1;
}

static int nod(int n1, int n2) {
    int div;
    if (n1 == n2)           // если числа равны, НОД найден
        return n1;
    if (n1 == 0 || n2 == 0) {
        return 1;
    }
    int d = n1 - n2;        // Находим разность чисел
    if (d < 0)              // если разность отрицательная,
    {
        d = -d;             // меняем знак
        div = nod(n1, d);   // вызываем функцию nod() для двух наименьших чисел
    } else                  // если разность n1-n2 положительная
    {
        div = nod(n2, d);   // вызываем функцию nod() для двух наименьших чисел
    }
    return div;
}

void j_nod(j_double *one) {
    int nod_value = nod(abs(one->denominator), abs(one->numerator));
    one->denominator /= nod_value;
    one->numerator /= nod_value;
    if (one->denominator == 0) {
        one->denominator = 1;
    }
    if (one->denominator < 0) {
        one->denominator *= -1;
        one->numerator *= -1;
    }
}

void add(j_double *one, j_double *two) {
    int d2 = two->denominator;
    int d1 = one->denominator;
    one->numerator = one->numerator * d2 + two->numerator * d1;
    one->denominator = one->denominator * d2;
    j_nod(one);
}

void add_int(j_double *one, int two) {
    j_double *new_double = calloc(1, sizeof(j_double));
    new_double->numerator = two;
    new_double->denominator = 1;
    add(one, new_double);
    free_j_double(new_double);
}

void subtract(j_double *one, j_double *two) {
    int d2 = two->denominator;
    int d1 = one->denominator;
    one->numerator = one->numerator * d2 - two->numerator * d1;
    one->denominator = one->denominator * d2;
    j_nod(one);
}

void sub_int(j_double *one, int two) {
    j_double *new_double = calloc(1, sizeof(j_double));
    new_double->numerator = two;
    new_double->denominator = 1;
    subtract(one, new_double);
    free_j_double(new_double);
}

void multiply(j_double *one, j_double *two) {
    one->numerator = one->numerator * two->numerator;
    one->denominator *= two->denominator;
    j_nod(one);
}

void multiply_int(j_double *one, int two) {
    j_double *new_double = calloc(1, sizeof(j_double));
    new_double->numerator = two;
    new_double->denominator = 1;
    multiply(one, new_double);
    free_j_double(new_double);
}

void divide(j_double *one, j_double *two) {
    one->numerator *= two->denominator;
    one->denominator *= two->numerator;
    j_nod(one);
}

void divide_int(j_double *one, int two) {
    j_double *new_double = calloc(1, sizeof(j_double));
    new_double->numerator = two;
    new_double->denominator = 1;
    divide(one, new_double);
    free_j_double(new_double);
}

void free_j_double(struct j_double *value) {
    if (value) {
        free(value);
    }
}
