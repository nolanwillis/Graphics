///////////////////////////////////////////////////////////////////////         
//// circleAndMore.cpp
////
//// Draw a 6 sided circle (aka hexagon) and a rectangle per Exercise
//
////
//// Interaction:
////  
////
//// Baruch and you
/////////////////////////////////////////////////////////////////////// 
//
//#include <cstdlib>
//#include <cmath>
//#include <iostream>
//
//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#endif
//
//#define PI 3.14159265358979324
//
//using namespace std;
//
//// Globals.
//static float R = 40.0; // Radius of circle.
//static float X = 50.0; // X-coordinate of center of circle.
//static float Y = 50.0; // Y-coordinate of center of circle.
//static int numVertices = 5; // Number of vertices on circle.
//bool big = false;
//static float zRect = -2;
//static float zHex = -3;
//
//
//// Drawing routine.
//void drawScene(void)
//{
//    float t = 0; // Angle parameter.
//    int i;
//
//    //Set viewing box
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    if (!big) {
//        glOrtho(-10.0, 10.0, 0, 20, 1, 10);
//    }
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//
//
//    //Display the background
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//
//
//    //Draw a green rectangle
//    glColor3f(0.0, 1.0, 0.0);  //*********needs values************
//
//
//    glBegin(GL_POLYGON);
//    glVertex3f(-1.0, 3.0, zRect);  //*********needs values************
//    glVertex3f(8.0, 3.0, zRect);  //*********needs values************
//    glVertex3f(8.0, 5.0, zRect);  //*********needs values************
//    glVertex3f(-1.0, 5.0, zRect);  //*********needs values************
//    glEnd();
//
//
//
//    // Draw a light blue hexagon
//    glLineWidth(5);
//    glColor3f(0.5, 0.5, 1.0);  //*********needs values************
//    glBegin(GL_LINE_LOOP);
//    for (i = 0; i < 6; ++i)  //*********needs a value************
//    {
//
//        glVertex3f(5.0 + 6.5 *cos(t), 7.0 + 6.5 * sin(t), zHex );  //*********needs values************
//        t += 2 * PI / 6 ;  //*********needs a value************
//    }
//    glEnd();
//
//    // Adds new vertices to the screen
//    glFlush();
//}
//
//// Initialization routine.
//void setup(void)
//{	//light yellow background
//    glClearColor(1, 1, .5, 0); //*********needs values************
//}
//
//// OpenGL window reshape routine.
//void resize(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    //glOrtho moved to drawScene
//}
//
//// Keyboard input processing routine.
//void keyInput(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 27:
//        exit(0);
//        break;
//    case 'b':
//        big = true;
//        
//
//    default:
//        break;
//    }
//}
//
//// Routine to output interaction instructions to the C++ window.
//void printInteraction(void)
//{
//    cout << "Interaction:" << endl;
//    cout << "Press escape to quit" << endl;
//}
//
//// Main routine.
//int main(int argc, char** argv)
//{
//    printInteraction();
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("circleAndMore.cpp");
//    setup();
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutMainLoop();
//
//    return 0;
//}