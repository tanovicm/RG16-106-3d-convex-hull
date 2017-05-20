#ifndef __VECTOR_H_
#define __VECTOR_H_

#include "point.h"

/**
 * @brief Vector is determined with 3 scalar values.
 * 
 */
typedef Point Vector;

/**
 * @brief Creates vector from given values.
 * 
 * @param x, y, z 
 * Vector components
 * 
*/
Vector make_vector(double x, double y, double z);

/**
 * @brief Returns cross product of two vectors.
 * 
 * @param u, v
 * Vectors which cross product is computed.
 */
Vector cross(Vector u, Vector v);

/**
 * @brief Returns dot product of two vectors.
 * 
 * @param u, v
 * Vectors which dot product is computed.
 */
double dot(Vector u, Vector v);

/**
 * @brief Returns product of vector and constant.
 * 
 * @param u
 * Vector which is multiplied.
 * 
 * @param constant
 * Given vector is multiplied by constant.
 */
Vector mul(Vector u, double constant);

/**
 * @brief Returns normalized vector.
 * @param u
 * Vector which is normalized.
 */
Vector normalize(Vector u);

/**
 * @brief Returns length of vector.
 * 
 * @param u
 * Vector which length is computed.
 */
double vector_length(Vector u);

/**
 * @brief Returns sum of two vectors.
 * 
 * @param u, v
 * Vectors which sum is computed.
 */
Vector add_vector(Vector u, Vector v);

/**
 * @brief Returns substitution of two vectors.
 * 
 * @param u, v
 * Vector which substitution is computed.
 */
Vector sub_vector(Vector u, Vector v);

#endif // __VECTOR_H_