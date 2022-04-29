///***********************************************************
//*
//* Name: Nolan Willis
//*
//* Email: nwillis@syr.edu    
//*
//* Assignment: Final Project
//* 
//* Environment: Visual Studio Community 2022
//* 
//* Date submitted: 
//* 
//* References: None
//* 
//* Interactions: 
//      Press esc to exit 
//*
//************************************************************/

#include <iostream>

#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

#define _CRT_SECURE_NO_DEPRECATE

using namespace std;

//Global Variables------------------------------------------------------------------------

//Window size
int height, width;

//Mouse click coordinates
int mouseX, mouseY;

//Camera position values
float eyeX = -8, eyeY = 5.5, eyeZ = 0.0;
static float eyeAngle = 180;  //angle user is facing
static float stepSize = 2.0;  //step size
static float turnSize = 10.0; //degrees to turn

//Value to keep track of selecting state
bool isSelecting = false;

//Default selection ID
int itemID = 0;

//Selection ID for ignition button
int IGNID = 1;

//Global specular and shininess arrays for all objects
float materialSpec[] = { 1.0, 1.0, 1.0, 1.0 }, materialShin[] = { 50.0 };

//Text for light tree
char prestageText[] = "PRE-STAGE", stageText[] = "STAGE";

//Colored materials
//White
float whiteMatAmbandDif[] = { 1.0, 1.0, 1.0, 1.0 };
//Off-White
float offwhiteMatAmbandDif[] = { .8, .8, .8, 1.0 };
//Sky
float skyMatAmbandDif[] = { 146.0 / 255.0, 154.0 / 255.0, 167.0 / 255.0, 1.0 };
//Concrete
float concreteMatAmbandDif[] = { 179.0 / 255.0, 178.0 / 255.0, 173.0 / 255.0, 1.0 };
//Asphalt
float asphMatAmbandDif[] = { 49.0 / 255.0, 57.0 / 255.0, 66.0 / 255.0, 1.0 };
//Black
float blackMatAmbandDif[] = { 0, 0, 0, 1.0 };
//Off-black
float offblackMatAmbandDif[] = { 0.3, 0.3, 0.3, 1.0 };
//Red
float redMatAmbandDif[] = { 1.0, 0, 0, 1.0 };
//Yellow
float yellowMatAmbandDif[] = { 255.0 / 255.0, 255.0 / 255.0, 0.0 / 255, 1.0 };
//Green
float greenMatAmbandDif[] = { 20.0 / 255.0, 200.0 / 255.0, 0.0 / 255, 1.0 };
//Flame orange
float forangeMatAmbandDif[] = { 255.0 / 255.0, 200.0 / 255.0, 35.0 / 255, 1.0 };
//Rusted orange
float rorangeMatAmbandDif[] = { 217.0 / 255.0, 48.0 / 255.0, 20.0 / 255, 1.0 };
//Purple
float purpleMatAmbandDif[] = { 72.0 / 255.0, 52.0 / 255.0, 117.0 / 255.0, 1.0 };
//Blue
float blueMatAmbandDif[] = { 0.0 / 255.0, 37.0 / 255.0, 118.0 / 255.0, 1.0 };
//Grey
float greyMatAmbandDif[] = { .5, .5, .5, 1.0 };
//Glass
float glassMatAmbandDif[] = { .8, .8, .8, .8 };
//Global ambient values
float gAmb = 1.0;

//Quadric object
GLUquadricObj* qobj;

//Texture stuff
//Texture data array
static unsigned int texture[20];
//BitMapFile Struct
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char* data;
};

//Windshield bezier surface coords
static float bezcoords[6][4][3] =
{
    {{0.599999,-3.4,5}, {0.55,-2.6,5}, {0.55,-2.1,5}, {0.500001,-1.6,5}},
    {{-1.9,-0.6,3}, {-0.25,0,3}, {0.25,0,3}, {0.400001,-0.2,3}},
    {{-2.1,-0.5,1}, {-0.25,0,1}, {0.25,0,1}, {0.400001,-0.2,1}},
    {{-2.1,-0.6,-1}, {-0.25,0,-1}, {0.25,0,-1}, {0.400001,0,-1}},
    {{-1.9,-0.8,-3}, {-0.25,0,-3}, {0.25,0,-3}, {0.400001,0,-3}},
    {{0.499999,-3.9,-5}, {0.55,-3.4,-5}, {0.55,-2.7,-5}, {0.600001,-2,-5}}
};

