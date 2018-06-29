//
// Created by kazac on 22.06.2018.
//


#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "double_john.h"

double_john *new_double_john(int num, int den) {
    double_john *var = malloc(sizeof(double_john));
    memset(var, 0, sizeof(double_john));
  //  free(var);
    var->den = den;
    var->num = num;
    return var;
}

void putInt(double_john *this, int num) {
    this->num = num;
    this->den = 1;
}

int NOD(int n1, int n2) {
    int div;
    if (n1 == n2)   // если числа равны, НОД найден
        return n1;
    int d = n1 - n2; // Находим разность чисел
    if (d < 0)       // если разность отрицательная,
    {
        d = -d;     // меняем знак
        div = NOD(n1, d); // вызываем функцию NOD() для двух наименьших чисел
    } else      // если разность n1-n2 положительная
    {
        div = NOD(n2, d); // вызываем функцию NOD() для двух наименьших чисел
    }
    return div;
}

void NOD_john(double_john *one) {
    int nod = NOD(abs(one->den), abs(one->num));
    one->den /= nod;
    one->num /= nod;
    if (one->den == 0) one->den = 1;
    if (one->den < 0) {
        one->den *= -1;
        one->num *= -1;
    }
}

void add(double_john *one, double_john *two) {
    int d2 = two->den;
    int d1 = one->den;
    one->num = one->num * d2 + two->num * d1;
    one->den = one->den * d2;

    NOD_john(one);
}

void addInt(double_john *one, int two) {
    double_john *new = (double_john *) malloc(sizeof(double_john));
    new->num = two;
    new->den = 1;
    add(one, new);
}

void sub(double_john *one, double_john *two) {
    int d2 = two->den;
    int d1 = one->den;
    one->num = one->num * d2 - two->num * d1;
    one->den = one->den * d2;
    NOD_john(one);
}

void subInt(double_john *one, int two) {
    double_john *new = (double_john *) malloc(sizeof(double_john));
    new->num = two;
    new->den = 1;
    sub(one, new);
}

void mult(double_john *one, double_john *two) {
    one->num = one->num * two->num;
    one->den = one->den * two->den;
    NOD_john(one);
}

void multInt(double_john *one, int two) {
    double_john *new = (double_john *) malloc(sizeof(double_john));
    new->num = two;
    new->den = 1;
    mult(one, new);
}

void dev(double_john *one, double_john *two) {
    one->num = one->num * two->den;
    one->den = one->den * two->num;
    NOD_john(one);
}

void devInt(double_john *one, int two) {
    double_john *new = (double_john *) malloc(sizeof(double_john));
    new->num = two;
    new->den = 1;
    dev(one, new);
}

