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

Plain * make_plain(Point *a, Point *b, Point *c);
Node *get_points(Plain *plain);
Node *get_neighboors(Plain *plain);


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
 * Ravan u odnosu na koju racunamo pripadnost tacke
 * @param point
 * Tacka za koju racunamo da li prirapada ravni.
 * 
 * @return pripadnost
 */
int contains_projection(Plain plain, Point point);

/**
 * @brief Trazi najdalju tacku u odnosu na trougao.
 * 
 * @param plain 
 * Ravan u odnosu na koju trazi najdalju tacku
 * 
 * @return najdalja tacka
 */
Point* find_farthest_point(Plain plain);

/**
 * @brief Draw plain.
 * 
 * @param plain 
 * Plain to draw
 */
void draw_plain(Plain plain);

void print_plain(Plain *plain);

#endif // __PLAIN_H_