//Boolean to keep track of cars launch status
bool carLaunch = false;

//Boolean to keep track of race start status
bool carStart = false;

//Boolean value that determines tracklight status
bool TLOn = false;

//Boolean value to keep track of time (day/night)
bool isDay = true;

//Speedometer animation values
float speedX = 0, speedY = 0;
float speedRot = 0;

//Tachometer animation values
float tachX = 0, tachY = 0;
float tachRot = 0;

//--------------------------------------------------------------------------------------

//Function that sets the view mode (frust)
void setViewMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 150);
    glMatrixMode(GL_MODELVIEW);
}

//Individual draw functions
void drawAsphalt() 
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
    glTranslated(-20.0, 0.0, 0.0);
    glScaled(40.0, 1.0, 1250.0);
    glNormal3f(0.0, -1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 50.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 50.0); glVertex3f(1, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void drawGrass()
{
    //Left
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(-120.0, 0.0, 0.0);
    glScaled(100.0, 0.0, 1250.0);
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(75.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(75.0, 75.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 75.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    //Right
    glPushMatrix();
    glTranslated(20.0, 0.0, 0.0);
    glScaled(100.0, 0.0, 1250.0);
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(75.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(75.0, 75.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 75.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void drawTrackBorder()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glEnable(GL_TEXTURE_2D);
    glNormal3f(0.0, -1.0, 0.0);
    glPushMatrix();
    glTranslated(-20.0, .1, 0.0);
    glScaled(3.0, 0.0, 1000.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 50.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 50.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslated(17.0, .1, 0.0);
    glScaled(3.0, 0.0, 1000.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 50.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 50.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void drawBarriers()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    //Left
    glNormal3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-20, 0.0, 0.0);
    glRotated(90, 0, 0, 1);
    glScaled(4, .75, 1000);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 1.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 1.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    //Center
    glNormal3f(-1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-.5, 0.0, 0.0);
    glRotated(90, 0, 0, 1);
    glScaled(4, .75, 1000);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 1.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 1.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    //Right
    glNormal3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(20, 0.0, 0.0);
    glRotated(90, 0, 0, 1);
    glScaled(4, .75, 1000);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(50.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(50.0, 1.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 1.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}
void drawStands()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    //Left
    glPushMatrix();
    glTranslated(-90, 5, -110);
    glRotated(145, 0, 0, 1);
    glScaled(50, .75, 70);
    glutSolidCube(1);
    glPopMatrix();
    //Right
    glPushMatrix();
    glTranslated(90, 5, -110);
    glRotated(35, 0, 0, 1);
    glScaled(50, .75, 70);
    glutSolidCube(1);
    glPopMatrix();
}
void drawCar(float R, float G, float B)
{
    //Dash
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslated(-8.75, 3.7, -2.43);
    glScaled(1.5, .75, .05);
    glNormal3f(0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(10.0, 0.0); glVertex3f(0, 1, 0);
    glTexCoord2f(10.0, 10.0); glVertex3f(1, 1, 0);
    glTexCoord2f(0.0, 10.0); glVertex3f(1, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Windscreen
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glassMatAmbandDif);
    glPushMatrix();
    glTranslated(-8.0, 4.56, -2.8);
    glRotated(90, 0, 1, 0);
    glRotated(-90, 0, 0, 1);
    glScaled(.2, .2, .146);
    glMapGrid2d(20.0, 0.0, 1.0, 20.0, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();

    //Power button
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, redMatAmbandDif);
    glColor3f(R, G, B);
    glPushMatrix();
    glTranslated(-7.6, 3.94, -2.4);
    glScaled(.08, .08, .03);
    glutSolidCube(1);
    glPopMatrix();
    
    //Guages
    //Center housing
    //Outer ring
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslated(-8.0, 4.2, -2.43);
    glEnable(GL_TEXTURE_2D);
    gluCylinder(qobj, .2, .2, .075, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //Background graphic
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glPushMatrix();
    glTranslated(-8.0, 4.2, -2.4);
    glEnable(GL_TEXTURE_2D);
    gluDisk(qobj, 0.0, .2, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //Dot
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, redMatAmbandDif);
    glPushMatrix();
    glTranslated(-8.0, 4.15, -2.39);
    gluDisk(qobj, 0.0, .015, 25, 25);
    glPopMatrix();
    //Arrow
    glNormal3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(-8.002 + speedX, 4.15 + speedY, -2.39);
    glRotated(speedRot, 0, 0, 1);
    glRotated(130, 0, 0, 1);
    glScaled(.005, .12, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    
    //Right housing
    //Outer ring
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslated(-7.6, 4.2, -2.43);
    glEnable(GL_TEXTURE_2D);
    gluCylinder(qobj, .1, .1, .075, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //Background graphic
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glPushMatrix();
    glTranslated(-7.6, 4.2, -2.4);
    glEnable(GL_TEXTURE_2D);
    gluDisk(qobj, 0.0, .1, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //Dot
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, redMatAmbandDif);
    glPushMatrix();
    glTranslated(-7.6, 4.21, -2.39);
    gluDisk(qobj, 0.0, .01, 25, 25);
    glPopMatrix();
    //Arrow
    glNormal3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(-7.602 + tachX, 4.205 + tachY, -2.39);
    glRotated(tachRot, 0, 0, 1);
    glRotated(130, 0, 0, 1);
    glScaled(.005, .06, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    //Left housing
    //Outer ring
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslated(-8.4, 4.2, -2.43);
    glEnable(GL_TEXTURE_2D);
    gluCylinder(qobj, .1, .1, .075, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //Background graphic
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glPushMatrix();
    glTranslated(-8.4, 4.2, -2.4);
    glEnable(GL_TEXTURE_2D);
    gluDisk(qobj, 0.0, .1, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
   
    // Wheel
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blueMatAmbandDif);
    glPushMatrix();
    glTranslated(-8, 4.1, -1.5);
    glutSolidTorus(.05, .3, 50, 50);
    glPopMatrix();
    // Center support
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, concreteMatAmbandDif);
    glPushMatrix();
    glTranslated(-8, 4.27, -1.5);
    glScaled(.075, .3, .075);
    glutSolidCube(1);
    glPopMatrix();
    // Left support
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, concreteMatAmbandDif);
    glPushMatrix();
    glTranslated(-8.1, 4.05, -1.5 );
    glRotated(120, 0, 0, 1);
    glScaled(.075, .3, .075);
    glutSolidCube(1);
    glPopMatrix();
    // Right support
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, concreteMatAmbandDif);
    glPushMatrix();
    glTranslated(-7.9, 4.05, -1.5);
    glRotated(-120, 0, 0, 1);
    glScaled(.075, .3, .075);
    glutSolidCube(1);
    glPopMatrix();

    //Sides
    //Left
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(-8.64, 3.7, -.9);
    glRotated(90, 0, 1, 0);
    glScaled(1.5, .75, .05);
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(2.0, 0.0); glVertex3f(0, 1, 0);
    glTexCoord2f(2.0, 2.0); glVertex3f(1, 1, 0);
    glTexCoord2f(0.0, 2.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-8.74, 4.45, -2.4);
    glRotated(90, 1, 0, 0);
    glScaled(.1, 1.75, 0);
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(2.0, 0.0); glVertex3f(0, 1, 0);
    glTexCoord2f(2.0, 2.0); glVertex3f(1, 1, 0);
    glTexCoord2f(0.0, 2.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    //Right
    glPushMatrix();
    glTranslated(-7.35, 3.7, -.9);
    glRotated(90, 0, 1, 0);
    glScaled(1.5, .75, .05);
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(2.0, 0.0); glVertex3f(0, 1, 0);
    glTexCoord2f(2.0, 2.0); glVertex3f(1, 1, 0);
    glTexCoord2f(0.0, 2.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-7.36, 4.45, -2.4);
    glRotated(90, 1, 0, 0);
    glScaled(.1, 1.75, 0);
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(2.0, 0.0); glVertex3f(0, 1, 0);
    glTexCoord2f(2.0, 2.0); glVertex3f(1, 1, 0);
    glTexCoord2f(0.0, 2.0); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE);
   
    //Hood
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
    glTranslated(-8.8, 4.45, -2.41);
    glNormal3f(0.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.053, 0, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(.5, 0, -7);
    glTexCoord2f(0.0, 1.0); glVertex3f(1, 0, -7);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.545, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Floor
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glPushMatrix();
    glTranslated(-10.2, .6, -4.0);
    glScaled(4.5, 0.0, 4.0);
    glNormal3f(0.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(5.0, 0.0); glVertex3f(0, 0, -1);
    glTexCoord2f(5.0, 5.0); glVertex3f(1, 0, -1);
    glTexCoord2f(0.0, 5.0); glVertex3f(1, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Wheels
    //Left
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offblackMatAmbandDif);
    glPushMatrix();
    glTranslated(-8.5, 4.4, -8.8);
    glRotated(90, 0, 1, 0);
    glutSolidTorus(.1, .3, 50, 50);
    glPopMatrix();
    //Right
    glPushMatrix();
    glTranslated(-7.6, 4.4, -8.8);
    glRotated(90, 0, 1, 0);
    glutSolidTorus(.1, .3, 50, 50);
    glPopMatrix();
}
void drawTrackLights()
{
    //Left poles
    for (int i = 0; i < 10; i++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyMatAmbandDif);
        glPushMatrix();
        glTranslated(-21, 18, -15 - (i * 100));
        glRotated(90, 1, 0, 0);
        gluCylinder(qobj, .2, .2, 18, 25, 25);
        glPopMatrix();
        glPushMatrix();
        glTranslated(-21.1, 18, -15 - (i * 100));
        glRotated(8, 0, 0, 1);
        glRotated(90, 0, 1, 0);
        gluCylinder(qobj, .2, .15, 10, 25, 25);
        glPopMatrix();
        glPushMatrix();
        glTranslated(-10.5, 19.5, -15 - (i * 100));
        glRotated(8, 0, 0, 1);
        glScaled(2, .2, .5);
        glutSolidCube(1);
        glPopMatrix();
        if (TLOn)
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
        }
        else
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glassMatAmbandDif);
        }
        glPushMatrix();
        glTranslated(-10.5, 19.4, -15 - (i * 100));
        glRotated(8, 0, 0, 1);
        glScaled(1, .2, .25);
        glutSolidCube(1);
        glPopMatrix();
    }

    //Right poles
    for (int i = 0; i < 10; i++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyMatAmbandDif);
        glPushMatrix();
        glTranslated(21, 18, -15 - (i * 100));
        glRotated(90, 1, 0, 0);
        gluCylinder(qobj, .2, .2, 18, 25, 25);
        glPopMatrix();
        glPushMatrix();
        glTranslated(21.1, 18, -15 - (i * 100));
        glRotated(-8, 0, 0, 1);
        glRotated(-90, 0, 1, 0);
        gluCylinder(qobj, .2, .15, 10, 25, 25);
        glPopMatrix();
        glPushMatrix();
        glTranslated(10.5, 19.5, -15 - (i * 100));
        glRotated(-8, 0, 0, 1);
        glScaled(2, .2, .5);
        glutSolidCube(1);
        glPopMatrix();
        if (TLOn)
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
        }
        else
        {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, glassMatAmbandDif);
        }
        glPushMatrix();
        glTranslated(10.5, 19.4, -15 - (i * 100));
        glRotated(-8, 0, 0, 1);
        glScaled(1, .2, .25);
        glutSolidCube(1);
        glPopMatrix();
    }
    
}

//Enables text, required in drawLightTree
void writeStrokeString(void* font, char* string)
{
    char* c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}
void drawLightTree()
{
    glPushMatrix(); //Transformations for the entire light fixture
    glTranslated(0, 3, -15);

    //Post
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blueMatAmbandDif);
    glPushMatrix();
    glTranslated(0, 5, -6.5);
    glRotated(90, 0, 0, 1);
    glScaled(15, .5, .5);
    glutSolidCube(1);
    glPopMatrix();

    //Stagging cluster
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackMatAmbandDif);
    glPushMatrix();
    glTranslated(0, 11.45, -6.4);
    glScaled(3, 2.7, .2);
    glutSolidCube(1);
    glPopMatrix();
    //Pre-Stage Sign
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyMatAmbandDif);
    glPushMatrix();
    glTranslated(0, 12.5, -6.2);
    glScaled(3, .5, .1);
    glutSolidCube(1);
    glPopMatrix();
    //Text
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glTranslatef(-1.15, 12.25, -6.1);
    glScalef(.003, .003, .003);
    writeStrokeString(GLUT_STROKE_ROMAN, prestageText);
    glPopMatrix();
    //Pre-Stage Bulbs Right
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offwhiteMatAmbandDif);
    glPushMatrix();
    glTranslated(.6, 11.8, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.1, 11.8, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    //Pre-Stage Bulbs Left
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
    glPushMatrix();
    glTranslated(-.6, 11.8, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1.1, 11.8, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    //Stage Sign
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyMatAmbandDif);
    glPushMatrix();
    glTranslated(0, 11.15, -6.2);
    glScaled(3, .5, .1);
    glutSolidCube(1);
    glPopMatrix();
    //Text
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glTranslatef(-.7, 10.95, -6.1);
    glScalef(.003, .003, .003);
    writeStrokeString(GLUT_STROKE_ROMAN, stageText);
    glPopMatrix();
    //Stage Bulbs Right
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offwhiteMatAmbandDif);
    glPushMatrix();
    glTranslated(.6, 10.5, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.1, 10.5, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    //Stage Bulbs Left
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forangeMatAmbandDif);
    glPushMatrix();
    glTranslated(-.6, 10.5, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1.1, 10.5, -6.3);
    glutSolidSphere(.2, 50, 50);
    glPopMatrix();

    //Right cluster
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackMatAmbandDif);
    glPushMatrix();
    glTranslated(.8, 6.7, -7);
    glRotated(35, 0, 1, 0);
    glScaled(1.5, 6, .5);
    glutSolidCube(1);
    glPopMatrix();
    //Right Bulbs
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offwhiteMatAmbandDif);
    glPushMatrix();
    glTranslated(.9, 8.8, -6.9);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(.9, 7.7, -6.9);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(.9, 6.6, -6.9);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offwhiteMatAmbandDif);
    glPushMatrix();
    glTranslated(.9, 5.5, -6.9);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offwhiteMatAmbandDif);
    glPushMatrix();
    glTranslated(.9, 4.4, -6.9);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();

    //Left cluster
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackMatAmbandDif);
    glPushMatrix();
    glTranslated(-.8, 6.7, -7);
    glRotated(-35, 0, 1, 0);
    glScaled(1.5, 6, .5);
    glutSolidCube(1);
    glPopMatrix();
    //Left Bulbs
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellowMatAmbandDif);
    glPushMatrix();
    glTranslated(-1, 8.8, -6.5);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1, 7.7, -6.5);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1, 6.6, -6.5);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greenMatAmbandDif);
    glPushMatrix();
    glTranslated(-1, 5.5, -6.5);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, redMatAmbandDif);
    glPushMatrix();
    glTranslated(-1, 4.4, -6.5);
    glutSolidSphere(.4, 50, 50);
    glPopMatrix();
   
    glPopMatrix();
}

