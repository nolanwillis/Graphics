/////***********************************************************
////*
////* Name: Nolan Willis
////*
////* Email: nwillis@syr.edu    
////*
////* Assignment: Assignment 4
////* 
////* Environment: Visual Studio Community 2022
////* 
////* Date submitted: 4/12/2022
////* 
////* References: None
////* 
////* Interactions: 
////      Use arrow keys to move around
////      Press d or click the doors to open
////      Press L to turn on the hall light
////      Press > or < to increase/decrease the ambient lighting of the scene 
////      Walk near the flashlight or click s to pick it up
////      Press f to turn the flashlight on or off
////      Press w or click the wand to start the guessing game
////      Press G, H, R, or S to select a house guess
////      Press esc to exit 
////*
////************************************************************/
//
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
////Global Variables------------------------------------------------------------------------
//
////Window size
//int height, width;
//
////Mouse click coordinates
//int mouseX, mouseY;
//
////Camera position values
//float eyeX = 6, eyeY = 8, eyeZ = 2;
//static float eyeAngle = 180;  //angle user is facing
//static float stepSize = 5.0;  //step size
//static float turnSize = 10.0; //degrees to turn
//
////Flashlight position values
//float flX = -5, flY = 5, flZ = -70;
//
////Value to keep track of selecting state
//bool isSelecting = false;
//
////Array of houses
//string houses[] = { "Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"};
//
////Instruction text
//char inst[] = "Guess a house G for Gryffindor, H for Hufflepuff, R for Ravenclaw, and S for Slytherin";
//
////Result text
//char correct[] = "Correct! Your a wizard!";
//char incorrect[] = "Sorry you won't be a wizard :(";
//
////Rand house number
//int randHouse = -1;
//
////User guess
//int guess = -1;
//
////Keeps track if an answer was submitted
//bool submitted = false;
//
////Value to keep track of the last selected item
//int itemID = 0;
//
////IDs for selecting
//int DOOR = 1, WAND = 2, HAT = 3, FL = 4;
//
////Value to keep track of door angle
//float doorAngle = 0;
//
////Door x and y offsets (for animation)
//float doorX = 0, doorZ = 0;
//
////Open/close value of door
//int isDoorOpen = 0;
//
////On/off lightSwitch
//bool lightOn = false;
//
////On/off for flashlight
//bool flOn = false;
//
////Near flashlight value for animation (when near, animate fl to eye pos)
//bool nearFL = false;
//
////Boolean to turn on/off collision
//bool collActive = true;
//
////Wand X,Y,Z offsets (for animation)
//float wandX = 0, wandY = 0, wandZ = 0;
//
////Value to determine if the wand is over the hat
//float overHat = false;
//
////Hat rotation angle offset (for animation)
//float hatAngle = 0.0;
//
////Hat Y offset (for animation)
//float hatY = 0.0;
//
////Global specular and shininess arrays for all objects
//float materialSpec[] = { 1.0, 1.0, 1.0, 1.0 }, materialShin[] = { 50.0 };
//
////Position of light0
//float light0posX = 5.5, light0posY = 40.0, light0posZ = -60.0;
//
////Position of light1
//float light1posX = 5.5, light1posY = 6 , light1posZ = -16.5;
//
////Colored materials for lighting
////Stone: used on the courtyard and bridge
//float stoneMatAmbandDif[] = { 101.0 / 255.0, 102.0 / 255.0, 105 / 255.0, 1.0 };
////Sandstone: used on outdoor walls and railings
//float sandstoneMatAmbandDif[] = { 114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0, 1.0 };
////Wood: used on furniture and 
//float woodMatAmbandDif[] = { 70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0, 1.0 };
////White
//float whiteMatAmbandDif[] = { 1.0, 1.0, 1.0, 1.0 };
////Dark Grey
//float darkGreyMatAmbandDif[] = { .2, .2, .2, 1.0 };
////Hat color
//float hatMatAmbandDif[] = { 100.0/255.0, 85.0/255.0, 68.0/255, 1.0 };
////Black
//float blackMatAmbandDif[] = { 0, 0, 0, 1.0 };
////Red
//float redMatAmbandDif[] = { 1.0, 0, 0, 1.0 };
////Flame orange
//float forangeMatAmbandDif[] = { 255.0 / 255.0, 200.0 / 255.0, 35.0 / 255, 1.0 };
////Purple
//float purpleMatAmbandDif[] = { 72.0 / 255.0, 52.0 / 255.0, 117.0 / 255.0, 1.0 };
//
////Specular and shininess values for the hat
//float hatSpec[] = { 100.0 / 255.0, 85.0 / 255.0, 68.0 / 255, 1.0 };
//float hatShin[] = { 128 };
//
////Emissive values for the want
//float wandEmiss[] = { 0.9, 0.0, 0.0, 1.0 };
//
////Default emissive values
//float defEmiss[] = { 0.0, 0.0, 0.0, 1.0 };
//
////Global ambient values
//float gAmb = .6;
//
////--------------------------------------------------------------------------------------
//
////Function that sets the view mode (frust)
//void setViewMode()
//{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(90, 1, 1, 150);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void drawBridge()
//{
//    //Floor
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
//    glPushMatrix();
//    glTranslated(6, 0, -6.5);
//    glScaled(5, 1, 12);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right railing
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
//    glPushMatrix();
//    glTranslated(8.5, 1, -6);
//    glScaled(.5, 2, 12);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left railing
//    glPushMatrix();
//    glTranslated(3.5, 1, -6);
//    glScaled(.5, 2, 12);
//    glutSolidCube(1);
//    glPopMatrix();
//}
//
//void drawCourtyard() 
//{
//    //Floor
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
//    glPushMatrix();
//    glTranslated(6, 0, -22);
//    glScaled(50, 1, 20);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right front railing
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
//    glPushMatrix();
//    glTranslated(19.5, 2.5, -12);
//    glRotated(90, 0, 1, 0);
//    glScaled(.5, 5, 22.5);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left front railing
//    glPushMatrix();
//    glTranslated(-7.5, 2.5, -12);
//    glRotated(90, 0, 1, 0);
//    glScaled(.5, 5, 22.5);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right middle railing
//    glPushMatrix();
//    glTranslated(31, 2.5, -23);
//    glScaled(.5, 5, 22.5);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left middle railing
//    glPushMatrix();
//    glTranslated(-19, 2.5, -23);
//    glScaled(.5, 5, 22.5);
//    glutSolidCube(1);
//    glPopMatrix();
//  
//}
//
//void drawHall()
//{
//    //Outside color
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
//    //Inside color
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//
//    //Left wall
//    glPushMatrix();
//    glTranslated(-12.5, 0, -32);
//    glRotated(90, 0, 1, 0);
//    glScaled(60, 38, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 0.0, 1.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0); 
//    glEnd();
//    glPopMatrix();
//
//    //Left roof
//    glPushMatrix();
//    glTranslated(-12.5, 38, -32);
//    glRotated(-22, 0, 0, 1);
//    glRotated(90, 0, 1, 0);
//    glScaled(60, 50, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 0.0, 1.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Facade back
//    glPushMatrix();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glTranslated(-4.5, 38, -92);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, -1.0, 0.0);
//    glVertex3f(-9, 0, 0);
//    glVertex3f(10, 48, 0);
//    glVertex3f(29, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Outside color (switch GL_BACK/GL_FRONT, transformations are different)
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
//    //Inside color
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//
//    //Right wall
//    glPushMatrix();
//    glTranslated(22.5, 0, -32);
//    glRotated(90, 0, 1, 0);
//    glScaled(60, 38, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 0.0, -1.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Right roof
//    glPushMatrix();
//    glTranslated(23, 37, -32);
//    glRotated(22, 0, 0, 1);
//    glRotated(90, 0, 1, 0);
//    glScaled(60, 49, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 0.0, -1.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Facade front
//    glPushMatrix();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glTranslated(-4.5, 38, -32);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 1.0, 0.0);
//    glVertex3f(-9, 0, 0);
//    glVertex3f(10, 48, 0);
//    glVertex3f(29, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Front left
//    glPushMatrix();
//    glTranslated(-19.5, 0, -32);
//    glScaled(20, 38, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 1.0, 0.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Front center
//    glPushMatrix();
//    glTranslated(.5, 24.5, -32);
//    glScaled(11, 13.5, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 1.0, 0.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Front right
//    glPushMatrix();
//    glTranslated(11.5, 0, -32);
//    glScaled(20, 38, 0);
//    glBegin(GL_POLYGON);
//    glNormal3f(0.0, 1.0, 0.0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(1, 1, 0);
//    glVertex3f(1, 0, 0);
//    glEnd();
//    glPopMatrix();
//
//    //Outside color (switch GL_BACK/GL_FRONT, transformations are different)
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
//    //Inside color
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    
//    //Back wall
//    glPushMatrix();
//    glTranslatef(-13, 0.0, -92.0); 
//    glScaled(38, 38, 0);
//
//    //n rows and n columns of triangles
//    double n = 100.0;  
//    glNormal3f(0.0, -1.0, 0.0);
//    for (int r = 0; r < n; r++)  
//    {
//        glBegin(GL_TRIANGLE_STRIP);
//        for (int c = 0; c <= n; c++)
//        {
//            glVertex3f(c / n, r / n, 0.0);
//            glVertex3f(c / n, (r + 1) / n, 0.0);
//        }
//        glEnd();
//    }
//
//    glPopMatrix();
//
//    //Floor
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
//    glPushMatrix();
//    glTranslated(5, 0, -62);
//    glScaled(35, 1, 60);
//    glutSolidCube(1);
//    glPopMatrix();
//}
//
//void drawFurniture()
//{
//    //Table 1
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, woodMatAmbandDif);
//    glPushMatrix();
//    glTranslated(-5, 4, -60);
//    glScaled(3, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Table beam 1
//    glPushMatrix();
//    glTranslated(-5, 2, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(3, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench 1
//    glPushMatrix();
//    glTranslated(-6.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench beam 1
//    glPushMatrix();
//    glTranslated(-6.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench 1
//    glPushMatrix();
//    glTranslated(-3.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench beam 1
//    glPushMatrix();
//    glTranslated(-3.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    
//
//    //Table 2
//    glPushMatrix();
//    glTranslated(2, 4, -60);
//    glScaled(3, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Table beam 2
//    glPushMatrix();
//    glTranslated(2, 2, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(4, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench 2
//    glPushMatrix();
//    glTranslated(.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench beam 2
//    glPushMatrix();
//    glTranslated(.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench 2
//    glPushMatrix();
//    glTranslated(3.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench beam 2
//    glPushMatrix();
//    glTranslated(3.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Table 3
//    glPushMatrix();
//    glTranslated(10, 4, -60);
//    glScaled(3, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Table beam 3
//    glPushMatrix();
//    glTranslated(10, 2, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(4, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench 3
//    glPushMatrix();
//    glTranslated(8.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench beam 3
//    glPushMatrix();
//    glTranslated(8.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench 3
//    glPushMatrix();
//    glTranslated(11.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench beam 3
//    glPushMatrix();
//    glTranslated(11.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Table 4
//    glPushMatrix();
//    glTranslated(17, 4, -60);
//    glScaled(3, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Table beam 4
//    glPushMatrix();
//    glTranslated(17, 2, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(4, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench 4
//    glPushMatrix();
//    glTranslated(15.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Left bench beam 4
//    glPushMatrix();
//    glTranslated(15.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench 4
//    glPushMatrix();
//    glTranslated(18.5, 2, -60);
//    glScaled(1.5, .5, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Right bench beam 4
//    glPushMatrix();
//    glTranslated(18.5, 1, -60);
//    glRotated(90, 0, 0, 1);
//    glScaled(1.5, .25, 30);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Table 5
//    glPushMatrix();
//    glTranslated(5.5, 5, -87);
//    glRotated(90, 0, 1, 0);
//    glScaled(3, .5, 20);
//    glutSolidCube(1);
//    glPopMatrix();
//}
//
//void drawLightFixture()
//{
//    glPushMatrix(); //Transformations for the entire light fixture
//    glTranslated(light0posX, light0posY - 5, light0posZ + 6);
//    glTranslated(0, 0, 0);
//
//    //Ceiling arm
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, darkGreyMatAmbandDif);
//    glPushMatrix();
//    glTranslated(0, 15, -6.5);
//    glRotated(90, 0, 0, 1);
//    glScaled(20, .1, .1);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Arm facing north
//    glPushMatrix();
//    glTranslated(0, 2.5, -6.8);
//    glRotated(90, 0, 1, 0);
//    glScaled(3, .1, .1);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Light cone north
//    if (lightOn)
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
//    }
//    else
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    }
//    glPushMatrix();
//    glTranslated(0, 2.5, -8.5);
//    glRotated(-90, 1, 0, 0);
//    glutSolidCone(.3, 1.5, 25, 25);
//    glPopMatrix();
// 
//    //Arm facing east
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, darkGreyMatAmbandDif);
//    glPushMatrix();
//    glTranslated(.3, 2.5, -6.5);
//    glScaled(3, .1, .1);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Light cone east
//    if (lightOn)
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
//    }
//    else
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    }
//    glPushMatrix();
//    glTranslated(2, 2.5, -6.5);
//    glRotated(-90, 1, 0, 0);
//    glutSolidCone(.3, 1.5, 25, 25);
//    glPopMatrix();
// 
//    //Arm facing south (towards initial spawn)
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, darkGreyMatAmbandDif);
//    glPushMatrix();
//    glTranslated(0, 2.5, -6.2);
//    glRotated(-90, 0, 1, 0);
//    glScaled(3, .1, .1);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Light cone south
//    if (lightOn)
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
//    }
//    else
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    }
//    glPushMatrix();
//    glTranslated(0, 2.5, -4.5);
//    glRotated(-90, 1, 0, 0);
//    glutSolidCone(.3, 1.5, 25, 25);
//    glPopMatrix();
// 
//    //Arm facing west
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, darkGreyMatAmbandDif);
//    glPushMatrix();
//    glTranslated(-.3, 2.5, -6.5);
//    glScaled(3, .1, .1);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    //Light cone west
//    if (lightOn)
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
//    }
//    else
//    {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    }
//    glPushMatrix();
//    glTranslated(-2, 2.5, -6.5);
//    glRotated(-90, 1, 0, 0);
//    glutSolidCone(.3, 1.5, 25, 25);
//    glPopMatrix();
//
//    glPopMatrix();
//
//}
//
//void drawWand(float R, float G, float B) {
//    
//    glPushMatrix(); //Transformations to move all parts of the wand
//    glTranslated(wandX, wandY, wandZ);
//
//    glColor3f(R, G, B); 
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, darkGreyMatAmbandDif);
//    glPushMatrix(); //Transformations for each part of the wand
//    glTranslated(5.5, 6, -86);
//    glScaled(.1, .1, 1.2);
//    glutSolidCube(1);
//    glPopMatrix();
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    if (itemID == WAND) {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, wandEmiss);
//    }
//    else {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defEmiss);
//    }
//    glPushMatrix();
//    glTranslated(5.5, 6, -86.5);
//    glScaled(.11, .11, .3);
//    glutSolidCube(1);
//    glPopMatrix();
//    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defEmiss); //Reset emissive for all other objects
//
//    glPopMatrix();
//}
//
//void drawSelectionHat(float R, float G, float B) {
//    glColor3f(R, G, B);
//    //Set ambient, diffuse, specular, and shininess values for hat
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, hatMatAmbandDif);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, hatSpec);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, hatShin);
//    //Draw hat
//    glPushMatrix();
//    glTranslated(2.5, 6 + hatY, -86);
//    glRotated(hatAngle, 1, 0, 0);
//    glRotated(-90, 1, 0, 0);
//    glutSolidTorus(.2, .8, 25, 25);
//    glutSolidCone(.8, 3.5, 25, 25);
//    //Set the shininess/specular values back to default
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShin);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, purpleMatAmbandDif);
//    glTranslated(0, 0, 3.5);
//    glScaled(.2, .25, .25);
//    glutSolidDodecahedron();
//
//    glPopMatrix();
//}
//
//void drawFlashlight()
//{
//    //Transformations to position the flashlighta
//    glPushMatrix();
//    glTranslated(flX, flY, flZ);
//
//    //Transformations to draw the flashlight
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
//    glPushMatrix();
//    glRotated(180, 0, 1, 0);
//    glutSolidCone(.5, .5, 25, 25);
//    glPopMatrix();
//    
//    glPushMatrix();
//    glTranslated(0, 0, -.8);
//    glScaled(.3, .3, 1.2);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//void drawDoors(float R, float G, float B) {
//    //Door Left
//    glColor3f(R, G, B);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, woodMatAmbandDif);
//    glPushMatrix();
//    glTranslated(3.1 - doorX, 12.5, -32 + doorZ);
//    glRotated(-doorAngle, 0, 1, 0);
//    glRotated(90, 0, 1, 0);
//    glScaled(.5, 24, 5.8);
//    glutSolidCube(1);
//    glPopMatrix();
//    //Door Right
//    glPushMatrix();
//    glTranslated(8.9 + doorX, 12.5, -32 + doorZ);
//    glRotated(doorAngle, 0, 1, 0);
//    glRotated(-90, 0, 1, 0);
//    glScaled(.5, 24, 5.8);
//    glutSolidCube(1);
//    glPopMatrix();
//}
//
//void animateDoorOpen(int value) {
//    if (doorAngle < 90) {
//        doorAngle += .5;
//        doorX += .015;
//        doorZ += .016;
//    }
//    glutPostRedisplay();
//}
//
//void animateDoorClose(int value) {
//    if (doorAngle > 0) {
//        doorAngle -= .5;
//        doorX -= .015;
//        doorZ -= .016;
//    }
//    glutPostRedisplay();
//}
//
//void animateWand(int value) 
//{
//    if (wandX > -3) 
//    {
//        wandX -= .022;
//    }
//    if (wandY < 4) 
//    {
//        wandY += .03;
//    }
//    else
//    {
//        //Reaches Y limit when wand is directly over the hat 
//        //reaches Z and X limits slightly before, so overHat = true
//        //must be after the wandY if-statement
//        overHat = true;
//    }
//    if (wandZ < 1) 
//    {
//        wandZ += .03;
//    }
//    
//    glutPostRedisplay();
//}
//
//void animateWandBack(int value) {
//    overHat = false;
//    if (wandX < 0) {
//        wandX += .022;
//    }
//    if (wandY > 0) {
//        wandY -= .03;
//    }
//    if (wandZ > 0) {
//        wandZ -= .03;
//    }
//    glutPostRedisplay();
//}
//
//void animateHat(int value)
//{
//    if (hatAngle > -90) {
//        hatAngle -= .5;
//    }
//    if (hatY < 2) {
//        hatY += .01;
//    }
//    glutPostRedisplay();
//}
//
//void animateHatBack(int value)
//{
//    if (hatAngle < 0) {
//        hatAngle += .5;
//    }
//    if (hatY > 0) {
//        hatY -= .01;
//    }
//    glutPostRedisplay();
//}
//
////Sets the camera viewing position
//void setCameraView() 
//{
//   gluLookAt(eyeX, eyeY, eyeZ,
//             eyeX + sin(eyeAngle * PI/180), eyeY, eyeZ + cos(eyeAngle * PI/180),
//             0, 1, 0);
//}
//
////Determines the ID of the object the mouse has clicked 
//void getID(int x, int y) {
//    unsigned char pixel[3];
//    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
//    {
//        itemID = DOOR;
//        cout << "Door Selected" << endl;
//    }
//    else if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0)
//    {
//        itemID = WAND;
//        cout << "Wand selected" << endl;
//    }
//    else if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255)
//    {
//        itemID = HAT;
//        cout << "Hat selected" << endl;
//    }
//    else
//    {
//        itemID = 0;
//    }
//    isSelecting = false;
//    glutPostRedisplay();
//}
//
////Flashlight collision detection
//void collision(void)
//{
//    if (-10 <= eyeX && eyeX<= -8.0 && -75.0 <= eyeZ && eyeZ <= -64.0 && collActive)
//    {
//        cout << "Near flashlight" << endl;
//        collActive = false;
//        nearFL = true;
//    }
//}
//
////Enable text 
//void writeStrokeString(void* font, char* string)
//{
//    char* c;
//    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
//}
//
//void generateRandHouse()
//{
//    randHouse = (rand() % 4);
//    cout << houses[randHouse] << endl;
//}
//
//void runGuessingGame()
//{
//    glPushMatrix();
//    glTranslatef(-9.75, 30, -90);
//    glScalef(.005, .006, .005);
//    writeStrokeString(GLUT_STROKE_ROMAN, inst);
//    glPopMatrix();
//    if (submitted == true)       
//    {
//        if (guess == randHouse)
//        {
//            glPushMatrix();
//            glTranslatef(0.5, 20, -90);
//            glScalef(.006, .006, .006);
//            writeStrokeString(GLUT_STROKE_ROMAN, correct);
//            glPopMatrix();
//            glutPostRedisplay();
//        }
//        else
//        {
//            glPushMatrix();
//            glTranslatef(-1, 20, -90);
//            glScalef(.006, .006, .006);
//            writeStrokeString(GLUT_STROKE_ROMAN, incorrect);
//            glPopMatrix();
//            glutPostRedisplay();
//        }
//    }
//}
//
////Setup lighting
//void setupLighting(void)
//{
//    //Main lighting setup
//    glEnable(GL_LIGHTING);
//
//    glEnable(GL_NORMALIZE);
//
//    //Global ambient 
//    float globAmb[] = { gAmb, gAmb, gAmb, 1.0 };
//
//    //Set global properties of lighting
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //Enable 2 sided lighting
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); //Global ambient
//
//    //Properties for light0 (light in the hall)
//    float lightAmbLight0[] = { 50.0 / 255.0, 25.0 / 255.0, 0.0 / 255.0, 1.0 };
//    float lightDifAndSpecLight0[] = { 255.0 / 255.0, 119.0 / 255.0, 0.0 / 255.0, .2 };
//    float lightPosLight0[] = { light0posX, light0posY, light0posZ, 1.0 };
//    //Define properties for light0 
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbLight0);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpecLight0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpecLight0);
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosLight0);
//    //Enable for light0 in keyboard input function
//
//    //Properties for light1 
//    float lightAmbLight1[] = { 1.0, 1.0, 1.0, 1.0 };
//    float lightDifAndSpecLight1[] = { 1.0, 1.0, 1.0, 1.0 };
//    static float spotAngle = 10.0;
//    static float spotExponent = 2.0;
//    //Position defined and initialized in drawFlashlight
//    //Define properties for light1
//    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbLight1);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpecLight1);
//    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpecLight1);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
//    //Enable for light1 in keyboard input function
//
//
//}
//
////Draws the objects in the scene
//void drawObjects(void)
//{
//    //Color picking 
//    if (isSelecting)
//    {
//        drawWand(1.0, 0.0, 0.0);
//        drawDoors(0.0, 1.0, 0.0);
//        drawSelectionHat(0.0, 0.0, 1.0);
//    }
//    else
//    {
//        drawDoors(.2, .2, .2);
//        drawWand(.2, .2, .2);
//        drawSelectionHat(.2, .2, .2);
//    }
//
//    //Animation control
//    if (itemID == WAND) 
//    {
//        glutTimerFunc(.05, animateWand, 1);
//        runGuessingGame();
//    }
//    else
//    {
//        glutTimerFunc(.05, animateWandBack, 1);
//    }
//    if (itemID == DOOR) 
//    {
//        glutTimerFunc(.001, animateDoorOpen, 1);
//    }
//    else
//    {
//        glutTimerFunc(.001, animateDoorClose, 1);
//    }
//    if (overHat)
//    {
//        glutTimerFunc(.05, animateHat, 1);
//    }
//    else
//    {
//        glutTimerFunc(.05, animateHatBack, 1);
//    }
//
//    //Check if user is near flashlight
//    collision();
//
//    //Draw objects not using color picking
//    drawBridge();
//    drawCourtyard();
//    drawHall();
//    drawFurniture();
//    drawLightFixture();
//
//    glPushMatrix();
//    if (nearFL) {
//        glTranslated(eyeX, eyeY, eyeZ);
//        glRotated(eyeAngle, 0, 1, 0);
//        glTranslated(-eyeX, -eyeY, -eyeZ);
//        glTranslated(eyeX - 1 - flX, eyeY - flY - 1, eyeZ - flZ + 2);
//
//        float lightPosLight1[] = { flX, flY, flZ, 1.0 };
//        float spotDirection[] = { 0.0, 0.0, 1.0 };
//        //Define properties for light1
//
//        glLightfv(GL_LIGHT1, GL_POSITION, lightPosLight1);
//        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
//      
//    }
//    drawFlashlight();
//    glPopMatrix();
//}
//
////Drawing routine 
//void drawScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    //Enable depth testing
//    glEnable(GL_DEPTH_TEST);
//    //Set camera view
//    setCameraView();
//    //Setup lighting
//    setupLighting();
//
//    //Set specular and shininess for all items
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShin);
//
//
//    //Draw everything with unique colors but don't display if user isSelecting
//    if (isSelecting)
//    {
//        glDisable(GL_LIGHTING);
//        drawObjects();
//        getID(mouseX, mouseY);
//    }
//    //Draw everything normally
//    else
//    {
//        glEnable(GL_LIGHTING);
//        drawObjects();
//        glutSwapBuffers();
//    }
//}
//
////Initialization routine
//void setup(void)
//{
//    //Seed random number generator with time
//    srand(time(0));
//
//    //Set world background color
//    glClearColor(72.0/255.0, 52.0/255.0, 117.0/255.0, -21.0);
//}
//
////OpenGL window reshape routine.
//void resize(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    setViewMode();
//    glMatrixMode(GL_MODELVIEW);
//    height = h;
//    width = w;
//}
//
////Keyboard input processing
//void keyInput(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'G':
//        guess = 0;
//        submitted = true;
//        glutPostRedisplay();
//        break;
//    case 'H':
//        guess = 1;
//        submitted = true;
//        glutPostRedisplay();
//        break;
//    case 'R':
//        guess = 2;
//        submitted = true;
//        glutPostRedisplay();
//        break;
//    case 'S':
//        guess = 3;
//        submitted = true;
//        glutPostRedisplay();
//        break;
//    case 'L':
//        if (lightOn) {
//            glDisable(GL_LIGHT0);
//            lightOn = false;
//        }
//        else {
//            glEnable(GL_LIGHT0);
//            lightOn = true;
//        }
//        glutPostRedisplay();
//        break;
//    case 'f':
//        if (flOn)
//        {
//            glDisable(GL_LIGHT1);
//            flOn = false;
//        }
//        else
//        {
//            glEnable(GL_LIGHT1);
//            flOn = true;
//        }
//        glutPostRedisplay();
//        break;
//    case 'w':
//        if (itemID == WAND)
//        {
//            itemID = 0;
//        }
//        else
//        {
//            itemID = WAND;
//        }
//        glutPostRedisplay();
//        break;
//    case 'd':
//        if (itemID == DOOR)
//        {
//            itemID = 0;
//        }
//        else
//        {
//            itemID = DOOR;
//        }
//        glutPostRedisplay();
//        break;
//    case 's':
//        nearFL = true;
//        glutPostRedisplay();
//        break;
//    case '>':
//        gAmb = gAmb + 0.1;
//        glutPostRedisplay();
//        break;
//    case '<':
//        gAmb = gAmb - 0.1;
//        glutPostRedisplay();
//        break;
//    case 27:
//        exit(0);
//        break;
//    default:
//        break;
//    }
//}
//
////Speical keyboard input processing
//void specialkeyInput(int key, int x, int y)
//{
//    switch (key)
//    {
//    case GLUT_KEY_UP:
//        eyeX += stepSize * sin(eyeAngle * PI / 180);
//        eyeZ += stepSize * cos(eyeAngle * PI / 180);
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_DOWN:
//        eyeX -= stepSize * sin(eyeAngle * PI / 180);
//        eyeZ -= stepSize * cos(eyeAngle * PI / 180);
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_RIGHT:
//        eyeAngle -= turnSize;
//        glutPostRedisplay();
//        break;
//    case GLUT_KEY_LEFT:
//        eyeAngle += turnSize;
//        glutPostRedisplay();
//        break;
//    }
//}
//
////Mouse input processing
//void mouseInput(int button, int state, int x, int y) 
//{
//    if (button == GLUT_LEFT && state == GLUT_DOWN)
//    {
//        isSelecting = true;
//        mouseX = x;
//        mouseY = height - y;
//        glutPostRedisplay();
//    }
//
//    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//        
//        glutPostRedisplay();
//    }
//}
//
////Routine to output interaction instructions to the C++ window
//void printInteraction(void)
//{
//    cout << "   Interaction:" << endl;
//    cout << "       Use arrow keys to move around" << endl;
//    cout << "       Press d or click the doors to open" << endl;
//    cout << "       Press L to turn on the hall light" << endl;
//    cout << "       Click > to increase and < to decrease global ambient light" << endl;
//    cout << "       Walk near the flashlight to pick it up" << endl;
//    cout << "       Press f to turn the flashlight on or off" << endl;
//    cout << "       Press w or click the wand to start guessing game" << endl;
//    cout << "       Pres G, H, R, or S to select a house guess" << endl;
//    cout << "       Pres Esc to exit" << endl;
//}
//
////Main routine
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(1500, 1000);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Magic Castle");
//    setup();
//    printInteraction();
//    generateRandHouse();
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//    glutSpecialFunc(specialkeyInput);
//    glutMouseFunc(mouseInput);
//    glutMainLoop();
//
//    return 0;
//}