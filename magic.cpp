///***********************************************************
//*
//* Name: Nolan Willis
//*
//* Email: nwillis@syr.edu    
//*
//* Assignment: Assignment 4
//* 
//* Environment: Visual Studio Community 2022
//* 
//* Date submitted: 
//* 
//* References: None
//* 
//* Interactions: 
//   
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

//Camera position values
static float eyeX = 6, eyeY = 5, eyeZ = 2;
static float eyeAngle = 0;  //angle facing
static float stepSize = 5.0;  //step size
static float turnSize = 10.0; //degrees to turn

//Value to keep track of selecting state
bool isSelecting = false;

//Value to keep track of the last selected item
int itemID = 0;

//Mountain size and positioning
int mountainZ = -17;
int mountainScaleX = 4, mountainScaleY = 3;

//--------------------------------------------------------------------------------------

//Function that sets the view mode (ortho or frust)
void setViewMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 150);
    glMatrixMode(GL_MODELVIEW);
}


//Draws the ground 
void drawBridge()
{
    //Floor
    glColor3f(101.0 / 255.0, 102.0 / 255.0, 105.0 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(5, 1, 12);
    glutSolidCube(1);
    glPopMatrix();
    //Right railing
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(8.5, 1, -6);
    glScaled(.5, 2, 12);
    glutSolidCube(1);
    glPopMatrix();
    //Left railing
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(3.5, 1, -6);
    glScaled(.5, 2, 12);
    glutSolidCube(1);
    glPopMatrix();
}

void drawCourtyard() 
{
    //Floor
    glColor3f(101.0 / 255.0, 102.0 / 255.0, 105.0 / 255.0);
    glPushMatrix();
    glTranslated(6, 0, -22);
    glScaled(50, 1, 20);
    glutSolidCube(1);
    glPopMatrix();
    //Right front railing
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(19.5, 2.5, -12);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 5, 22.5);
    glutSolidCube(1);
    glPopMatrix();
    //Left front railing
    glPushMatrix();
    glTranslated(-7.5, 2.5, -12);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 5, 22.5);
    glutSolidCube(1);
    glPopMatrix();
    //Right middle railing
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(31, 2.5, -23);
    glScaled(.5, 5, 22.5);
    glutSolidCube(1);
    glPopMatrix();
    //Left middle railing
    glPushMatrix();
    glTranslated(-19, 2.5, -23);
    glScaled(.5, 5, 22.5);
    glutSolidCube(1);
    glPopMatrix();
    //Right back railing
    /*glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);*/
    glColor3f(255.0 / 255.0, 0, 0);
    glPushMatrix();
    glTranslated(23.5, 2.5, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 5, 15.5);
    glutSolidCube(1);
    glPopMatrix();
    //Left back railing
    glPushMatrix();
    glTranslated(-11.5, 2.5, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 5, 15.5);
    glutSolidCube(1);
    glPopMatrix();
}

void drawHall()
{
    //Right wall
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(22.5, 20, -62);
    glScaled(3, 40, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Left wall
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(-11.5, 20, -62);
    glScaled(3, 40, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Right roof
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(15, 61, -62);
    glRotated(20, 0, 0, 1);
    glScaled(3, 50, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Left roof
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(-4, 61, -62);
    glRotated(-20, 0, 0, 1);
    glScaled(3, 50, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Center beam for roof
    glColor3f(114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0);
    glPushMatrix();
    glTranslated(5.5, 85, -62);
    glRotated(45, 0, 0, 1);
    glScaled(3.2, 3.2, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Facade right
    glColor3f(255.0 / 255.0, 0, 0);
    glPushMatrix();
    glTranslated(21.5, 18, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 40, 19.5);
    glutSolidCube(1);
    glPopMatrix();
    //Facade left
    glPushMatrix();
    glTranslated(-9.5, 18, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 40, 19.5);
    glutSolidCube(1);
    glPopMatrix();

    //Floor
    glColor3f(116.0 / 255.0, 96.0 / 255.0, 72.0 / 255.0);
    glPushMatrix();
    glTranslated(5, 0, -62);
    glScaled(35, 1, 60);
    glutSolidCube(1);
    glPopMatrix();
}

void drawFurniture()
{
    //Table 1
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(-5, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 1
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(-5, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 1
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(-6.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 1
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(-6.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 1
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(-3.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 1
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(-3.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    

    //Table 2
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(2, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 2
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(2, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 2
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 2
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 2
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(3.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 2
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(3.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 3
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(10, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 3
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(10, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 3
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(8.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 3
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(8.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 3
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(11.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 3
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(11.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 4
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(17, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 4
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(17, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 4
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(15.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 4
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(15.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 4
    glColor3f(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    glPushMatrix();
    glTranslated(18.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 4
    glColor3f(4.0 / 255.0, 3.0 / 255.0, 1.0 / 255.0);
    glPushMatrix();
    glTranslated(18.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 5
    glColor3f(101.0 / 255.0, 102.0 / 255.0, 105.0 / 255.0);
    glPushMatrix();
    glTranslated(5.5, 5, -87);
    glRotated(90, 0, 1, 0);
    glScaled(3, .5, 20);
    glutSolidCube(1);
    glPopMatrix();
}


//Draws the mountain range
void drawMountains() 
{
    glColor3f(.2, .2, .2);
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

//Sets the camera viewing position
void setCameraView() 
{
   gluLookAt(eyeX, eyeY, eyeZ,
             eyeX + sin(eyeAngle * PI/180), eyeY, eyeZ + cos(eyeAngle * PI/180),
             0, 1, 0);
    
   
}

//Determines the ID of the object the mouse has clicked 
void getID(int x, int y) {
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        cout << "Helicopter selected" << endl;
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
    
    if (isSelecting)
    {
       
    }
    else
    {
       
    }

    drawBridge();
    drawCourtyard();
    drawHall();
    drawFurniture();
}

//Drawing routine 
void drawScene(void)
{
    //Draw everything with unique colors but don't display if user isSelecting
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
    glClearColor(181.0/255.0, 185.0/255.0, 188.0/255.0, -21.0);
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
    case 'w':
        eyeX += stepSize * sin(eyeAngle * PI / 180);
        eyeZ += stepSize * cos(eyeAngle * PI / 180);
        glutPostRedisplay();
        break;
    case 's':
        eyeX -= stepSize * sin(eyeAngle * PI / 180);
        eyeZ -= stepSize * cos(eyeAngle * PI / 180);
        glutPostRedisplay();
        break;
    case 'd':
        eyeAngle -= turnSize;
        glutPostRedisplay();
        break;
    case 'a':
        eyeAngle += turnSize;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;

    default:
        break;
    }
}

//Speical keyboard input processing
void specialkeyInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        
        break;
    case GLUT_KEY_RIGHT:
        
        
        break;
    case GLUT_KEY_LEFT:
       
        break;
    }
}

//Mouse input processing
void mouseInput(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT && state == GLUT_DOWN)
    {
        eyeY += 2;
        glutPostRedisplay();
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        eyeY -= 2;
        glutPostRedisplay();
    }
}

//Routine to output interaction instructions to the C++ window
void printInteraction(void)
{
    cout << "   Interaction" << endl;
    cout << "   Press esc to exit" << endl;
}

//Main routine
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1500, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Magic Castle");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialkeyInput);
    glutMouseFunc(mouseInput);
    printInteraction();
    glutMainLoop();

    return 0;
}