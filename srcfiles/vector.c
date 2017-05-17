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

// calculates cross product of two vectors

Vector cross(Vector u, Vector v) 
{
    return make_vector(u.y*v.z - u.z*v.y,
                       u.z*v.x - u.x*v.z,
                       u.x*v.y - u.y*v.x);
}

// calculates scalar product of two vectors
double dot(Vector u, Vector v) 
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

// multiply vector with constant
Vector mul(Vector u, double constant)
{
    return make_vector(u.x * constant, u.y*constant, u.z * constant);
}

//calculates length of vector
double vector_length(Vector u)
{
    return sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

// calculates normalized vector from given vector u
Vector normalize(Vector u)
{
    return mul(u, 1/vector_length(u));
}

// sums two vector
Vector add_vector(Vector u, Vector v)
{
    return make_vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

// subtracts two vectors
Vector sub_vector(Vector u, Vector v)
{
    return make_vector(u.x - v.x, u.y - v.y, u.z - v.z);
}