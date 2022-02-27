///***********************************************************
//*
//* Name: Nolan Willis
//*
//* Email: nwillis@syr.edu    
//*
//* Assignment: Assignment 2
//* 
//* Environment: Visual Studio Community 2022
//* 
//* Date submitted: February 26, 2022
//* 
//* References: None
//* 
//* Interactions: 
//      Press q to draw a comet
//      Press w to draw an alien ship
//      Press e to draw ursa major
//      Press r to draw a space station
//      Press a to draw a new moon
//      Press s to draw a crescent moon
//      Press d to draw a half moon
//      Press f to draw a gibbous moon
//      Press g to draw a full moon
//      Press right-click in the sky window for popup menu
//      Press Esc to quit
//*
//************************************************************/

#include <cmath>
  //sin, cos
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

using namespace std;


// Globals
// Window identifiers
int menuWindow;
int skyWindow;
// Check boxes pressed status
bool CB1Pressed = false;
bool CB2Pressed = false;
bool CB3Pressed = false;
bool CB4Pressed = false;
// Boolean value that determines background color 
bool isDusk = true;
// Radio button pressed status
int rbValue = 1;
// Z value for Ursa Major
int ursaMajorZ = -12;
// Z value for the background stars
int backgroundStarsZ = -18;
// Rotation angle for the moon
int moonRotAngle = 90;
// Rotation angle for the entire sky scene
int skyRot = 0;
// Scale value for the moon
int moonScale = 1;
// For writting text
void writeBitmapString(void* font, char* string)
{
    char* c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}




// Functions that draw menu objects
// Draws a circle
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
// Draws a square
void drawSquare(float X, float Y) 
{
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(20 + X, 30 + Y, -17);
    glVertex3f(20 + X, 20 + Y, -17);
    glVertex3f(30 + X, 20 + Y, -17);
    glVertex3f(30 + X, 30 + Y, -17);
    glEnd();
}
// Draws the red/pink menu background
void drawMenuBox() 
{
    glColor3f(219.0 / 255.0, 80.0 / 255.0, 74.0 / 255.0);
    glBegin(GL_POLYGON);
    glVertex3f(10, 165, -18);
    glVertex3f(10, 15, -18);
    glVertex3f(170, 15, -18);
    glVertex3f(170, 165, -18);
    glEnd();
}
// Draws the radio buttons
void drawRadioButtons() 
{
    // Radio button 1 (top most)
    if (rbValue == 1) 
    {
        glColor3f(.4, .4, .4);
        // New moon angle
        moonRotAngle = 90;
    }
    else 
    {
        glColor3f(1, 1, 1);
    }
    drawCircle(5.0, 105.0, 120.0);

    // Radio button 2
    if (rbValue == 2) 
    {
        glColor3f(.4, .4, .4);
        // Crescent moon angle
        moonRotAngle = 28;
    }
    else 
    {
        glColor3f(1, 1, 1);
    }
    drawCircle(5.0, 105.0, 100.0);

    // Radio button 3
    if (rbValue == 3) 
    {
        glColor3f(.4, .4, .4);
        // Half moon angle
        moonRotAngle = 0;
    }
    else 
    {
        glColor3f(1, 1, 1);
    }
    drawCircle(5.0, 105.0, 80.0);

    // Radio button 4
    if (rbValue == 4) 
    {
        glColor3f(.4, .4, .4);
        // Gibbous moon angle, changes base on moon size
        if (moonScale == 1) {
            moonRotAngle = -40;
        }
        else
        {
            moonRotAngle = -25;
        }
    }
    else 
    {
        glColor3f(1, 1, 1);
    }
    drawCircle(5.0, 105.0, 60.0);

    // Radio button 5
    if (rbValue == 5) 
    {
        glColor3f(.4, .4, .4);
        // Full moon angle
        moonRotAngle = -90;
    }
    else 
    {
        glColor3f(1, 1, 1);
    }
    drawCircle(5.0, 105.0, 40.0);
}
// Draws the checkboxes and x's
void drawCheckBoxes() 
{
    glColor3f(1, 1, 1);
    drawSquare(5, 95);
    drawSquare(5, 75);
    drawSquare(5, 55);
    drawSquare(5, 35);

    if (CB1Pressed) 
    {
        glColor3f(.4, .4, .4);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(25, 115, -17);
        glVertex3f(35, 125, -17);
        glVertex3f(25, 125, -17);
        glVertex3f(35, 115, -17);
        glEnd();
    }
    if (CB2Pressed) 
    {
        glColor3f(.4, .4, .4);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(25, 95, -17);
        glVertex3f(35, 105, -17);
        glVertex3f(25, 105, -17);
        glVertex3f(35, 95, -17);
        glEnd();
    }
    if (CB3Pressed) 
    {
        glColor3f(.4, .4, .4);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(25, 75, -17);
        glVertex3f(35, 85, -17);
        glVertex3f(25, 85, -17);
        glVertex3f(35, 75, -17);
        glEnd();
    }
    if (CB4Pressed) 
    {
        glColor3f(.4, .4, .4);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(25, 55, -17);
        glVertex3f(35, 65, -17);
        glVertex3f(25, 65, -17);
        glVertex3f(35, 55, -17);
        glEnd();
    }
}
// Draws all the text in the menu
void drawText() 
{
    // Stellar objects title
    glColor3f(1, 1, 1);
    glRasterPos3f(25, 135, -17);
    char stellarObjects[] = "Stellar Objects";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, stellarObjects);
    glColor3f(.1, .1, .1);

    // Shooting star text
    glRasterPos3f(40, 118, -17);
    char comet[] = "Comet";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, comet);
    // Alien ship text
    glRasterPos3f(40, 98, -17);
    char alienShip[] = "Alien Ship";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, alienShip);
    // Ursa major text
    glRasterPos3f(40, 78, -17);
    char ursaMajor[] = "Ursa Major";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, ursaMajor);
    // Space station text
    glRasterPos3f(40, 58, -17);
    char spaceStation[] = "Space Station";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, spaceStation);

    // Moon phase title
    glColor3f(1, 1, 1);
    glRasterPos3f(100, 135, -17);
    char moonPhase[] = "Moon Phase";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, moonPhase);
    glColor3f(.1, .1, .1);

    // New moon phase text
    glRasterPos3f(115, 118, -17);
    char newMoon[] = "New";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, newMoon);
    // Crescent moon phase text
    glRasterPos3f(115, 98, -17);
    char crescentMoon[] = "Crescent";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, crescentMoon);
    // Half moon phase text
    glRasterPos3f(115, 78, -17);
    char halfMoon[] = "Half";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, halfMoon);
    // Gibbous moon phase text
    glRasterPos3f(115, 58, -17);
    char gibbousMoon[] = "Gibbous";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, gibbousMoon);
    // Full moon phase text
    glRasterPos3f(115, 38, -17);
    char fullMoon[] = "Full";
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, fullMoon);
}
// End of functions that draw menu objects




