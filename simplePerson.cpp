///***********************************************************
//*
//* Name: Nolan Willis
//*
//* Email: nwillis@syr.edu    
//*
//* Assignment: Assignment 1
//* 
//* Environment: Visual Studio Community 2022
//* 
//* Date submitted: February 13, 2022
//* 
//* References: simplePerson.cpp from class and 
//* Computer Graphics Through OpenGL, 3rd Edition, Sumanta Guha
//* 
//* Interactions: press v to switch view mode
//*
//************************************************************/
//
//#include <cmath>
//  //sin, cos
//#include <iostream>
//
//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#endif
//
//#define PI 3.14159
//
//using namespace std;
//
//// Globals.
//
//// Bool value to keep track of view mode (ortho or frust)
//bool isOrtho = true;
//
//// Z-values for the mountains, stars, and snow peaks
//float mountainz = -18.0; 
//float starz = -19.0;
//float snowpeakz = -17.0;
//
//// Color and vertex arrays for the mountains
//static float mountainVerts[] =
//{
//    0.0, 30.0, mountainz,
//    0.0, 0.0, mountainz,
//    10.0, 40.0, mountainz,
//    10.0, 0.0, mountainz,
//    20.0, 50.0, mountainz,
//    20.0, 0.0, mountainz,
//    30.0, 50.0, mountainz,
//    30.0, 0.0, mountainz,
//    40.0, 60.0, mountainz,
//    40.0, 0.0, mountainz,
//    50.0, 50.0, mountainz,
//    50.0, 0.0, mountainz,
//    60.0, 40.0, mountainz,
//    60.0, 0.0, mountainz,
//    70.0, 60.0, mountainz,
//    70.0, 0.0, mountainz,
//    80.0, 40.0, mountainz,
//    80.0, 0.0, mountainz,
//    90.0, 70.0, mountainz,
//    90.0, 0.0, mountainz,
//    100.0, 50.0, mountainz,
//    100.0, 0.0, mountainz
//};
//static float mountainColors[]
//{
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//    .5, .5, .5,
//    .2, .2, .2,
//
//};
//
//
//void drawHead(float cx, float cy, float cz, float r, float nv)
//{
//    int j;
//    //draw circle head with nv vertices, center (cx,cy,xz)
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(cx, cy, cz);
//    for (j = 0; j <= nv; j++)
//    {
//        glVertex3f(r * cos((float)(j) / nv * 2 * PI) + cx,
//            r * sin((float)(j) / nv * 2 * PI) + cy,
//            cz);
//    }
//    glEnd();
//
//
//}
//
//
//void drawStickBody(float cx, float cy, float cz, float r, float bodylength)
//{
//    //draw line for body, starting at bottom of head,
//      //of length bodylength
//    glLineWidth(5.0);
//    glBegin(GL_LINES);
//    glVertex3f(cx, cy - r, cz);
//    glVertex3f(cx, cy - r - bodylength, cz);
//    glEnd();
//    glLineWidth(1.0);  //restore width and color
//}
//
//
//void drawStickArms(float cx, float cy, float cz, float r, float bodylength)
//{
//    //draw 2 arms, attached partly down body, going down,
//    //at slight angle.
//    glLineWidth(5.0);
//    glBegin(GL_LINES);
//    glVertex3f(cx, cy - r - .2 * bodylength, cz); //down 20% of body
//    glVertex3f(cx - 1, cy - r - 1.2 * bodylength, cz);
//    glVertex3f(cx, cy - r - .2 * bodylength, cz); //down 20% of body
//    glVertex3f(cx + 1, cy - r - 1.2 * bodylength, cz);
//    glEnd();
//    glLineWidth(1.0);  //restore width and color
//    
//}
//
//
//void drawStickLegs(float cx, float cy, float cz, float r, float bodylength)
//{
//    //draw 2 legs, attached at bottom of body, going out
//    //at slight angle,
//    glLineWidth(5.0);
//    glBegin(GL_LINES);
//    glVertex3f(cx, cy - r - bodylength, cz); //down at bottom of body
//    glVertex3f(cx - 1, cy - r - bodylength - 6, cz);
//    glVertex3f(cx, cy - r - bodylength, cz); //down at bottom of body
//    glVertex3f(cx + 1, cy - r - bodylength - 6, cz);
//    glEnd();
//    glLineWidth(1.0);  //restore width and color
//   
//}
//
//
//// Draws mountains using a triangle strip
//void drawMountains()
//{ 
//    glColor3f(.2, .2, .2);
//    glBegin(GL_TRIANGLE_STRIP);
//        for (int i = 0; i < 22; i++) glArrayElement(i);
//    glEnd();
//    glFlush();
//}
//
//
//// Draws snow peaks using triangle fans
//void drawSnowPeaks()
//{
//    // Peak 0
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(40.0, 60.0, snowpeakz);
//    glVertex3f(30.0, 50.0, snowpeakz);
//    glVertex3f(33.3, 55.0, snowpeakz);
//    glVertex3f(36.6, 50.0, snowpeakz);
//    glVertex3f(40.0, 55.0, snowpeakz);
//    glVertex3f(43.3, 50.0, snowpeakz);
//    glVertex3f(46.3, 55.0, snowpeakz);
//    glVertex3f(50.0, 50.0, snowpeakz);
//    glEnd();
//    // Peak 1
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(70.0, 60.0, snowpeakz);
//    glVertex3f(60.0, 40.0, snowpeakz);
//    glVertex3f(63.3, 55.0, snowpeakz);
//    glVertex3f(66.6, 50.0, snowpeakz);
//    glVertex3f(70.0, 55.0, snowpeakz);
//    glVertex3f(73.3, 50.0, snowpeakz);
//    glVertex3f(76.3, 55.0, snowpeakz);
//    glVertex3f(80.0, 40.0, snowpeakz);
//    glEnd();
//    // Peak 2
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex3f(90.0, 70.0, snowpeakz);
//    glVertex3f(86.0, 58.0, snowpeakz);
//    glVertex3f(90.3, 65.0, snowpeakz);
//    glVertex3f(95.0, 60.0, snowpeakz);
//    glEnd();
//}
//
//
//// Draws stars behind the mountains
//void drawStars() 
//{
//    // Ursa Major
//    glColor3f(1.0, 1.0, 1.0);
//    glPointSize(3);
//    glBegin(GL_POINTS);
//    glVertex3f(5.0, 90.0, starz);
//    glVertex3f(9.0, 89.0, starz);
//    glVertex3f(11.0, 86.0, starz);
//    glVertex3f(15.0, 84.0, starz);
//    glVertex3f(14.5, 79.0, starz);
//    glVertex3f(22.0, 77.0, starz);
//    glVertex3f(24.0, 82.0, starz);
//    glVertex3f(15.0, 84.0, starz);
//    glEnd();
//
//    // 1000 random stars
//    glPointSize(1);
//    glBegin(GL_POINTS);
//    for (int i = 0; i < 1000; i++) {
//        int x = (rand() % 100 + 1);
//        int y = (rand() % 100 + 1);
//        glVertex3f(x, y, starz);
//    }
//    glEnd();
//}
//
//
//// Prints instructions to the terminal
//void printInteraction()
//{
//    cout << "\nPress v to change view mode" << endl;
//}
//
//
//// Draws a circle in the xz plane
//void drawCircle(float Y) 
//{
//    float numVerts = 500;
//    float R = 3;
//    float Z = -10;
//    float X = 50;
//    float t = 0;
//    glBegin(GL_LINE_LOOP);
//    for (int i = 0; i < numVerts; i++)
//    {
//        glVertex3f(X + R * sin(t), Y, Z + R * cos(t));
//        t += 2 * PI / numVerts;
//    }
//    glEnd();
//}
//
//
//// Stacks multiple circles on top of each other
//void drawCylinder() 
//{
//    for (int i = 5; i < 30; i++) {
//        drawCircle(i);
//      
//    }
//}
//
//
//// Draws all the parts of person, so multiple people can be drawn easily
//void drawPerson(float cx, float cy, float cz, float r, float bodylength, float nv) 
//{
//    drawHead(cx, cy, cz, r, nv );
//    drawStickArms(cx, cy, cz, r, bodylength);
//    drawStickBody(cx, cy, cz, r, bodylength);
//    drawStickLegs(cx, cy, cz, r, bodylength);
//}
//
//
//// Draws a polar bear, lets you scale the bear's size and move it in x,y,z directions
//void drawVertexBear(float scale, float x, float y, float z) {
//    glColor3f(1, 1, 1);
//    glBegin(GL_LINE_LOOP);
//    glVertex3f(1 * scale + x, .5 * scale + y, z);
//    glVertex3f(1.1 * scale + x, 0 + y, z);
//    glVertex3f(2 * scale + x, 0 + y, z);
//    glVertex3f(2.25 * scale + x, .75 * scale + y, z);
//    glVertex3f(2.5 * scale + x, 1.5 * scale + y, z);
//    glVertex3f(3 * scale + x, 0 + y, z);
//    glVertex3f(4 * scale + x , 0 + y, z);
//    glVertex3f(4 * scale + x, 1.5 * scale + y, z);
//    glVertex3f(4.5 * scale + x, 1 * scale + y, z);
//    glVertex3f(4.5 * scale + x, 0 + y, z);
//    glVertex3f(5.5 * scale + x, 0 + y, z);
//    glVertex3f(5.5 * scale + x, 1 * scale + y, z);
//    glVertex3f(6 * scale + x, 1.5 * scale + y, z);
//    glVertex3f(6 * scale + x, 0 + y, z);
//    glVertex3f(7 * scale + x, 0 + y, z);
//    glVertex3f(7 * scale + x, 2 * scale + y, z);
//    glVertex3f(9 * scale + x, 2.5 * scale + y, z);
//    glVertex3f(10 * scale + x, 3 * scale + y, z);
//    glVertex3f(9 * scale + x, 4 * scale + y, z);
//    glVertex3f(8 * scale + x, 4 * scale + y, z);
//    glVertex3f(5 * scale + x, 5 * scale + y, z);
//    glVertex3f(2 * scale + x, 4 * scale + y, z);
//    glVertex3f(1 * scale + x, 3 * scale + y, z);
//    glVertex3f(1.5 * scale + x, 1.5 * scale + y, z);
//    glVertex3f(1 * scale + x, .5 * scale + y, z);
//    glEnd();
//}
//
//// Defines a speech bubble
//void drawSpeechBubble(float scale, float x, float y, float z) {
//    glColor3f(1, 1, 1);
//    glPolygonMode(GL_FRONT, GL_FILL);
//    glBegin(GL_POLYGON);
//        glVertex3f(1.0 * scale + x, 4.0 * scale + y, z);
//        glVertex3f(1.0 * scale + x, 2.0 * scale + y, z);
//        glVertex3f(3.0 * scale + x, 2.0 * scale + y, z);
//        glVertex3f(3.5 * scale + x, 0.0 * scale + y, z);
//        glVertex3f(4.0 * scale + x, 2.0 * scale + y, z);
//        glVertex3f(6.0 * scale + x, 2.0 * scale + y, z);
//        glVertex3f(6.0 * scale + x, 4.0 * scale + y, z);
//        glVertex3f(1.0 * scale + x, 4.0 * scale + y, z);
//    glEnd();
//}
//
//
//// Defines a brown sign
//void drawSign(float scale, float x, float y, float z) {
//    glColor3f(79.0 / 255.0, 53.0 / 255.0, 36.0 / 255.0);
//    glPolygonMode(GL_FRONT, GL_FILL);
//
//    // Sign face
//    glBegin(GL_POLYGON);
//    glVertex3f(1.0 * scale + x, 4.0 * scale + y, z);
//    glVertex3f(1.0 * scale + x, 2.0 * scale + y, z);
//    glVertex3f(6.0 * scale + x, 2.0 * scale + y, z);
//    glVertex3f(6.0 * scale + x, 4.0 * scale + y, z);
//    glVertex3f(1.0 * scale + x, 4.0 * scale + y, z);
//    glEnd();
//
//    // Sign post
//    glBegin(GL_POLYGON);
//    glVertex3f(3.25 * scale + x, 2.0 * scale + y, z);
//    glVertex3f(3.25 * scale + x, 0.0 * scale + y, z);
//    glVertex3f(3.75 * scale + x, 0.0 * scale + y, z);
//    glVertex3f(3.75 * scale + x, 2.0 * scale + y, z);
//    glEnd();
//}
//
//
//// For writting text
//void writeBitmapString(void* font, char* string)
//{
//    char* c;
//    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
//}
//
//
//// Draws speech bubbles and sign with text
//void drawTextBoxes() 
//{
//    drawSpeechBubble(2, 41, 30, -14);
//    glColor3f(0, 0, 0);
//    glRasterPos3f(45, 35, -13);
//    char bluepersonmessage[] = "Oh no...";
//    writeBitmapString(GLUT_BITMAP_HELVETICA_18, bluepersonmessage);
//
//    drawSpeechBubble(2, 21, 60, -14);
//    glColor3f(0, 0, 0);
//    glRasterPos3f(23, 65.5, -13);
//    char orangepersonmessage[] = "VERTEX BEARS!";
//    writeBitmapString(GLUT_BITMAP_HELVETICA_12, orangepersonmessage);
//
//    glColor3f(1, 1, 1);
//    glRasterPos3f(73.4, 22, -13);
//    char signmessage[] = "Beware of vertex bears";
//    writeBitmapString(GLUT_BITMAP_HELVETICA_10, signmessage);
//
//    drawSign(2.5, 70, 15, -14);
//}
//
//
//// Draws two-sided box/doorway
//void drawTwoSidedBox()
//{
//    // Back
//    glColor3f(.1, .1, .1);
//    glBegin(GL_POLYGON);
//    glVertex3f(4, 50, -19);
//    glVertex3f(34, 50, -19);
//    glVertex3f(34, 20, -19);
//    glVertex3f(4, 20, -19);
//    glEnd();
//
//    // Front
//    glColor3f(1, 0, 0);
//    glBegin(GL_LINE_LOOP);
//    glVertex3f(-5, 35, -10);
//    glVertex3f(25, 35, -10);
//    glVertex3f(25, 5, -10);
//    glVertex3f(-5, 5, -10);
//    glEnd();
//
//    // Top
//    glColor3f(0, 1, 0);
//    glBegin(GL_POLYGON);
//    glVertex3f(-5, 35, -10);
//    glColor3f(.1, .1, .1);
//    glVertex3f(4, 50, -19);
//    glVertex3f(34, 50, -19);
//    glColor3f(0, 1, 0);
//    glVertex3f(25, 35, -10);
//    glEnd();
//
//    // Bottom
//    glColor3f(0, 0, 1);
//    glBegin(GL_POLYGON);
//    glVertex3f(-5, 5, -10);
//    glColor3f(.1, .1, .1);
//    glVertex3f(4, 20, -19);
//    glVertex3f(34, 20, -19);
//    glColor3f(0, 0, 1);
//    glVertex3f(25, 5, -10);
//    glEnd();
//}
//
//
//
//// Drawing routine
//void drawScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_PROJECTION);
//    glEnable(GL_DEPTH_TEST);
//    glLoadIdentity();
//
//    if (isOrtho) {
//        cout << "Orthographic view set" << endl;
//        glOrtho(0, 100, 0, 100, -1, 20);
//        glClearColor(.125, .165, .271, -20.0);
//        drawStars();
//        drawMountains();
//        drawSnowPeaks();
//        glColor3f(0, 0, 1);
//        drawPerson(50, 30, -1, 1, 4, 10);
//        glColor3f(1, .5, 0);
//        drawPerson(30, 60, -18.1, 1, 6, 10);
//        drawVertexBear(3, 2, 10, -15);
//        drawVertexBear(1, 2, 5, -14);
//        drawVertexBear(1, 23, 10, -13);
//        drawTextBoxes();
//        
//    }
//    else {
//        cout << "Frustrum view set \n" << endl;
//        glFrustum(-10, 10, -10, 10, 1, 20);
//        glClearColor(0, 0, 0, -20);
//        glColor3f(1, 1, 1);
//        drawCylinder();
//        drawTwoSidedBox();
//    }
//   
//    printInteraction();
//    glutSwapBuffers(); //instead of glFlush, double buffer
//}
//
//
//// Initialization routine.
//void setup(void)
//{
//    // Enable vertex/color arrays
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
//
//    // Define vertex/color array pointers
//    glVertexPointer(3, GL_FLOAT, 0, mountainVerts);
//    glColorPointer(3, GL_FLOAT, 0, mountainColors);
//}
//
//
//// OpenGL window reshape routine.
//void resize(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, 100.0, 0.0, 100.0, -1.0, 20.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//
//// Keyboard input processing routine.
//void keyInput(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 27:
//        exit(0);
//        break;
//    // Changes from ortho to frust when user clicks 'v'
//    case 'v':
//        isOrtho = !isOrtho;
//        glutPostRedisplay();
//    default:
//        break;
//    }
//}
//
//
//// Main routine.
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(1000, 1000);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("A Simple Person");
//    setup();
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutMainLoop();
//
//    return 0;
//}
