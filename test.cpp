////
////  walkingAroundForClass.cpp
////  Marjory Baruch
////  builds a ring of numbers, corresponding
////  to angles in degrees, in a circle of radius
////  50, centered at the origin.
//
////  This version has no lookat.
//
////  floor is xz plane, positive y is up.
//
////This define is so you can use sprintf
//#define _CRT_SECURE_NO_DEPRECATE
//
//#include <iostream>
//#include <stdio.h>
//#include <cmath>
//
//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#endif
//
//#define PI 3.14159
//using namespace std;
//
////I don't use these by you can
//static float meX = 0, meY = 0, meZ = 0;
//static float angle = 0;  //angle facing
//static float stepsize = 5.0;  //step size
//static float turnsize = 10.0; //degrees to turn
//
//// Initialization routine.
//void setup(void)
//{
//    glClearColor(1.0, 1.0, 1.0, 0.0);
//    glEnable(GL_DEPTH_TEST); // Enable depth testing.
//}
//
//// OpenGL window reshape routine.
//void resize(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(120, 1, 1, 100);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// Routine to draw a stroke character string.
//void writeStrokeString(void* font, const char* string)
//{
//    const char* c;
//    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
//}
//
//
//// Drawing routine.
//void drawScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    //gluLookAt goes here
//    gluLookAt(meX, meY, meZ,
//        meX + sin(angle * PI/180), meY, meZ + cos(angle * PI / 180),
//        0, 1, 0);
//
//
//
//    //Print the numbers in a circle.
//    //radius 50
//    //0 at (0,0,50)
//    //90 at (50,0,0)
//    glColor4f(0.0, 0.0, 0.0, 1.0);
//    for (int theta = 0; theta < 360; theta += 10)
//    {
//        glPushMatrix();
//        glTranslatef(50 * sin(theta * PI / 180), 0.0, 50 * cos(theta * PI / 180));
//        glRotatef(theta, 0, 1, 0);
//
//        glRotatef(180, 0.0, 1.0, 0.0); //line it up with 0 position
//        glScalef(0.025, 0.025, 0.025);
//
//        // convert a number to a string for printing
//        char numString[5];
//        sprintf(numString, "%d", theta);
//        writeStrokeString(GLUT_STROKE_ROMAN, numString);
//
//        glPopMatrix();
//    }
//
//
//    glutSwapBuffers();
//}
//
//void specialKeyInput(int key, int x, int y)
//{
//    switch (key) {
//    case GLUT_KEY_UP: //forward
//        meX += stepsize * sin(angle * PI / 180);
//        meZ += stepsize * cos(angle * PI / 180);
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_DOWN: //back
//        meX -= stepsize * sin(angle * PI / 180);
//        meZ -= stepsize * cos(angle * PI / 180);
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_RIGHT: //turn right
//        angle -= turnsize;
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_LEFT: //turn left
//        angle += turnsize;
//        glutPostRedisplay();
//        break;
//    }//end switch
//    glutPostRedisplay();
//}
//
//// Routine to output interaction instructions to the C++ window.
//void printInteraction(void)
//{
//    cout << "Interaction:" << endl;
//    cout << "Not yet implemented:" << endl;
//    cout << "\tup arrow - step forward" << endl;
//    cout << "\tdown arrow - step backward" << endl;
//    cout << "\tright arrow - turn to the right" << endl;
//    cout << "\tleft arrow - turn to the left" << endl;
//    cout << "\tr - reset to standing in the center ";
//    cout << "facing 0 degrees." << endl;
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
//    case 'r':
//
//        break;
//    default:
//        break;
//    }
//}
//
//
//// Main routine.
//int main(int argc, char** argv)
//{
//    printInteraction();
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Walking around looking at numbers.");
//    setup();
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutSpecialFunc(specialKeyInput);
//    glutMainLoop();
//
//    return 0;
//}