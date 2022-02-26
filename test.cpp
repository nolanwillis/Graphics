//#include <iostream>
//
//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#endif
//
//using namespace std;
//
//
////Globals
//double angle = 30;
//bool showBlackSide = false;
//bool wire = true;
//bool solid = true;
//
//
//
//// Drawing routine.
//void drawScene(void)
//{
//    glLoadIdentity();
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glLineWidth(5);
//
//    //Translate the icosahedron
//    glPushMatrix();
//    glTranslatef(0, 0, -5);
//
//    glPushMatrix(); //for rotating both of the icosahedrons
//
//    //Rotate the clipped icosahedroons around vertical axis
//    glRotated(angle, 0, 1, 0);
//
//    //draw a clipped icosahedron
//    double rEq[4] = { 1,0,0,0 };
//
//    glClipPlane(GL_CLIP_PLANE0, rEq);
//    glEnable(GL_CLIP_PLANE0);
//    if (solid)
//    {
//        glColor3f(1.0, 1.0, 1.0);
//        glutSolidIcosahedron();
//    }
//    if (wire)
//    {
//        glColor3f(.5, .5, .5);
//        glutWireIcosahedron();
//    }
//    glDisable(GL_CLIP_PLANE0);
//
//    if (showBlackSide)
//    {
//        //make black half icosahedron
//        double lEq[4] = { -1,0,0,0 };
//
//        glClipPlane(GL_CLIP_PLANE1, lEq);
//        glEnable(GL_CLIP_PLANE1);
//        if (solid)
//        {
//            glColor3f(0.0, 0.0, 1.0);
//            glutSolidIcosahedron();
//        }
//        if (wire)
//        {
//            glColor3f(0.5, 0.5, 0.5);
//            glutWireIcosahedron();
//
//        }
//        glDisable(GL_CLIP_PLANE1);
//    }//end show black side
//
//    glPopMatrix();//for rotating the icosahedrons
//
//    glPopMatrix();  //for translating icosahedrons
//
//
//    glutSwapBuffers();
//}
//
//// Initialization routine.
//void setup(void)
//{
//    glClearColor(0.0, 0.0, 1.0, 0.0);
//
//}
//
//// OpenGL window reshape routine.
//void resize(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-2, 2, -2, 2, 3.5, 10);
//    glMatrixMode(GL_MODELVIEW);
//
//}
//
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
//
//    case 's':
//        showBlackSide = !showBlackSide;
//        glutPostRedisplay();
//        break;
//
//    default:
//        break;
//    }
//}
//
//// Routine to output interaction instructions to the C++ window.
//void printInteraction(void)
//{
//    std::cout << "Interaction:" << std::endl;
//    std::cout << "Press s to see/hide black half." << std::endl;
//    std::cout << "Press esc to quit." << std::endl;
//}
//
//// Main routine.
//int main(int argc, char** argv)
//{
//    printInteraction();
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("clipped icosahedron");
//    setup();
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutMainLoop();
//
//    return 0;
//}