//Individual animation functions
//Launch car
void animateCarLaunch(int value)
{
    if (eyeZ > -950) 
    {
        eyeZ += -5;
    }
}

void animateSpeedometer(int value)
{
    if (speedRot > -230)
    {
        speedRot -= .5;
        speedX += .000025;
        speedY += .00001;
    }
}

void animateTachometer(int value)
{
    if (tachRot > -190)
    {
        tachRot -= 1;
        tachX += .000025;
        tachY += .000025;
    }  
}

void animateTachometerIdle(int value)
{
    if (tachRot > -10)
    {
        tachRot -= .25;
        tachX += .000025;
        tachY += .000025;
    }
}

void animateSpeedometerDec(int value)
{
    if (speedRot < 0)
    {
        speedRot += .5;
        speedX -= .000025;
        speedY -= .00001;
    }
}

void animateTachometerDec(int value)
{
    if (tachRot < 0)
    {
        tachRot += 1;
        tachX -= .000025;
        tachY -= .00005;
    }
}

void animateTachometerIdleDec(int value)
{
    if (tachRot < -10)
    {
        tachRot += 1;
        tachX -= .000025;
        tachY -= .000025;
    }
}

//Function that manages animation
void animate()
{
    if (carLaunch)
    {
        /*glutTimerFunc(.05, animateCarLaunch, 1);*/
        glutTimerFunc(.02, animateSpeedometer, 1);
        glutTimerFunc(.02, animateTachometer, 1);
    }
    else
    {
        glutTimerFunc(.02, animateSpeedometerDec, 1);
        glutTimerFunc(.02, animateTachometerIdleDec, 1);
    }
    
    if (carStart)
    {
        glutTimerFunc(.02, animateTachometerIdle, 1);
    }
    else
    {
        glutTimerFunc(.02, animateTachometerDec, 1);
    }

    glutPostRedisplay();
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
    if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255)
    {
        itemID = IGNID; 
    }
    else
    {
        itemID = 0;
    }
    isSelecting = false;
    glutPostRedisplay();
}

