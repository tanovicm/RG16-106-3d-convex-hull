#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "plain.h"
#include "point.h"
#include "vector.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// calculates normal to the plain
Vector normal(Plain plain)
{
    // norm(CA x CB)
    return normalize(cross(sub_vector(*plain.a, *plain.c), 
                           sub_vector(*plain.b, *plain.c)));
}

// check if point belongs to specified plain
int is_point_in_triangle(Plain plain, Point point)
{
    Vector l1 = normalize(sub_vector(*plain.a, point));
    Vector l2 = normalize(sub_vector(*plain.b, point));
    Vector l3 = normalize(sub_vector(*plain.c, point));
    
    double angle = acos(dot(l1,l2)) + acos(dot(l2,l3)) + acos(dot(l3,l1));
    
    return abs(angle - 2*M_PI) < 0.0001;
}

// checking if projection of a point belogs to a plain
int contains_projection(Plain plain, Point point)
{
    Point projection = sub_vector(point, mul(normal(plain), distance(plain, point)));
    return is_point_in_triangle(plain, projection);
}

// calculates distance between point and plain
double distance(Plain plain, Point point)
{
    return dot(normal(plain), sub_vector(point,*plain.a));
}

/*
 * get_neighbors accepts plain and
 * in regard to that plain calculates
 * its neighbors 
 */

Node *get_neighbors(Plain *plain)
{	
    Node *neighbors = NULL;
    neighbors = add_node(neighbors,plain->ba);
    neighbors = add_node(neighbors,plain->ac);
    neighbors = add_node(neighbors,plain->cb);

    return neighbors;
}

/*
 * create plain with passed points a, b, c
 * 
 */
Plain * make_plain(Point *a, Point *b, Point *c)
{
    Plain * plain = malloc(sizeof(Plain));
    if (plain == NULL){
//         fprintf(stderr,"Malloc error!");
        exit(EXIT_FAILURE);
    }

    plain->a = a;
    plain->b = b;
    plain->c = c;
	
	plain->points = NULL;
	
	plain->ba = NULL;
	plain->ac = NULL;
	plain->cb = NULL;
    
    return plain;
}

/* 
 * returns array of points 
 * which create plain
 */ 
Node *get_points(Plain *plain)
{
    Node *points = NULL;
    points = add_node(points,plain->a);
    points = add_node(points,plain->b);
    points = add_node(points,plain->c);
  
	if(points != NULL)
		return points;
}

/*
 * return farthest point in 
 * regard to the passed plain
 * 
 */
Point* find_farthest_point(Plain plain)
{
    double max = 0;
    Point *pmax = NULL;

    for (Node *temp = plain.points; temp != NULL; temp = temp->next) {
        Point *point = (Point *)temp->elem;
        double dist = distance(plain,*point);
        
        if (dist > max) {
            max = dist;
            pmax = point;
        }
    }

    return pmax;
}


// draws plain
void draw_plain(Plain plain)
{
    glBegin(GL_TRIANGLES);
// 		glColor3d(plain.a->x, plain.b->y, plain.c->z);
		glVertex3d(plain.a->x, plain.a->y, plain.a->z);
        glVertex3d(plain.b->x, plain.b->y, plain.b->z);
        glVertex3d(plain.c->x, plain.c->y, plain.c->z);
    glEnd();
}
/* Debug
void print_plain(Plain *plain)
{
	if(plain == NULL) {
		printf("{NULL}");
		return;
	}
	
	printf("{A=");
	print_point(plain->a);
	printf(", B=");
	print_point(plain->b);
	printf(", C=");
	print_point(plain->c);
	printf(", points=");
	print_list(plain->points, print_point);
	printf("}");
} */ 
