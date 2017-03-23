#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

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

/* Vreme proteklo od pocetka simulacije. */
static float animation_parameter;
static float x_parameter;
static float y_parameter;
static float z_parameter;
/* Fleg koji odredjuje stanje tajmera. */
static int animation_active;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
static void menu (int x);

void on_display(void);
void draw_convex_hull();

float iwidth=300, iheight=300;

Node *points, *plains;


int mState = UP;

// angle of rotation for the camera direction
float angleX = 0.0f;
float angleY = 0.0f;

// actual vector representing the camera's direction
float xlx=0.0f, xlz=0.0f;
float yly=0.0f, ylz=0.0f;



// the key states. These variables will be zero
//when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;


// Menu handling function declaration
void menu(int);



int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(iwidth, iheight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
// 	
    /* Registruju se funkcije za obradu dogadjaja. */
	glutKeyboardFunc(on_keyboard);
//        glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	
//     /* Inicijalizuju se globalne promenljive. */
 
	   
    animation_parameter = 0;
    animation_active = 0;
	x_parameter = 0;
	y_parameter = 0;
	z_parameter = 0;
	

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.64, 0.500, 0.87, 0.01);
    glEnable(GL_DEPTH_TEST);

   
//     int number_of_points = 60;
//    
//     int i;
//     for (i = 0; i < number_of_points; i++){
//         Point *point = random_point();
//         points = add_node(points, point);
// 
//     }
// 
//     
// 	plains = convex_hull(points);
//	plains = initial_convex_hull(points);
   
// 	print_list(plains, print_plain);
	
	
	
	glutCreateMenu(menu);
	
	// Add menu items
	glutAddMenuEntry("100 tacaka", 100);
	glutAddMenuEntry("50 tacaka", 50);
	glutAddMenuEntry("200 tacaka", 200);
	glutAddMenuEntry("10 tacaka", 10);
	
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	
	
	
     /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}
void on_display()
{
// 	printf("on_display");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glPushMatrix();
		glLoadIdentity (); 
		// Set the camera
 		//gluLookAt(0.0f, 0.0f, 0.0f, -xlx, /*-yly*/0, xlz/* + ylz*/, 0.0f, 1.0f,  0.0f);
		
		gluLookAt (0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0, 1.0, 0.0);
		glScalef (.5, .5, .5);      /* modeling transformation */ 

		glRotatef(x_parameter +angleY+deltaAngleY,1,0,0);
		glRotatef(y_parameter-angleX-deltaAngleX,0,1,0);
		glRotatef(z_parameter,0,0,1);	
		draw_convex_hull();
	
		
	glPopMatrix();
	
	
    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Pokrece se simulacija. */
        if (!animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 1;
        }
        break;

    //case 's':
    //case 'S':
        /* Zaustavlja se simulacija. */
        //animation_active = 0;
        //break;
	case 'a':
	case 'A':
		x_parameter -= 1;
		break;
	case 'd':
	case 'D':
		x_parameter += 1;
		break;
	case 'w':
	case 'W':
		z_parameter -= 1;
		break;
	case 's':
	case 'S':
		z_parameter += 1;
		break;
	case 'q':
	case 'Q':
		y_parameter += 1;
		break;
	case 'e':
	case 'E':
		y_parameter -= 1;
		break;
	}
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    animation_parameter += 0.1;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_active)
        glutTimerFunc(10, on_timer, 0);
}

static void on_reshape(int width, int height)
{
	iwidth = width;
	iheight = height;
	
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//     gluPerspective(60, (float) width / height, 0.000001,100);

		glTranslatef(0,0,-4);
	glMatrixMode (GL_MODELVIEW);
	
	
	
}
void draw_convex_hull()
{
//  	printf("draw_convex_hull");
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

void mouseMove(int x, int y) { 	
	
	// this will only be true when the left button is down
	if (xOrigin >= 0) {
		
		// update deltaAngle
		deltaAngleX = (x - xOrigin) * 0.5f;
		
		// update camera's direction
		xlx = sin(angleX + deltaAngleX);
		xlz = -cos(angleX + deltaAngleX);
		
		printf("   %lf %lf\n", xlx, xlz);
	}

	if (yOrigin >= 0) {
	
		// update deltaAngle
		deltaAngleY = (y - yOrigin) * 0.5f;
		
		// update camera's direction
		yly = sin(angleY + deltaAngleY);
		ylz = -cos(angleY + deltaAngleY);
		
		printf("%lf %lf\n", yly, ylz);
	}
}

void mouseButton(int button, int state, int x, int y) {
	
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		
		// when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
			deltaAngleX = 0;
			deltaAngleY = 0;
			xOrigin = -1;
			yOrigin = -1;
		}
		else  {// state = GLUT_DOWN
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
		
		glClearColor(0.64, 0.500, 0.87, 0.01);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		

	}
	
	if (!animation_active) {
		glutTimerFunc(10, on_timer, 0);
		animation_active = 1;
	}
			
    glutPostRedisplay();
			
	return;
}






