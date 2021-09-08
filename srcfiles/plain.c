/* VISUALSTUDIO branch (c) 2021 by dbj@dbj.org */

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

	double angle = acos(dot(l1, l2)) + acos(dot(l2, l3)) + acos(dot(l3, l1));

	return abs(angle - 2 * M_PI) < 0.0001;
}

int contains_projection(Plain plain, Point point)
{
	Point projection = sub_vector(point, mul(normal(plain), distance(plain, point)));
	return is_point_in_triangle(plain, projection);
}

double distance(Plain plain, Point point)
{
	return dot(normal(plain), sub_vector(point, *plain.a));
}

Node* get_neighbors(Plain* plain)
{
	Node* neighbors = NULL;
	neighbors = add_node(neighbors, plain->ba);
	neighbors = add_node(neighbors, plain->ac);
	neighbors = add_node(neighbors, plain->cb);

	return neighbors;
}

Plain* make_plain(Point* a, Point* b, Point* c)
{
	Plain* plain = malloc(sizeof(Plain));

	assert(plain); // DEBUG builds only

	if (plain == NULL) {
		perror("plain not allocated");
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

Node* get_points(Plain* plain)
{
	Node* points = NULL;
	points = add_node(points, plain->a);
	points = add_node(points, plain->b);
	points = add_node(points, plain->c);

	if (points != NULL)
		return points;

	// DBJ added
	perror("point can not be null here?");
	exit(EXIT_FAILURE);
}

Point* find_farthest_point(Plain plain)
{
	double max = 0;
	Point* pmax = NULL;

	for (Node* temp = plain.points; temp != NULL; temp = temp->next) {
		Point* point = (Point*)temp->elem;
		double dist = distance(plain, *point);

		if (dist > max) {
			max = dist;
			pmax = point;
		}
	}

	return pmax;
}


void draw_plain(Plain plain)
{
	/*excluding white*/
	float newRange = 0.86;
	float lowest = 0.14;

	// DBJ: this is not used
	// GLfloat light_position[] = { 0,0,3, 1 };

	GLfloat no_material[] = { (plain.a->x * newRange) + lowest, (plain.b->y * newRange) + lowest, (plain.c->z * newRange) + lowest };

	/* Ambient reflection. */
	GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1 };

	/* Diffuse reflection. */
	GLfloat material_diffuse[] = { 0.2, 0.5, 0.8, 1 };

	/* Specular reflection */
	GLfloat material_specular[] = { 0.1, 0.1, 1, 1 };

	/* Coefficient of specular reflection in case of low value of coefficients.	*/
	GLfloat low_shininess[] = { 5 };


	glBegin(GL_TRIANGLES);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
	glNormal3f(plain.a->y * plain.c->z -
		plain.a->z * plain.c->y,
		plain.a->z * plain.c->x -
		plain.a->x * plain.c->z,
		plain.a->x * plain.c->y -
		plain.a->y * plain.c->x
	);
	glVertex3d(plain.a->x, plain.a->y, plain.a->z);

	glNormal3f(plain.b->y * plain.a->z -
		plain.b->z * plain.a->y,
		plain.b->z * plain.a->x -
		plain.b->x * plain.a->z,
		plain.b->x * plain.a->y -
		plain.b->y * plain.a->x
	);

	glVertex3d(plain.b->x, plain.b->y, plain.b->z);
	glNormal3f(plain.c->y * plain.b->z -
		plain.c->z * plain.b->y,
		plain.c->z * plain.b->x -
		plain.c->x * plain.b->z,
		plain.c->x * plain.b->y -
		plain.c->y * plain.b->x
	);
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