//Setup lighting
void setupLighting(void)
{
    //Properties for track lights
    float lightAmbLight0[] = { 255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0, 1.0 };
    float lightDifAndSpecLight0[] = { 255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0, 1.0 };
    static float spotAngle = 20.0;
    static float spotExponent = 2.0;
    //Define properties for light0 
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpecLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpecLight0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
    glEnable(GL_LIGHT0);
  
   
}

//Menu
//Menu controllers
void frontMenu(int value)
{
    glutPostRedisplay();
}
void timeMenu(int value)
{
    if (value == 1) {
        gAmb = 1;
        isDay = true;
    }
    if (value == 2) {
        gAmb = .3;
        isDay = false;
    }
    glutPostRedisplay();
}
// Controller for moon menu (small/medium/large moon size)
void lightsMenu(int value)
{
    if (value == 1) {
        TLOn = true;
    }
    if (value == 2) {
        TLOn = false;
    }
    glutPostRedisplay();
}
//Main menu function
void drawPopupMenu(void)
{
    int timeSubMenu;
    timeSubMenu = glutCreateMenu(timeMenu);
    glutAddMenuEntry("Day", 1);
    glutAddMenuEntry("Night", 2);

    int lightsSubMenu;
    lightsSubMenu = glutCreateMenu(lightsMenu);
    glutAddMenuEntry("On", 1);
    glutAddMenuEntry("Off", 2);

    glutCreateMenu(frontMenu);
    glutAddSubMenu("Time", timeSubMenu);
    glutAddSubMenu("Track Lights", lightsSubMenu);
   
    // The menu is triggered by the right mouse button.
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Function to get BMP data
BitMapFile* getBMPData(string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;

    //Read input file name.
    ifstream infile(filename.c_str(), ios::binary);

    //Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char*)&offset, 4);

    //Get the header size of the bitmap.
    infile.read((char*)&headerSize, 4);

    //Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read((char*)&bmp->sizeX, 4);
    infile.read((char*)&bmp->sizeY, 4);

    //Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];

    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char*)bmp->data, size);

    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i + 2];
        bmp->data[i + 2] = temp;
    }

    return bmp;
}

