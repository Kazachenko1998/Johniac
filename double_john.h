
#ifndef UNTITLED2_DOUBLE_JOHN_H
typedef struct double_john {
    int num;
    int den;
} double_john;

void putInt(double_john*, int);

void add(double_john*, double_john*);

void addInt(double_john* one, int two);

void sub(double_john* one, double_john* two);

void subInt(double_john* one, int two);

void mult(double_john* one, double_john* two);

void multInt(double_john* one, int two);

void dev(double_john* one, double_john* two);

void devInt(double_john* one, int two);

#define UNTITLED2_DOUBLE_JOHN_H

#endif //UNTITLED2_DOUBLE_JOHN_H