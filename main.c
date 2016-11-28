#include <GL/glut.h>

/* Deklaracija callback funkcija */

static void on_display(void);

int main (int argc, char **argv)
{
    
    /* GLUT Initialization */
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    /* Window created */
    
    glutInitWindowSize(300,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    
    /* Callback functions */
    
    glutDisplayFunc(on_display);
    
    /* OpenGL Initialization */
    
    glClearColor(0.75,0.75,0.75,0);
    glEnable(GL_DEPTH_TEST);
    
    
    glutMainLoop();
    
    return 0;
    
}