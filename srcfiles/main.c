/* VISUALSTUDIO branch (c) 2021 by dbj@dbj.org */

#include "chull.h"

// DBJ: added
static struct GLOB_STRUCT_ {
	// DBJ: we call glutDestroyMenu(CONTEXT_MENU_ID)
	// from menu handler so that menu can be called only once
	// this is to prevent repeated memory leaks
	// since the previous point and plain lists are not freed currently
	// they are simply left in the memory
	int CONTEXT_MENU_ID;
	// basically app logic (not GL stuff) starts not
	// before user selects something from the context menu
	// we use this to avoid drawing  from GL main loop 
	// before that is the case
	bool MENU_WAS_USED;
} GLOB = {
	.CONTEXT_MENU_ID = -1,
	.MENU_WAS_USED = false
};



enum {
	UP = 1,
	DOWN,
};

static int oldX = -13;
static int oldY = -13;

static int window;
static int menu_id;
static int submenu_id;

/* Time passed from the begining of a simulation */
static float animation_parameter = 0.0f;
static float x_parameter = 0.0f;
static float y_parameter = 0.0f;
static float z_parameter = 0.0f;

/* Flag determines timer state. */
static int animation_active = 0;

/* Callback functions declarations */
//static void on_keyboard(unsigned char key, int x, int y);
//static void on_reshape(int width, int height);
//static void on_timer(int value);
//static void mouseMove(int x, int y);
//void mouseButton(int button, int state, int x, int y);
//static void menu(int x);
//void on_display(void);
//void draw_convex_hull();

static float iwidth = 1000, iheight = 600;

// DBJ: in next iteration will have to free these
// when users selects new point set size
// and when app exits
// As far as I can see both plains and points do not
// own sublists, plains just reference them
// so these two list freeing should be straightforward
static Node* points = 0, * plains = 0;

static int mState = UP;

// angle of rotation for the camera direction
static /*float*/ double angleX = 0.0f;
static /*float*/ double angleY = 0.0f;

// actual vector representing the camera's direction
static float xlx = 0.0f, xlz = 0.0f;
static float yly = 0.0f, ylz = 0.0f;

// the key states. These variables will be zero
// when no key is being presses
static /*float*/ double deltaAngleX = 0.0f;
static /*float*/ double deltaAngleY = 0.0f;
static int xOrigin = -1;
static int yOrigin = -1;

/*----------------------------------------------------------------*/
static void draw_convex_hull(void)
{
	if (false == GLOB.MENU_WAS_USED) return; // DBJ added

	Node* p = points;
	for (; p != NULL; p = p->next) {
		Point* point = (Point*)p->elem;
		draw_point(*point);
	}

	p = plains;
	int i = 0;
	for (; p != NULL; p = p->next, i++) {
		if (i >= animation_parameter)
			break;
		draw_plain(*((Plain*)p->elem));
	}
}

// this is GLUT stuff 
static void on_display(void)
{

	GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1 };

	GLfloat material_diffuse[] = { 0.4, 0.4, 0.4, 1 };

	GLfloat material_specular[] = { 0.1, 0.1, 1, 1 };

	GLfloat low_shininess[] = { 5 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0, 1.0, 0.0);
	glScalef(.5, .5, .5);      /* modeling transformation */
	glRotatef(x_parameter + angleY + deltaAngleY, 1, 0, 0);
	glRotatef(y_parameter - angleX - deltaAngleX, 0, 1, 0);
	glRotatef(z_parameter, 0, 0, 1);
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

static void on_keyboard(unsigned char key, int x, int y)
{
	//DBJ: x and y are not used in here?
	(void)x;
	(void)y;

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
	glTranslatef(0, 0, -4);
	glMatrixMode(GL_MODELVIEW);
}

static void mouseMove(int x, int y)
{
	//	 this will only be true when the left button is down
	if (xOrigin >= 0) {
		// update deltaAngle
		// DBJ: using double
		deltaAngleX = (((double)x - (double)xOrigin) * 0.5/*f*/);

		// update camera's direction
		xlx = sin(angleX + deltaAngleX);
		xlz = -cos(angleX + deltaAngleX);
	}

	if (yOrigin >= 0) {
		// 		update deltaAngle
		// DBJ: using double
		deltaAngleY = ((double)y - (double)yOrigin) * 0.5/*f*/;

		//	 	update camera's direction
		yly = sin(angleY + deltaAngleY);
		ylz = -cos(angleY + deltaAngleY);
	}
}

static void mouseButton(int button, int state, int x, int y)
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
		}
		else {
			// 		state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

// DBJ: this is called AFTER user selects entry from the context menu
static void menu(int item)
{

	if (false == GLOB.MENU_WAS_USED) // flip only once
	{
		animation_parameter = 0.0;
		int number_of_points = item;
		int i;
		points = NULL;
		for (i = 0; i < number_of_points; i++) {
			Point* point = random_point();
			points = add_node(points, point);
		}
		plains = convex_hull(points);

		if (animation_active) {

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		if (!animation_active) {
			glutTimerFunc(10, on_timer, 0);
			animation_active = 1;
		}

		glutPostRedisplay();

		GLOB.MENU_WAS_USED = true; // DBJ added
		// remove the context menu
		//so it can be used only once
		assert(GLOB.CONTEXT_MENU_ID != -1);
		glutDestroyMenu(GLOB.CONTEXT_MENU_ID);
	}

	return;
}

// DBJ: simplest is to have main at the bottom of the main.c

int main(int argc, char** argv)
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
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	GLOB.CONTEXT_MENU_ID = glutCreateMenu(menu);

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