// Start of functions that draw sky objects
void drawUrsaMajor()
{
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3);
    glPushMatrix();
    glBegin(GL_POINTS);
    glVertex3f(1.0, 20.0, ursaMajorZ);
    glVertex3f(5.0, 19.0, ursaMajorZ);
    glVertex3f(7.0, 16.0, ursaMajorZ);
    glVertex3f(11.0, 14.0, ursaMajorZ);
    glVertex3f(10.5, 9.0, ursaMajorZ);
    glVertex3f(18.0, 7.0, ursaMajorZ);
    glVertex3f(20.0, 12.0, ursaMajorZ);
    glVertex3f(11.0, 14.0, ursaMajorZ);
    glPopMatrix();
    glEnd();
}
// Draws the stars in the background
void drawBackgroundStars()
{
    glColor3f(1, 1, 1);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; i++) {
       int x = ((rand() % 100 + 1)*1.023443)  - ((rand() % 100 + 1) * 1.004392);
       int y = ((rand() % 100 + 1)*1.059422) - ((rand() % 100 + 1) * 1.065302);
       glVertex3f(x, y, backgroundStarsZ);
    }
    glEnd();
}
// Draws the comet
void drawComet()
{
    // Blue-purple sphere
    glPushMatrix();
    glTranslatef(-20, 20, -15.1);
    glColor3f(107.0 / 255.0, 63.0 / 255.0, 160.0 / 255.0);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    // Purple cylinder
    glPushMatrix();
    glTranslatef(-20, 20, -15);
    glRotated(1, 0, 1, 0);
    glColor3f(156.0 / 255.0, 0, 74.0 / 255.0);
    glutWireCone(1, 5, 50, 50);
    glPopMatrix();

    // Blue-purple cylinder
    glPushMatrix();
    glTranslatef(-20, 20, -15);
    glRotated(-1, 0, 1, 0);
    glColor3f(107.0 / 255.0, 63.0 / 255.0, 160.0 / 255.0);
    glutWireCone(1, 5, 50, 50);
    glPopMatrix();
}
// Draws the space station
void drawSpaceStation()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();
    glTranslatef(-25, -25, -15);
    glColor3f(1, 1, 1);
    glutWireSphere(2, 25, 25);

    glColor3f(.8, .8, .8);
    glutWireTorus(.5, 6, 25, 25);
    
    glLineWidth(7);

    glBegin(GL_LINE_LOOP);
    glVertex3f(-2, 0, -1);
    glVertex3f(-2, 5, -1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-2, -4, -1);
    glVertex3f(-2, -8, -1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-4, -2, -1);
    glVertex3f(-8, -2, -1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, -2.3, -1);
    glVertex3f(4, -2.3, -1);
    glEnd();

    glPopMatrix();
}
// Draws the alien ship
void drawAlienShip()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
    glColor3f(.5, 0, 0);
    glTranslatef(25, -25, -15);
    glutSolidCube(3);
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();
    glColor3f(0, .8, 0);
    glTranslatef(25, -22, -15);
    glutWireSphere(3, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22, -25, -15);
    glutWireSphere(2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28, -25, -15);
    glutWireSphere(2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, -27, -15);
    glutWireSphere(2, 50, 50);
    glPopMatrix();
}
// Draws the moon
void drawMoon()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
    glTranslated(0, 0, -15);
    glScalef(moonScale, moonScale, moonScale);

    glPushMatrix();
    glRotated(moonRotAngle, 0, 1, 0);

    double LightCPEq[4] = { 1, 0, 0, 0 };
    glClipPlane(GL_CLIP_PLANE0, LightCPEq);
    glEnable(GL_CLIP_PLANE0);
    glColor3f(1, 1, 1);
    glutSolidSphere(5, 25, 25);
    glDisable(GL_CLIP_PLANE0);

    double DarkCPEq[4] = { -1, 0, 0, 0 };
    glClipPlane(GL_CLIP_PLANE0, DarkCPEq);
    glEnable(GL_CLIP_PLANE0);
    if (isDusk) {
        glColor3f(7.0 / 255, 15.0 / 255, 32.0 / 255.0);
    }
    else {
        glColor3f(250.0 / 255.0, 123.0 / 255.0, 98.0 / 255.0);
    }
    glutSolidSphere(5, 25, 25);
    glDisable(GL_CLIP_PLANE0);


    glPopMatrix();

    glPopMatrix();
}
// End of functions that draw sky objects