//Function that loads all BMP files
void loadTextures()
{
    //Storage for BMP file data
    BitMapFile* image[20];

    //Textures
    image[0] = getBMPData("Textures/carbfib2.bmp");
    image[1] = getBMPData("Textures/asphalt.bmp");
    image[2] = getBMPData("Textures/metal.bmp");
    image[3] = getBMPData("Textures/bluecarpaint.bmp");
    image[4] = getBMPData("Textures/grass.bmp");
    image[5] = getBMPData("Textures/redrubber.bmp");
    image[6] = getBMPData("Textures/hatchedmetalsheet.bmp");
    image[7] = getBMPData("Textures/speedometer.bmp");
    image[8] = getBMPData("Textures/tachometer.bmp");
    image[9] = getBMPData("Textures/fuel.bmp");
    image[10] = getBMPData("Textures/concrete.bmp");

    //Carbon-fiber index[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);

    //Asphalt index[1]
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);

    //Metal sheet index[2]
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[2]->sizeX, image[2]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);

    //Blue car paint index[3]
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[3]->sizeX, image[3]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);

    //Grass index[4]
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[4]->sizeX, image[4]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[4]->data);

    //Red-rubber index[5]
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[5]->sizeX, image[5]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[5]->data);

    //Hatched metal sheet index[6]
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[6]->sizeX, image[6]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[6]->data);

    //Speedometer index[7]
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[7]->sizeX, image[7]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[7]->data);

    //Tachometer index[8]
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[8]->sizeX, image[8]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[8]->data);

    //Fuel index[9]
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[9]->sizeX, image[9]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[9]->data);

    //Concrete index[10]
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[10]->sizeX, image[10]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[10]->data);
}

