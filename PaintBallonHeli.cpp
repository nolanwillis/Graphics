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

#define PI 3.14159

using namespace std;

//Global Variables------------------------------------------------------------------------

//Window size
int height, width;

//Mouse click coordinates
int mouseX, mouseY;

//Camera position
int eyePos = 2;

//Angle for helicopter blade animation
int mainRotorAngle = 0, tailRotorAngle = 0;

//Boolean value to determine if the helicopter is running;
int propPower = false;

//Boolean value that allows the helicopter to fly;
int fly = false;

//Coordinates of the helicopter
float heliX = 0, heliY = 0, heliZ = 0;

//Value of the current leg of the flight path
int pathLeg = 1;

//Fuseladge id for selection
int FUSELADGE = 1;

//Value to keep track of selecting state
bool isSelecting = false;

//Value to keep track of the last selected item
int itemID = 0;

//Ballon color values
float balloonR = .63, balloonG = .13, balloonB = .94;

//Ballon Y coordinate modifier value
float balloonY = 0;

//Mountain color values 
float mtnR = .23, mtnG = .34, mtnB = .37;

//House roof color values
float roofR = .4, roofG = .4, roofB = .4;

//Tree canopy color values
float canR = .2, canG = 1.0, canB = .2;

//Value to keep track if the balloon is dropped
bool isDropped = false;

//Mountain size and positioning
int mountainZ = -17;
int mountainScaleX = 4, mountainScaleY = 3;

//Values to keep track if objects are hit
bool houseHit = false, mtnHit = false, treeHit = false;

//----------------------------------------------------------------------------------------

//Function that sets the view mode (ortho or frust)
void setViewMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);
    gluPerspective(90, 1, 1, 20);

    glMatrixMode(GL_MODELVIEW);
}

void drawCircle(float R, float X, float Y) 
{
    glLineWidth(1);
    int numVerts = 1000;
    float Z = -17;
    float t = 0;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVerts; i++)
    {
        glVertex3f(X + R * cos(t), Y + R * sin(t), Z);
        t += 2 * PI / numVerts;
    }
    glEnd();
}

