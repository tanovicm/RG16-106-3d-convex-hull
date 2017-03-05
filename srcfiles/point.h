#ifndef  __POINT_H_
#define  __POINT_H_ 

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
    double x,y,z;
} Point;

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

void print_point(Point *point);

#endif // __POINT_H_ 