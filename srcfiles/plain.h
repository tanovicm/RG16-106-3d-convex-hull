#ifndef __PLAIN_H_
#define __PLAIN_H_

#include "point.h"
#include "list.h"

/**
 * @struct Plain
 * 
 * @brief Plain is a triangular plain in 3D space.
 * 
 * @var Plain::a
 * Member 'a' is one of the triangle points.
 * @var Plain::b
 * Member 'b' is one of the triangle points.
 * @var Plain::c
 * Member 'c' is one of the triangle points.
 * @var Plain::ba
 * Member 'ba' is pointer to adjecent plain containing points b and a.
 * @var Plain::ac
 * Member 'ac' is pointer to adjecent plain containing points a and c.
 * @var Plain::cb
 * Member 'cb' is pointer to adjecent plain containing points c and b.
 * @var Plain::points
 * Member 'points' is list of points whose projections are contained by this plain.
 */
typedef struct _plain {
    Point *a,*b,*c;
    struct _plain *ba, *ac, *cb;
    Node *points;
} Plain;

/**
 * @brief Makes plain from given points.
 *
 * @param a
 * First point of a plain. 
 * 
 * @param b
 * Second point of a plain.
 * 
 * @param c
 * Third point of a plain.
 * 
 * @return Plain
 */
Plain* make_plain(Point *a, Point *b, Point *c);

/**
 * @brief Geting list of points.
 * 
 * @param plain
 * Plain from which we get list of points.
 *
 * @return List of points.
 */
Node* get_points(Plain *plain);

/**
 * @brief Gets neighbors of a plain.
 * 
 * @param plain 
 * Plain from which we get neighbors.
 * 
 * @return 
 * List of plains which are neighbors.
 */
Node* get_neighbors(Plain *plain);

/**
 * @brief Returns distance between plain and point
 * 
 * The distance depends on side of point, so it may be positive or negative.
 * 
 * @param plain 
 * Plain from which we are calculating the distance.
 * @param point
 * Point to which we are calculating the distance.
 * 
 * @return Distance
 */
double distance(Plain plain, Point point);

/**
 * @brief Returns true if the plain contains projection of the point.
 * 
 * @param plain 
 * Plain in respect to which we calculate if given point belongs to plain
 * @param point
 * Point for which we calculate if belongs to plain
 * 
 * @return 	One if point belongs to plain, zero otherwise
 */
int contains_projection(Plain plain, Point point);

/**
 * @brief Looking for the farthes point relative to plain.
 * 
 * @param plain 
 * Plain in respect to which we look for point.
 * 
 * @return The farthest point.
 */
Point* find_farthest_point(Plain plain);

/**
 * @brief Draw plain.
 * 
 * @param plain 
 * Plain to draw
 */
void draw_plain(Plain plain);

// void print_plain(Plain *plain);

#endif // __PLAIN_H_