///***********************************************************
//*
//* Name: Nolan Willis
//*
//* Email: nwillis@syr.edu    
//*
//* Assignment: Assignment 3
//* 
//* Environment: Visual Studio Community 2022
//* 
//* Date submitted: 
//* 
//* References: None
//* 
//* Interactions: 
//*     Press n for the view from the north
//*     Press e for the view from the east
//*     Press s for the view from the south
//*     Press w for the view from the west
//*
//************************************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

int eyePos = 0;

void setViewMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);
    gluPerspective(90, 1, 1, 20);

    glMatrixMode(GL_MODELVIEW);

}


// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Set view mode: ortho, frust, or persp
    setViewMode();
    //Clear modeview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);

    //Set View
    //View from the north
    if (eyePos == 0) {
        gluLookAt(6, 5, -15,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the east
    if (eyePos == 1) {
        gluLookAt(15.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the south
    if (eyePos == 2) {
        gluLookAt(6, 5, 2,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the west
    if (eyePos == 3) {
        gluLookAt(-3.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }

    //base - top is at y=0
    //Heli landing pad
    glColor3f(210.0/255.0, 209.0/255.0, 205/255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(8, .25, 6);
    glutSolidCube(1);
    glPopMatrix();

    //Fuselage
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslated(6, 1, -6.5);
    glScaled(1.2, .65, .75);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(.5, .5, .5);
    glPushMatrix();
    glTranslated(6.5, 1, -6.5);
    glScaled(.6, .6, .5);
    glutSolidCube(1);
    glPopMatrix();
    
    //Rotor blades
    glColor3f(.3, .3, .3);
    glPushMatrix();
    glTranslated(6, 1.5, -6.5);
    glRotated(0, 0, 1, 0);
    glScaled(3, .1, .15);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6, 1.6, -6.5);
    glRotated(90, 0, 1, 0);
    glScaled(3, .1, .15);
    glutSolidCube(1);
    glPopMatrix();

    //Tail
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(5, 1, -6.5);
    glScaled(2, .2, .2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.8, 1.2, -6.5);
    glRotated(135, 0, 0, 1);
    glScaled(.75, .14, .2);
    glutSolidCube(1);
    glPopMatrix();

    //Tail rotor blades
    glColor3f(.3, .3, .3);
    glPushMatrix();
    glTranslated(4.1, 1.05, -6.35);
    glRotated(90, 0, 0, 1);
    glScaled(.70, .1, .05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.1, 1.05, -6.35);
    glRotated(180, 0, 0, 1);
    glScaled(.70, .1, .05);
    glutSolidCube(1);
    glPopMatrix();

    //Ground
    glColor3f(186.0 / 255.0, 166.0 / 255.0, 132 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(100, .05, 100);
    glutSolidCube(1);
    glPopMatrix();

    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(135.0/255.0, 206.0/255.0, 235.0/255.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    setViewMode();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'n':
        eyePos = 0;
        glutPostRedisplay();
        break;
    case 'e':
        eyePos = 1;
        glutPostRedisplay();
        break;
    case 's':
        eyePos = 2;
        glutPostRedisplay();
        break;
    case 'w':
        eyePos = 3;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;

    default:
        break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "   Press n for the view from the north" << endl;
    cout << "   Press e for the view from the east" << endl;
    cout << "   Press s for the view from the south" << endl;
    cout << "   Press w for the view from the west" << endl;
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1500, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint Ballon Helicopter");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    printInteraction();
    glutMainLoop();

    return 0;
}