//Draws helicopter landing pad
void drawHeliPad() 
{
    glColor3f(210.0 / 255.0, 209.0 / 255.0, 205 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(8, .25, 6);
    glutSolidCube(1);
    glPopMatrix();
}

//Draws the ground 
void drawGround() 
{
    glColor3f(108.0 / 255.0, 165.0 / 255.0, 128.0 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(100, .05, 100);
    glutSolidCube(1);
    glPopMatrix();
}

//Draws helicopter
void drawHeli(float fuselageR, float fuselageG, float fuselageB) 
{
    //Fuselage
    glColor3f(fuselageR, fuselageG, fuselageB);
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

    //Balloon
    glPushMatrix();
    glColor3f(balloonR, balloonG, balloonB);
    glTranslated(6 + heliX, .5 + heliY + balloonY, -6.5 + heliZ);
    glutSolidSphere(.5, 25, 25);
    glPopMatrix();
}

//Draws the house
void drawHouse() 
{
    //Base
    glColor3f(0, .5, 1);
    glPushMatrix();
    glTranslated(15, 0, -14);
    glScaled(2, 3.3, 1);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0, .5, 1);
    glPushMatrix();
    glTranslated(15, 1.8, -14);
    glScaled(1.3, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //Roof
    if (houseHit)
    {
        glColor3f(balloonR, balloonG, balloonB);
    }
    else 
    {
        glColor3f(roofR, roofG, roofB);
    }
    glPushMatrix();
    glTranslated(14.4, 2.2, -14);
    glRotated(45, 0, 0, 1);
    glScaled(2, .5, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(15.5, 2.2, -14);
    glRotated(-45, 0, 0, 1);
    glScaled(2, .5, 1.5);
    glutSolidCube(1);
    glPopMatrix();
}

//Draws the tree
void drawTree() 
{
    //Trunk
    glColor3f(.4, .3, .3);
    glPushMatrix();
    glTranslated(0, .5, -6.5);
    glRotated(90, 0, 0, 1);
    glScaled(5, .2, .2);
    glutSolidCube(1);
    glPopMatrix();

    //Branches
    //Branch facing north
    glColor3f(.4, .3, .3);
    glPushMatrix();
    glTranslated(0, 2.5, -6.8);
    glRotated(90, 0, 1, 0);
    glRotated(70, 0, 0, 1);
    glScaled(1.5, .1, .1);
    glutSolidCube(1);
    glPopMatrix();
    //Branch facing east
    glColor3f(.4, .3, .3);
    glPushMatrix();
    glTranslated(.3, 2.5, -6.5);
    glRotated(65, 0, 0, 1);
    glScaled(1.8, .1, .1);
    glutSolidCube(1);
    glPopMatrix();
    //Branch facing south
    glColor3f(.4, .3, .3);
    glPushMatrix();
    glTranslated(0, 2.5, -6.2);
    glRotated(-90, 0, 1, 0);
    glRotated(70, 0, 0, 1);
    glScaled(1.5, .1, .1);
    glutSolidCube(1);
    glPopMatrix();
    //Branch facing west
    glColor3f(.4, .3, .3);
    glPushMatrix();
    glTranslated(-.3, 2.5, -6.5);
    glRotated(-65, 0, 0, 1);
    glScaled(1.8, .1, .1);
    glutSolidCube(1);
    glPopMatrix();

    //Canopy
    if (houseHit)
    {
        glColor3f(balloonR, balloonG, balloonB);
    }
    else
    {
        glColor3f(canR, canG, canB);
    }
    glPushMatrix();
    glTranslated(0, 4, -6.5);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
}

//Draws the mountain range
void drawMountains() 
{
    if (mtnHit) 
    {
        glColor3f(balloonR, balloonG, balloonB);
    }
    else
    {
        glColor3f(mtnR, mtnG, mtnB);
    }
    
    glPushMatrix();
    glTranslated(-10.0, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0 * mountainScaleX, 1.0 * mountainScaleY, mountainZ);
    glVertex3f(-1.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(0.0 * mountainScaleX, 2.0 * mountainScaleY, mountainZ);
    glVertex3f(0.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(1.0 * mountainScaleX, 3.0 * mountainScaleY, mountainZ);
    glVertex3f(1.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(2.0 * mountainScaleX, 3.0 * mountainScaleY, mountainZ);
    glVertex3f(2.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(3.0 * mountainScaleX, 4.0 * mountainScaleY, mountainZ);
    glVertex3f(3.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(4.0 * mountainScaleX, 3.0 * mountainScaleY, mountainZ);
    glVertex3f(4.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(5.0 * mountainScaleX, 2.0 * mountainScaleY, mountainZ);
    glVertex3f(5.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(6.0 * mountainScaleX, 4.0 * mountainScaleY, mountainZ);
    glVertex3f(6.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(7.0 * mountainScaleX, 2.0 * mountainScaleY, mountainZ);
    glVertex3f(7.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(8.0 * mountainScaleX, 5.0 * mountainScaleY, mountainZ);
    glVertex3f(8.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glVertex3f(9.0 * mountainScaleX, 3.0 * mountainScaleY, mountainZ);
    glVertex3f(9.0 * mountainScaleX, 0.0 * mountainScaleY, mountainZ);
    glEnd();
    glPopMatrix();
}

//Increases the angle of the rotor blades (main and tail rotor)
void increaseBladeAngle() 
{
    if (mainRotorAngle < -360) 
    {
        mainRotorAngle = 0;
    }
    if (tailRotorAngle < -360) 
    {
        tailRotorAngle = 0;
    }
    mainRotorAngle -= 10;
    tailRotorAngle -= 10;
    glutPostRedisplay();
}

//Animates the movement of the entire helicopter
void animateHeliMovement(int num) 
{
    //Allows the helicopter climb/fall independently
    if (propPower && fly && heliY < 10) 
    {
        heliY += .05;
    }
    if ((!propPower || !fly) && heliY > 0) 
    {
        heliY -= .1;
    }
    //Controls the flight path
    if (propPower && fly) 
    {
        if (pathLeg == 0) 
        {
            if (heliX < 0) 
            {
                heliX += .05;
            }
            else
            {
                pathLeg = 1;
            }
        }
        if (pathLeg == 1) 
        {
            if (heliX < 15) 
            {
                heliX += .05;
            }
            if (heliZ > -7.5) 
            {
                heliZ -= .04;
            }
            else 
            {
                pathLeg = 2;
            }
        }
        if (pathLeg == 2) 
        {
            if (heliX > 4) 
            {
                heliX -= .04;
            }
            if (heliZ > -11) 
            {
                heliZ -= .04;
            }
            else 
            {
                pathLeg = 3;
            }
        }
        if (pathLeg == 3) 
        {
            if (heliX > -7) 
            {
                heliX -= .04;
            }
            if (heliZ < 0) 
            {
                heliZ += .04;
            }
            else
            {
                pathLeg = 0;
            }
        }
    }
    glutPostRedisplay();
}

//Animates the helicopter blades
void animateHeliBlades() 
{
    if (propPower) 
    {
        glutIdleFunc(increaseBladeAngle);
    }
    else 
    {
        glutIdleFunc(NULL);
    }
    glutPostRedisplay();
}

//Animates the balloon falling
void animateBalloon(int value)
{
    if (balloonY > -20) {
        balloonY -= .4;
    }
    glutPostRedisplay();
}

//Sets the camera viewing position
void setCameraView() 
{
    //View from the north
    if (eyePos == 0) 
    {
        gluLookAt(6, 5, -15,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the east
    else if (eyePos == 1) 
    {
        gluLookAt(15.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the south
    else if (eyePos == 2) 
    {
        gluLookAt(6, 5, 2,
            6, 5, -6,
            0, 1, 0);
    }
    //View from the west
    else if (eyePos == 3) 
    {
        gluLookAt(-3.5, 5, -6,
            6, 5, -6,
            0, 1, 0);
    }
    //View from above (not working)
    else if (eyePos == 4) 
    {
        gluLookAt(6, 6, -6,
            6, 5, -6,
            0, -1, 0);
    }
}

//Determines if the mouse has clicked an object 
void getID(int x, int y) {
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        itemID = FUSELADGE;
    }
    else
    {
        itemID = 0;
    }
    isSelecting = false;
    glutPostRedisplay();
}

//Draws the objects in the scene
void drawObjects(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //Set camera view
    setCameraView();

    //Draw objects
    drawHeliPad();
    drawGround();
    drawHouse();
    drawTree();
    drawMountains();
    if (isSelecting)
    {
        drawHeli(0.0, 1.0, 0.0);
    }
    else
    {
        drawHeli(1.0, 0.0, 0.0);
    }
   
    //Selection control (if a certain itemID is selected do something)
    if (itemID == FUSELADGE)
    {
        glutTimerFunc(1, animateBalloon, 1);
    }
    
    //Animation function calls
    animateHeliBlades();
    glutTimerFunc(5, animateHeliMovement, 1);

}

//Drawing routine 
void drawScene(void)
{
    //Draw everything with unique colors but don't display if user isSelecting
     //glTranslated(6 + heliX, 1 + heliY, -6.5 + heliZ);
    
    if (isSelecting)
    {
        drawObjects();
        getID(mouseX, mouseY);
    }
    //Draw everything normally
    else
    {
        drawObjects();
        glutSwapBuffers();
    }
}

// Initialization routine
void setup(void)
{
    glClearColor(135.0/255.0, 206.0/255.0, 235.0/255.0, -21.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setViewMode();
    glMatrixMode(GL_MODELVIEW);
    height = h;
    width = w;
}

//Keyboard input processing
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

//Mouse input processing
void mouseInput(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT && state == GLUT_DOWN)
    {
        isSelecting = true;
        mouseX = x;
        mouseY = height - y;
        glutPostRedisplay();
    }
}

//Routine to output interaction instructions to the C++ window
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

//Main routine
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
    glutMouseFunc(mouseInput);
    printInteraction();
    glutMainLoop();

    return 0;
}