//Draws the objects in the scene
void drawObjects(void)
{
    //Draw everything with unique colors but don't display, if user isSelecting
    if (isSelecting)
    {
        glDisable(GL_LIGHTING);
        drawCar(0.0, 0.0, 1.0);
        getID(mouseX, mouseY);
    }
    //Draw everything normally otherwise
    else
    {
        //glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        //Draw objects not using color picking
        drawAsphalt();
        drawTrackBorder();
        drawTrackLights();
        drawBarriers();
        drawGrass();
        drawLightTree();
        drawCar(1.0, 0.0, 0.0);
        glutSwapBuffers();
    }

    //Selection handler
    if (itemID == IGNID)
    {
        if (!carStart)
        {
            carStart = true;
            itemID = 0;
            cout << "   Engine started!" << endl;
        }
        else
        {
            carStart = false;
            carLaunch = false;
            itemID = 0;
            cout << "   Engine off" << endl;
        }
    }
}

//Main drawing routine 
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    //Set camera view
    setCameraView();
    
    //Enable lighting
    //Global ambient 
    float globAmb[] = { gAmb, gAmb, gAmb, 1.0 };
    //Set global properties of lighting
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //Enable 2 sided lighting
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); //Global ambient

    //Spotlight direction for track lights
    /*glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotDirection);*/
    setupLighting();
    
    //Set position of individual lights
    float lightPosLight0[] = { -10.5, 5, -15, 1.0 };
    float spotDirection[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosLight0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    
    //Set specular and shininess for all items
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShin);
    
    //Draw objects in scene
    drawObjects();
    
    //Start animation
    animate();
}

