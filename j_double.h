#ifndef RUN_DOUBLE_JOHN_H
#define RUN_DOUBLE_JOHN_H

typedef struct j_double {
    int numerator;
    int denominator;
} j_double;

struct j_double *new_j_double(int num, int den);

void free_j_double(struct j_double *value);

void put_int(struct j_double *, int);

void add(struct j_double*, j_double*);

void add_int(struct j_double *one, int two);

void subtract(struct j_double *one, struct j_double *two);

void sub_int(struct j_double *one, int two);

void multiply(struct j_double *one, j_double *two);

void multiply_int(struct j_double *one, int two);

void divide(struct j_double *one, struct j_double *two);

void divide_int(struct j_double *one, int two);

#endif //RUN_DOUBLE_JOHN_H