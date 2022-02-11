///////////////////////////////////////////////////////////////////////////////////////          
// simplePerson.cpp
// Author:  Baruch
//
// This program draws a person.
//
// 
/////////////////////////////////////////////////////////////////////////////////////// 

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

// Globals.
static float r = 1.0; // Radius of head.
static int nv = 10;  //Number of vertices for head.
static float cx = 20.0, cy = 15.0, cz = -1.0;  //Center of head.
static float bodylength = 4.0;
bool isOrtho = true;
float mountainz = -18.0; 
float starz = -19.0;
float snowpeakz = -17.0;
static float mountainVerts[] =
{
    0.0, 30.0, mountainz,
    0.0, 0.0, mountainz,
    10.0, 40.0, mountainz,
    10.0, 0.0, mountainz,
    20.0, 50.0, mountainz,
    20.0, 0.0, mountainz,
    30.0, 50.0, mountainz,
    30.0, 0.0, mountainz,
    40.0, 60.0, mountainz,
    40.0, 0.0, mountainz,
    50.0, 50.0, mountainz,
    50.0, 0.0, mountainz,
    60.0, 40.0, mountainz,
    60.0, 0.0, mountainz,
    70.0, 60.0, mountainz,
    70.0, 0.0, mountainz,
    80.0, 40.0, mountainz,
    80.0, 0.0, mountainz,
    90.0, 70.0, mountainz,
    90.0, 0.0, mountainz,
    100.0, 50.0, mountainz,
    100.0, 0.0, mountainz
};


void drawHead()
{
    int j;
    //draw circle head with nv vertices, center (cx,cy,xz)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(cx, cy, cz);
    for (j = 0; j <= nv; j++)
    {
        glVertex3f(r * cos((float)(j) / nv * 2 * PI) + cx,
            r * sin((float)(j) / nv * 2 * PI) + cy,
            cz);
    }
    glEnd();


}

void drawStickBody()
{
    //draw line for body, starting at bottom of head,
      //of length bodylength
    glLineWidth(5.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(cx, cy - r, cz);
    glVertex3f(cx, cy - r - bodylength, cz);
    glEnd();
    glLineWidth(1.0);  //restore width and color
    glColor3f(0.0, 0.0, 0.0);

}

void drawStickArms()
{
    //draw 2 arms, attached partly down body, going down,
    //at slight angle.
    glLineWidth(5.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(cx, cy - r - .2 * bodylength, cz); //down 20% of body
    glVertex3f(cx - 1, cy - r - 1.2 * bodylength, cz);
    glVertex3f(cx, cy - r - .2 * bodylength, cz); //down 20% of body
    glVertex3f(cx + 1, cy - r - 1.2 * bodylength, cz);
    glEnd();
    glLineWidth(1.0);  //restore width and color
    glColor3f(0.0, 0.0, 0.0);
}

void drawStickLegs()
{
    //draw 2 legs, attached at bottom of body, going out
    //at slight angle,
    glLineWidth(5.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(cx, cy - r - bodylength, cz); //down at bottom of body
    glVertex3f(cx - 1, cy - r - bodylength - 6, cz);
    glVertex3f(cx, cy - r - bodylength, cz); //down at bottom of body
    glVertex3f(cx + 1, cy - r - bodylength - 6, cz);
    glEnd();
    glLineWidth(1.0);  //restore width and color
    glColor3f(0.0, 0.0, 0.0);
}

void drawMountains()
{
    glColor3f(.2, .2, .2);
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 22; i++) glArrayElement(i);
    glEnd();
    glFlush();
}

void drawSnowPeaks()
{
    // Snow Peaks
    // Peak 0
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(40.0, 60.0, snowpeakz);
    glVertex3f(30.0, 50.0, snowpeakz);
    glVertex3f(33.3, 55.0, snowpeakz);
    glVertex3f(36.6, 50.0, snowpeakz);
    glVertex3f(40.0, 55.0, snowpeakz);
    glVertex3f(43.3, 50.0, snowpeakz);
    glVertex3f(46.3, 55.0, snowpeakz);
    glVertex3f(50.0, 50.0, snowpeakz);
    glEnd();
    // Peak 1
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(70.0, 60.0, snowpeakz);
    glVertex3f(60.0, 40.0, snowpeakz);
    glVertex3f(63.3, 55.0, snowpeakz);
    glVertex3f(66.6, 50.0, snowpeakz);
    glVertex3f(70.0, 55.0, snowpeakz);
    glVertex3f(73.3, 50.0, snowpeakz);
    glVertex3f(76.3, 55.0, snowpeakz);
    glVertex3f(80.0, 40.0, snowpeakz);
    glEnd();
    // Peak 2
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(90.0, 70.0, snowpeakz);
    glVertex3f(86.0, 58.0, snowpeakz);
    glVertex3f(90.3, 65.0, snowpeakz);
    glVertex3f(95.0, 60.0, snowpeakz);
    glEnd();
}

void drawStars() 
{
    // Ursa Major
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex3f(5.0, 90.0, starz);
    glVertex3f(9.0, 89.0, starz);
    glVertex3f(11.0, 86.0, starz);
    glVertex3f(15.0, 84.0, starz);
    glVertex3f(14.5, 79.0, starz);
    glVertex3f(22.0, 77.0, starz);
    glVertex3f(24.0, 82.0, starz);
    glVertex3f(15.0, 84.0, starz);
    glEnd();

    // 1000 random stars
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; i++) {
        int x = (rand() % 100 + 1);
        int y = (rand() % 100 + 1);
        glVertex3f(x, y, starz);
    }
    glEnd();
    
}

void printInteraction()
{
    cout << "TEST" << endl;
}

void drawCylinder() {
    int q = 10;
    glColor3f(1, 1, 1);
    for (int j = 0; j < q; j++)
    {
        int R = 5;
        int p = 10;
        // One latitudinal triangle strip.
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= p; i++)
        {
            glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) *
                cos(2.0 * (float)i / p * PI),
                R * sin((float)(j + 1) / q * PI / 2.0),
                -R * cos((float)(j + 1) / q * PI / 2.0) *
                sin(2.0 * (float)i / p * PI));
            glVertex3f(R * cos((float)j / q * PI / 2.0) *
                cos(2.0 * (float)i / p * PI),
                R * sin((float)j / q * PI / 2.0),
                -R * cos((float)j / q * PI / 2.0) *
                sin(2.0 * (float)i / p * PI));
        }
    }
}


// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    if (isOrtho) {
        glOrtho(0, 100, 0, 100, -1, 20);
    }
    else {
        cout << "Frust set" << endl;
        drawCylinder();
        glFrustum(0, 5, 0, 5, 1, 20);
    }
    drawStars();
    drawMountains();
    drawSnowPeaks();
    drawHead();
    drawStickArms();
    drawStickBody();
    drawStickLegs();
    

    

    printInteraction();
    

    glutSwapBuffers(); //instead of glFlush, double buffer
}

// Initialization routine.
void setup(void)
{
    glClearColor(.125, .165, .271, -20.0);

    // Enable vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mountainVerts);

   
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100.0, 0.0, 100.0, -1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'v':
        isOrtho = !isOrtho;
        glFlush();
        glutPostRedisplay();

    default:
        break;
    }
}



// Main routine.
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A Simple Person");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();

    return 0;
}
