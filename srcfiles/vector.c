#include <math.h>

#include "vector.h"

Vector make_vector(double x, double y, double z) 
{
    Vector v;
    
    v.x = x;
    v.y = y;
    v.z = z;
    
    return v;
}

Vector cross(Vector u, Vector v) 
{
    return make_vector(u.y*v.z - u.z*v.y,
                       u.z*v.x - u.x*v.z,
                       u.x*v.y - u.y*v.x);
}

double dot(Vector u, Vector v) 
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vector mul(Vector u, double constant)
{
    return make_vector(u.x * constant, u.y*constant, u.z * constant);
}

double vector_length(Vector u)
{
    return sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

Vector normalize(Vector u)
{
    return mul(u, 1/vector_length(u));
}

Vector add_vector(Vector u, Vector v)
{
    return make_vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector sub_vector(Vector u, Vector v)
{
    return make_vector(u.x - v.x, u.y - v.y, u.z - v.z);
}