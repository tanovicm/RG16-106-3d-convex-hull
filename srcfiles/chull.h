#ifndef __CHULL_H_
#define __CHULL_H_

#include "plain.h"

/**
 * @brief Creates convex convex hull.
 * From given points, convex hull is generated.
 * 
 * @param points
 * List of points in 3D space.
 * 
 * @return 
 * List of plains which should be drawn.
 */
Node *convex_hull(Node *points);

/**
 * @brief Initial convex hull. 
 * Look for the farthest points along axis and 
 * we have initial convex hull
 * 
 * @param
 * List of random generated points in 3D
 * 
 * @return List of initial plains.
 */
Node *initial_convex_hull(Node *points);

#endif // __CHULL_H_