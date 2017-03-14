#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "plain.h"
#include "point.h"
#include "vector.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Vector normal(Plain plain)
{
    // norm(CA x CB)
    return normalize(cross(sub_vector(*plain.a, *plain.c), 
                           sub_vector(*plain.b, *plain.c)));
}
int is_point_in_triangle(Plain plain, Point point)
{
    Vector l1 = normalize(sub_vector(*plain.a, point));
    Vector l2 = normalize(sub_vector(*plain.b, point));
    Vector l3 = normalize(sub_vector(*plain.c, point));
    
    double angle = acos(dot(l1,l2)) + acos(dot(l2,l3)) + acos(dot(l3,l1));
    
    return abs(angle - 2*M_PI) < 0.0001;
}

int contains_projection(Plain plain, Point point)
{
    Point projection = sub_vector(point, mul(normal(plain), distance(plain, point)));
    return is_point_in_triangle(plain, projection);
}

double distance(Plain plain, Point point)
{
    return dot(normal(plain), sub_vector(point,*plain.a));
}

Node *get_neighboors(Plain *plain)
{	
    Node *neighboors = NULL;
    neighboors = add_node(neighboors,plain->ba);
    neighboors = add_node(neighboors,plain->ac);
    neighboors = add_node(neighboors,plain->cb);

    return neighboors;
}
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

Node *get_points(Plain *plain)
{
	
	
    /*NAPISI VRATI listu Tacaka [a,b,c]*/
    Node *points = NULL;
    points = add_node(points,plain->a);
    points = add_node(points,plain->b);
    points = add_node(points,plain->c);
  
	if(points != NULL)
		return points;
}
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

void draw_plain(Plain plain)
{
    glBegin(GL_TRIANGLES);
		glColor3d(plain.a->x, plain.b->y, plain.c->z);
		glVertex3d(plain.a->x, plain.a->y, plain.a->z);
        glVertex3d(plain.b->x, plain.b->y, plain.b->z);
        glVertex3d(plain.c->x, plain.c->y, plain.c->z);
    glEnd();
}

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
}