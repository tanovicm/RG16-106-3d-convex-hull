#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "point.h"
#include "vector.h"

// Once program is run, points are generated
int callOnce = 0;

double random_number()
{
	if(!callOnce) {
		srand(time(NULL));
		callOnce = 1;
	}
    
    return rand()/(double)RAND_MAX * 2 - 1;
}

Point* random_point()
{
    Point *point = malloc(sizeof(Point));
    if (point == NULL)
	exit(1);
    
    point->x = random_number();
    point->y = random_number();
    point->z = random_number();
    
    return point;
}

void draw_point(Point point)
{
	glPointSize(3);
    glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
        glVertex3d(point.x, point.y, point.z);
    glEnd();
}

double point_to_line_distance(Point point, Point lineA, Point lineB)
{
	double p = vector_length(cross(sub_vector(lineB, lineA), sub_vector(lineA, point)));
	double q = vector_length(sub_vector(lineB, lineA));

	double r = p/q;	
	return r;
}

/* Debugging function 
void print_point(Point *point)
{
	printf("(x=%lf, y=%lf, z=%lf)", point->x, point->y, point->z);
}
 */
