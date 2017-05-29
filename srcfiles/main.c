#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "chull.h"

enum {
	UP = 1, 
	DOWN, 
};

int oldX = -13;
int oldY = -13;

static int window;
static int menu_id;
static int submenu_id;

/* Time passed from the begining of a simulation */
static float animation_parameter;
static float x_parameter;
static float y_parameter;
static float z_parameter;

/* Flag determines timer state. */
static int animation_active;

/* Callback functions declarations */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
static void menu (int x);

void on_display(void);
void draw_convex_hull();

float iwidth=1000, iheight=600;

Node *points, *plains;


int mState = UP;

// angle of rotation for the camera direction
float angleX = 0.0f;
float angleY = 0.0f;

// actual vector representing the camera's direction
float xlx=0.0f, xlz=0.0f;
float yly=0.0f, ylz=0.0f;

// the key states. These variables will be zero
// when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

// Menu handling function declaration
void menu(int);


int main(int argc, char **argv)
{
	
	GLfloat light_ambient[] = { 0.43, 0.4, 0.7, 1 };
	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	GLfloat light_specular[] = { 1, 1, 1, 1 };
	GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
	
    /* GLUT init */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Window created. */
    glutInitWindowSize(iwidth, iheight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    /* Events processing */
	glutKeyboardFunc(on_keyboard);
//        glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

// 	  Global vars declaration 
	animation_parameter = 0;
    animation_active = 0;
	x_parameter = 0;
	y_parameter = 0;
	z_parameter = 0;
	

    /* OpenGL init */
    glClearColor(0,0, 0, 1);
    glEnable(GL_DEPTH_TEST);
	
	glutCreateMenu(menu);
	
	// Add menu items
	glutAddMenuEntry("10 points", 10);
	glutAddMenuEntry("25 points", 25);
	glutAddMenuEntry("50 points", 50);
	glutAddMenuEntry("75 points", 75);
	glutAddMenuEntry("100 points", 100);
	glutAddMenuEntry("150 points", 150);
	glutAddMenuEntry("200 points", 200);
	
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	
	
     /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}
void on_display()
{
	
	GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1 };
	
	GLfloat material_diffuse[] = { 0.4, 0.4, 0.4, 1 };
	
	GLfloat material_specular[] = { 0.1, 0.1, 1, 1 };
	
	GLfloat low_shininess[] = { 5 };
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glLoadIdentity(); 
		gluLookAt (0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0, 1.0, 0.0);
		glScalef (.5, .5, .5);      /* modeling transformation */
		glRotatef(x_parameter +angleY+deltaAngleY,1,0,0);
		glRotatef(y_parameter-angleX-deltaAngleX,0,1,0);
		glRotatef(z_parameter,0,0,1);	
		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glNormal3f(0.0, 0.0, 1.0);
		draw_convex_hull();
	glPopMatrix();
	
    /* Rendering */
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* ESC exit */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Start. */
        if (!animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 1;
        }
        break;
	}
}

static void on_timer(int value)
{
    /* Callback from matching timer. */
    if (value != 0)
        return;

    /* Time of animation update */
    animation_parameter += 0.1;

    /* Rendering display again */
    glutPostRedisplay();

    /* Sets timer */
    if (animation_active)
        glutTimerFunc(10, on_timer, 0);
}

static void on_reshape(int width, int height)
{
	iwidth = width;
	iheight = height;
	
    /* Viewport set. */
    glViewport(0, 0, width, height);

    /* Projection parameters */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//     gluPerspective(60, (float) width / height, 0.000001,100);
		glTranslatef(0,0,-4);
	glMatrixMode (GL_MODELVIEW);
}

void draw_convex_hull()
{
    Node *p = points;
    for (; p != NULL; p = p->next) {
		Point *point = (Point *)p->elem;
        draw_point(*point);
	}
	
    p = plains;
    int i = 0;
    for (; p != NULL; p = p->next, i++){
         if (i >= animation_parameter)
            break;
        draw_plain(*((Plain *)p->elem));
    }
}

void mouseMove(int x, int y) 
{ 	
//	 this will only be true when the left button is down
	if (xOrigin >= 0) {
		// update deltaAngle
		deltaAngleX = (x - xOrigin) * 0.5f;
		
		// update camera's direction
		xlx = sin(angleX + deltaAngleX);
		xlz = -cos(angleX + deltaAngleX);
	}
	
	if (yOrigin >= 0) {
// 		update deltaAngle
		deltaAngleY = (y - yOrigin) * 0.5f;
		
//	 	update camera's direction
		yly = sin(angleY + deltaAngleY);
		ylz = -cos(angleY + deltaAngleY);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
//	only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		
//		 when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
			deltaAngleX = 0;
			deltaAngleY = 0;
			xOrigin = -1;
			yOrigin = -1;
		} else {
// 		state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}


void menu(int item)
{
	animation_parameter = 0.0;
	int number_of_points = item;
	int i;
	points = NULL;
	for (i = 0; i < number_of_points; i++){
		Point *point = random_point();
		points = add_node(points, point);
	}
	plains = convex_hull(points);
						
	if (animation_active){
		
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
	}
	
	if (!animation_active) {
		glutTimerFunc(10, on_timer, 0);
		animation_active = 1;
	}
			
    glutPostRedisplay();
			
	return;
}