// Functions involved in user input
// Keyboard input processing
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'q':
        if (CB1Pressed)
        {
            CB1Pressed = false;
        }
        else
        {
            CB1Pressed = true;
        }
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'w':
        if (CB2Pressed)
        {
            CB2Pressed = false;
        }
        else
        {
            CB2Pressed = true;
        }
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'e':
        if (CB3Pressed)
        {
            CB3Pressed = false;
        }
        else
        {
            CB3Pressed = true;
        }
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'r':
        if (CB4Pressed)
        {
            CB4Pressed = false;
        }
        else
        {
            CB4Pressed = true;
        }
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'a':
        rbValue = 1;
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 's':
        rbValue = 2;
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'd':
        rbValue = 3;
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'f':
        rbValue = 4;
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    case 'g':
        rbValue = 5;
        glutSetWindow(menuWindow);
        glutPostRedisplay();
        glutSetWindow(skyWindow);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
// Mouse input processing
void mouseControlMenu(int button, int state, int x, int y)
{
    int mouseX, mouseY;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseX = x / 5;
        mouseY = (500 - y) / 5;

        // Checkboxes
        // postRedisplay is called during each button if-statement to prevent
        // a redisplay if the user clicks outside the check-boxes/radio buttons.
        // This prevents random stars being re-generated if a user clicks the menu and
        // not a button.
        if (mouseX >= 15 && mouseX <= 20 && mouseY >= 68 && mouseY <= 73)
        {
            if (CB1Pressed)
            {
                CB1Pressed = false;
            }
            else
            {
                CB1Pressed = true;
            }
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 15 && mouseX <= 20 && mouseY >= 55 && mouseY <= 62)
        {
            if (CB2Pressed)
            {
                CB2Pressed = false;
            }
            else
            {
                CB2Pressed = true;
            }
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 15 && mouseX <= 20 && mouseY >= 44 && mouseY <= 50)
        {
            if (CB3Pressed)
            {
                CB3Pressed = false;
            }
            else
            {
                CB3Pressed = true;
            }
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 15 && mouseX <= 20 && mouseY >= 33 && mouseY <= 38)
        {
            if (CB4Pressed)
            {
                CB4Pressed = false;
            }
            else
            {
                CB4Pressed = true;
            }
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }

        // Radio buttons
        if (mouseX >= 58 && mouseX <= 64 && mouseY >= 68 && mouseY <= 73)
        {
            rbValue = 1;
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 58 && mouseX <= 64 && mouseY >= 55 && mouseY <= 62)
        {
            rbValue = 2;
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 58 && mouseX <= 64 && mouseY >= 44 && mouseY <= 50)
        {
            rbValue = 3;
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 58 && mouseX <= 64 && mouseY >= 33 && mouseY <= 38)
        {
            rbValue = 4;
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
        if (mouseX >= 58 && mouseX <= 64 && mouseY >= 21 && mouseY <= 26)
        {
            rbValue = 5;
            glutSetWindow(menuWindow);
            glutPostRedisplay();
            glutSetWindow(skyWindow);
            glutPostRedisplay();
        }
    }
}
// Popup menu for the Sky window
// Controller for the front menu
void frontMenu(int value)
{
    if (skyRot == 0) {
        skyRot = 30;
    }
    else
    {
        skyRot = 0;
    }
    glutPostRedisplay();
}
// Controller for time menu (dawn/dusk)
void timeMenu(int value)
{
    if (value == 1) {
        glClearColor(250.0 / 255.0, 123.0 / 255.0, 98.0 / 255.0, -20.0);
        isDusk = false;
    }
    if (value == 2) {
        glClearColor(7.0 / 255, 15.0 / 255, 32.0 / 255.0, -20.0);
        isDusk = true;
    }
    glutPostRedisplay();
}
// Controller for moon menu (small/medium/large moon size)
void moonMenu(int value)
{
    if (value == 1) {
        moonScale = 1;
    }
    if (value == 2) {
        moonScale = 2;
    }
    glutPostRedisplay();
}
// Draws the entire menu
void drawPopupMenu(void)
{
    int timeSubMenu;
    timeSubMenu = glutCreateMenu(timeMenu);
    glutAddMenuEntry("Dawn", 1);
    glutAddMenuEntry("Dusk", 2);

    int moonSubMenu;
    moonSubMenu = glutCreateMenu(moonMenu);
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Large", 2);

    glutCreateMenu(frontMenu);
    glutAddSubMenu("Time", timeSubMenu);
    glutAddSubMenu("Moon Size", moonSubMenu);
    glutAddMenuEntry("Skew sky toggle", 1);
    

    // The menu is triggered by the right mouse button.
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// Prints input instructions to the console
void printInstructions()
{
    cout << "\nPress q to draw a comet" << endl;
    cout << "\nPress w to draw an alien ship" << endl;
    cout << "\nPress e to draw ursa major" << endl;
    cout << "\nPress r to draw a space station" << endl;
    cout << "\n" << endl;
    cout << "\nPress a to draw a new moon" << endl;
    cout << "\nPress s to draw a crescent moon" << endl;
    cout << "\nPress d to draw a half moon" << endl;
    cout << "\nPress f to draw a gibbous moon" << endl;
    cout << "\nPress g to draw a full moon" << endl;
    cout << "\n" << endl;
    cout << "\nRight click in the sky window for more options" << endl;
    cout << "\nPress Esc exit" << endl;
}




// Draw scene functions for Menu and Sky
void  drawMenuScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glFrustum(0.0, 10.0, 0.0, 10.0, 1.0, 20.0);

    drawMenuBox();
    drawRadioButtons();
    drawCheckBoxes();
    drawText();

    glutSwapBuffers(); //instead of glFlush, double buffer
}
void drawSkyScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glFrustum(-2.5, 2.5, -2.5, 2.5, 1.0, 20.0);

    glPushMatrix();
    // Entire sky rotation
    glRotated(skyRot, 0, 0, 1);
    drawBackgroundStars();
    if (CB1Pressed) drawComet();
    if (CB2Pressed) drawAlienShip();
    if (CB3Pressed) drawUrsaMajor();
    if (CB4Pressed) drawSpaceStation();
    drawMoon();
    glPopMatrix();

    glutSwapBuffers(); //instead of glFlush, double buffer
}


// Setup and resize functions for both draw scene functions
void setupMenuWindow(void)
{
    glClearColor(8.0 / 255.0, 76.0 / 255.0, 97.0 / 255.0, -20.0);
}
void setupSkyWindow(void)
{
    if (isDusk) {
        glClearColor(7.0 / 255, 15.0 / 255, 32.0 / 255.0, -20.0);
    }
    else {
        glClearColor(250.0 / 255.0, 123.0 / 255.0, 98.0 / 255.0, -20.0);
    }
}


// Window reshape functions for both draw scene functions
void resizeMenu(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0.0, 10.0, 0.0, 10.0, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
void resizeSky(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2.5, 2.5, -2.5, 2.5, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}




// Main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    printInstructions();

    // Menu window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    menuWindow = glutCreateWindow("Menu");
    setupMenuWindow();
    glutDisplayFunc(drawMenuScene);
    glutMouseFunc(mouseControlMenu);
    glutReshapeFunc(resizeMenu);

    // Sky window
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    skyWindow = glutCreateWindow("Sky");
    setupSkyWindow();
    drawPopupMenu();
    glutDisplayFunc(drawSkyScene);
    glutReshapeFunc(resizeSky);
 
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}
