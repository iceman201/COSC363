#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//#define M_PI 3.141592653;

double drand48()
{	return (rand()%10000)/10000.0; }

//end of corrections
//#endif


#define MAX_POINTS 5000
int numPoints;
float curx, cury;
float x[MAX_POINTS], y[MAX_POINTS];
float xacc[MAX_POINTS], yacc[MAX_POINTS];
float red, green, blue;
int step; int length;

void initialize()
{ 
    int j;
    double temp, temp2;

    numPoints = drand48()*(MAX_POINTS-1);
    curx = -0.5 + drand48();
    cury = 0.0 + drand48();

    red = 0.5 + 0.5*drand48();
    green = 0.5 + 0.5*drand48();
    blue = 0.5 + 0.5*drand48();
    glPointSize(1.5); 
    step = 0;
    length = 700 + 300*drand48();


    /* initialize the blast */
    for (j=0 ; j<numPoints ; j++ ) {
        x[j] = curx;
        y[j] = cury;
        temp = drand48();
        temp2 = drand48()*2.0*M_PI;
        xacc[j] = (cos(temp2) * temp)/length;
        yacc[j] = (sin(temp2) * temp)/length;
    }

}

void draw_blast(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    double glow = (length - step) / (double)length;
    glColor3f(red*glow, green*glow, blue*glow);
    glBegin(GL_POINTS);
    for (i=0;i<numPoints;i++) {
        x[i] += xacc[i];
        y[i] += yacc[i];
        glVertex2f(x[i], y[i]);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    if (step < 0.9*length) {
        for (i=0; i<numPoints; i++){
        yacc[i] -= 0.02 / length; // gravity
        draw_blast();
        }
    }
    step ++;
    if (step > length){
        initialize();
    }
}

void idle(void)
{
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    if (w <= h){
        glOrtho(-1.0, 1.0, -1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w, -1.0, 1.0);
    }
    else{
        glOrtho(-1.0*(GLfloat)w/(GLfloat)h, 1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow ("Fireworks");

    glClearColor (0.0, 0.0, 0.0, 0.0);
    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0; 
}
