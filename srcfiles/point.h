#ifndef  __POINT_H_
#define  __POINT_H_ 

/*
VISUALSTUDIO branch (c) 2021 by dbj@dbj.org
*/
// DBJ: notice this is a top level include for this project
// thus very good place to include common.h
// and not include it where not necessary
#include "common.h"

/**
 * @struct Point
 *
 * @brief Point is a point in 3D space.
 *
 * @var Point::x
 * Member 'x' contains the x coordinate of the point.
 * @var Point::y
 * Member 'y' contains the y coordinate of the point.
 * @var Point::z
 * Member 'z' contains the y coordinate of the point.
 */
typedef struct {
	double x, y, z;
} Point;

/**
 * @brief Returns a random number.
 *
 * @return Random number.
 */

double random_number();

/**
 * @brief Returns a random point in 3D space.
 *
 * All coordinat values are in [-1, 1] interval.
 *
 * @return Random point
 */
Point* random_point();

/**
 * @brief Draw point.
 *
 * @param point
 * Point to draw
 */
void draw_point(Point point);

/**
 * @brief Prints point for debug.
 *
 * @param point
 * Prints given point

 void print_point(Point *point);
 */

 /**
  * @brief Calculates distance between given point and line setpoint
  *
  * @param point
  * Relative to which one we calculates distance
  *
  * @param lineA lineB
  * Line bound relative to which calculation is done
  *
  * @return Distance between point and line given with points
  *
  */
double point_to_line_distance(Point point, Point lineA, Point lineB);

#endif // __POINT_H_ 