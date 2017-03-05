#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "chull.h"

/* Vreme proteklo od pocetka simulacije. */
static float animation_parameter;

/* Fleg koji odredjuje stanje tajmera. */
static int animation_active;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
void on_display(void);
void draw_convex_hull();


Node *points, *plains;

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
	glutKeyboardFunc(on_keyboard);
//        glutReshapeFunc(on_reshape);
	   glutDisplayFunc(on_display);
// 
//     /* Inicijalizuju se globalne promenljive. */
//     animation_parameter = 0;
//     animation_active = 0;

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0.75);
    glEnable(GL_DEPTH_TEST);

   
    int number_of_points = 6;
   
    int i;
    for (i = 0; i < number_of_points; i++){
        Point *point = random_point();
        points = add_node(points, point);

    }

    
	plains = convex_hull(points);
   
	print_list(plains, print_plain);
	
     /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}
void on_display()
{
	printf("on_display");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_convex_hull();
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

//     case 'g':
//     case 'G':
//         /* Pokrece se simulacija. */
//         if (!animation_active) {
//             glutTimerFunc(10, on_timer, 0);
//             animation_active = 1;
//         }
//         break;

    case 's':
    case 'S':
        /* Zaustavlja se simulacija. */
        animation_active = 0;
        break;
    }
}

// static void on_timer(int value)
// {
//     /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
//     if (value != 0)
//         return;
// 
//     /* Azurira se vreme simulacije. */
//     animation_parameter++;
// 
//     /* Forsira se ponovno iscrtavanje prozora. */
//     glutPostRedisplay();
// 
//     /* Po potrebi se ponovo postavlja tajmer. */
//     if (animation_active)
//         glutTimerFunc(10, on_timer, 0);
// }

// static void on_reshape(int width, int height)
// {
//     /* Postavlja se viewport. */
//     glViewport(0, 0, width, height);
// 
//     /* Postavljaju se parametri projekcije. */
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(60, (float) width / height, 1, 1500);
// }
void draw_convex_hull()
{
 	printf("draw_convex_hull");
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