#ifndef __VECTOR_H_
#define __VECTOR_H_

#include "point.h"

typedef Point Vector;

Vector make_vector(double x, double y, double z);

Vector cross(Vector u, Vector v);
double dot(Vector u, Vector v);
Vector mul(Vector u, double constant);
Vector normalize(Vector u);
double vector_length(Vector u);
Vector add_vector(Vector u, Vector v);
Vector sub_vector(Vector u, Vector v);

#endif // __VECTOR_H_