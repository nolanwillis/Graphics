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
//      Press n for the view from the north
//      Press e for the view from the east
//      Press s for the view from the south
//      Press w for the view from the west
//      Press o to toggle propeller power
//      Press f to authorize flight
//      Press r to reset the scene
//      Press esc to exit 
//*
//************************************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//Camera position
int eyePos = 2;

//Angle for helicopter blade animation
int mainRotorAngle = 0;
int tailRotorAngle = 0;

//Boolean value to determine if the helicopter is running;
int propPower = false;

//Boolean value that allows the helicopter to fly;
int fly = false;

//Coordinates of the helicopter;
//Location
float heliX = 0;
float heliY = 0;
float heliZ = 0;
//Yaw
int yaw = 0;


//Function that sets the view mode (ortho or frust)
void setViewMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);
    gluPerspective(90, 1, 1, 20);

    glMatrixMode(GL_MODELVIEW);
}


//Functions called in drawScene
//Draws helicopter landing pad
void drawHeliPad(void) {
    glColor3f(210.0 / 255.0, 209.0 / 255.0, 205 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(8, .25, 6);
    glutSolidCube(1);
    glPopMatrix();
}
//Draws the ground 
void drawGround(void) {
    glColor3f(186.0 / 255.0, 166.0 / 255.0, 132 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(100, .05, 100);
    glutSolidCube(1);
    glPopMatrix();
}
//Draws helicopter
void drawHeli(void) {
    //Fuselage
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslated(6 + heliX, 1 + heliY, -6.5 + heliZ);
    glScaled(1.2, .65, .75);
    glutSolidCube(1);
    glPopMatrix();
    glColor3f(.5, .5, .5);
    glPushMatrix();
    glTranslated(6.5 + heliX, 1 + heliY, -6.5 + heliZ);
    glScaled(.6, .6, .5);
    glutSolidCube(1);
    glPopMatrix();

    //Rotor blades
    glColor3f(.3, .3, .3);
    glPushMatrix();
    glTranslated(6 + heliX, 1.4 + heliY, -6.5 + heliZ);
    //Rotation for blade spin
    glRotated(0 + mainRotorAngle, 0, 1, 0);
    glScaled(3, .1, .15);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(6 + heliX, 1.5 + heliY, -6.5 + heliZ);
    //Rotation for blade spin
    glRotated(90 + mainRotorAngle, 0, 1, 0);
    glScaled(3, .1, .15);
    glutSolidCube(1);
    glPopMatrix();

    //Tail
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(5 + heliX, 1 + heliY, -6.5 + heliZ);
    glScaled(2, .2, .2);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(3.8 + heliX, 1.2 + heliY, -6.5 + heliZ);
    //Rotation for tail tip position
    glRotated(135, 0, 0, 1);
    glScaled(.75, .14, .2);
    glutSolidCube(1);
    glPopMatrix();

    //Tail rotor blades
    glColor3f(.3, .3, .3);
    glPushMatrix();
    glTranslated(4.1 + heliX, 1.05 + heliY, -6.35 + heliZ);
    //Rotation for blade spin
    glRotated(90 + tailRotorAngle, 0, 0, 1);
    glScaled(.70, .1, .05);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.1 + heliX, 1.05 + heliY, -6.35 + heliZ);
    //Rotation for blade spin
    glRotated(180 + tailRotorAngle, 0, 0, 1);
    glScaled(.70, .1, .05);
    glutSolidCube(1);
    glPopMatrix();
}

//Animation functions
//Function that increases blade rotation
void increaseBladeAngle() {
    if (mainRotorAngle < -360) {
        mainRotorAngle = 0;
    }
    if (tailRotorAngle < -360) {
        tailRotorAngle = 0;
    }
    mainRotorAngle -= 10;
    tailRotorAngle -= 10;
    glutPostRedisplay();
}
//Function that makes helicopter hover
void hover(int value) {
    if (heliY < 10 && propPower && fly) {
        heliY += .05;
    }
    else if (heliY > 0 && (!propPower || !fly)) {
        heliY -= .1;
    }
    
    glutPostRedisplay();
}

//Drawing routine.
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
    
    glutTimerFunc(20, hover, 1);

    if (propPower) {
        glutIdleFunc(increaseBladeAngle);
    }
    else {
        glutIdleFunc(NULL);
    }
    
    //Set View
    //View from the north
    if (eyePos == 0) {
        gluLookAt(6, 5, -15,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the east
    else if (eyePos == 1) {
        gluLookAt(15.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the south
    else if (eyePos == 2) {
        gluLookAt(6, 5, 2,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the west
    else if (eyePos == 3) {
        gluLookAt(-3.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }
    //View from above (not working)
    else if (eyePos == 4) {
        gluLookAt(6, 6, -6,
            6, 5, -6,
            0, -1, 0);
    }

    drawHeliPad();
    drawGround();

    glPushMatrix();
    glRotated(yaw, 0, 1, 0);
    drawHeli();
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
    case 'o':
        if (propPower) {
            propPower = false;
        }
        else {
            propPower = true;
        }
        glutPostRedisplay();
        break;
    case 'f':
        if (fly) {
            fly = false;
        }
        else {
            fly = true;
        }
        glutPostRedisplay();
        break;
    case 'r':
        fly = false;
        eyePos = 2;
        propPower = false;
        heliX = 0;
        heliY = 0;
        heliZ = 0;
        glutPostRedisplay;
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
    cout << "   Interaction" << endl;
    cout << "" << endl;
    cout << "   Camera position:" << endl;
    cout << "   Press n for the view from the north" << endl;
    cout << "   Press e for the view from the east" << endl;
    cout << "   Press s for the view from the south" << endl;
    cout << "   Press w for the view from the west" << endl;
    cout << "" << endl;
    cout << "   Helicopter controls:" << endl;
    cout << "   Press o to toggle propeller power" << endl;
    cout << "   Press f to authorize flight" << endl;
    cout << "" << endl;
    cout << "   General:" << endl;
    cout << "   Press r to reset the scene" << endl;
    cout << "   Press esc to exit" << endl;
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