//Initialization routine
void setup(void)
{
    //Set world background color
    glClearColor(146.0 / 255.0, 154.0 / 255.0, 167.0 / 255.0, -500.0);

    //Seed random number generator with time
    srand(time(0));

    glEnable(GL_NORMALIZE);

    //Enable quadrics
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, true);

    //Enable Textures
    //Register texture index array.
    glGenTextures(20, texture);
    //Apply textures
    loadTextures();
    //How textures combine with color
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //Enable bezier surfaces
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, bezcoords[0][0]);
    glEnable(GL_MAP2_VERTEX_3);

    //Enable blending
    glEnable(GL_BLEND);
    //Blending properties
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enable popup menu
    drawPopupMenu();
}

//OpenGL window reshape routine.
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
    case 'r':
        carLaunch = false;
        eyeZ = 0;
        glutPostRedisplay();
        break;
    case'w':
        if (!carLaunch && carStart)
        {
            carLaunch = true;
        }
        else
        {
            carLaunch = false;
        }
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
    case GLUT_KEY_UP:
        eyeX += stepSize * sin(eyeAngle * PI / 180);
        eyeZ += stepSize * cos(eyeAngle * PI / 180);
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        eyeX -= stepSize * sin(eyeAngle * PI / 180);
        eyeZ -= stepSize * cos(eyeAngle * PI / 180);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        eyeAngle -= turnSize;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        eyeAngle += turnSize;
        glutPostRedisplay();
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
    cout << "   Interaction:" << endl;
    cout << "       Use arrow keys to move around" << endl;
    cout << "       Press d or click the doors to open" << endl;
    cout << "       Press L to turn on the hall light" << endl;
    cout << "       Click > to increase and < to decrease global ambient light" << endl;
    cout << "       Walk near the flashlight to pick it up" << endl;
    cout << "       Press f to turn the flashlight on or off" << endl;
    cout << "       Press w or click the wand to start guessing game" << endl;
    cout << "       Pres G, H, R, or S to select a house guess" << endl;
    cout << "       Pres Esc to exit" << endl;
}

//Main routine
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1500, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Drag Racer");
    setup();
    printInteraction();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialkeyInput);
    glutMouseFunc(mouseInput);
    glutMainLoop();

    return 0;
}