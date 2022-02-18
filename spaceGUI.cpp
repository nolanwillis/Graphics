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
//* Date submitted: February 13, 2022
//* 
//* References: 
//* 
//* Interactions: 
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



// For writting text
void writeBitmapString(void* font, char* string)
{
    char* c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


// Draw
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glFrustum(0.0, 100.0, 0.0, 100.0, 1.0, 20.0);
    
    glColor3f(219.0 / 255.0, 80.0 / 255.0, 74.0 / 255.0);
    glBegin(GL_POLYGON);
    glVertex3f(20, 180, -2);
    glVertex3f(20, 20, -2);
    glVertex3f(180, 20, -2);
    glVertex3f(180, 180, -2);
    glEnd();
   
    glutSwapBuffers(); //instead of glFlush, double buffer
}


// Initialization
void setup(void)
{
    glClearColor(8.0 / 255.0, 76.0 / 255.0, 97.0 / 255.0, -20.0);
}


// OpenGL window reshape
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0.0, 100.0, 0.0, 100.0, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}


// Keyboard input processing
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}


// Main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Skyviewer");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();

    return 0;
}
