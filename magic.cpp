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
static float eyeX = 6, eyeY = 8, eyeZ = 2;
static float eyeAngle = 0;  //angle facing
static float stepSize = 5.0;  //step size
static float turnSize = 10.0; //degrees to turn

//Value to keep track of selecting state
bool isSelecting = false;

//Value to keep track of the last selected item
int itemID = 0;

//Door id for selecting
int DOOR = 1;

//Value to keep track of door angle
float doorAngle = 0;

//Values to keep track of door x and z
float doorX = 0, doorZ = 0;

//Open/close value of door
int isDoorOpen = 0;

//Global specular and shininess arrays for all objects
float materialSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float materialShin[] = { 50.0 };

//Position of light0
float light0posX = 6.0, light0posY = 40.0, light0posZ = -5.0;

//Colored materials for lighting
//Stone: used on the courtyard and bridge
float stoneMatAmbandDif[] = { 101.0 / 255.0, 102.0 / 255.0, 105 / 255.0, 1.0 };
//Sandstone: used on outdoor walls and railings
float sandstoneMatAmbandDif[] = { 114.0 / 255.0, 107.0 / 255.0, 82.0 / 255.0, 1.0 };
//Wood: used on furniture and 
float woodMatAmbandDif[] = { 70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0, 1.0 };
//White
float whiteMatAmbandDif[] = { 1.0, 1.0, 1.0, 1.0 };

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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
    glPushMatrix();
    glTranslated(6, 0, -6.5);
    glScaled(5, 1, 12);
    glutSolidCube(1);
    glPopMatrix();
    //Right railing
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
    glPushMatrix();
    glTranslated(8.5, 1, -6);
    glScaled(.5, 2, 12);
    glutSolidCube(1);
    glPopMatrix();
    //Left railing
    glPushMatrix();
    glTranslated(3.5, 1, -6);
    glScaled(.5, 2, 12);
    glutSolidCube(1);
    glPopMatrix();
}

void drawCourtyard() 
{
    //Floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
    glPushMatrix();
    glTranslated(6, 0, -22);
    glScaled(50, 1, 20);
    glutSolidCube(1);
    glPopMatrix();
    //Right front railing
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
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
  
}

void drawHall()
{
    //Right wall
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sandstoneMatAmbandDif);
    glPushMatrix();
    glTranslated(22.5, 20, -62);
    glScaled(3, 40, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Left wall
    glPushMatrix();
    glTranslated(-11.5, 20, -62);
    glScaled(3, 40, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Right roof
    glPushMatrix();
    glTranslated(15, 61, -62);
    glRotated(20, 0, 0, 1);
    glScaled(3, 50, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Left roof
    glPushMatrix();
    glTranslated(-4, 61, -62);
    glRotated(-20, 0, 0, 1);
    glScaled(3, 50, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Center beam for roof
    glPushMatrix();
    glTranslated(5.5, 85, -62);
    glRotated(45, 0, 0, 1);
    glScaled(3.2, 3.2, 60);
    glutSolidCube(1);
    glPopMatrix();
    //Door frame right
    glPushMatrix();
    glTranslated(21.5, 18, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 40, 19.5);
    glutSolidCube(1);
    glPopMatrix();
    //Door frame left
    glPushMatrix();
    glTranslated(-9.5, 18, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 40, 19.5);
    glutSolidCube(1);
    glPopMatrix();
    //Door frame top
    glPushMatrix();
    glTranslated(6, 32, -32);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 15, 15);
    glutSolidCube(1);
    glPopMatrix();
    //Facade front
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslated(-4.5, 38, -32);
    glBegin(GL_POLYGON);
    glVertex3f(-9, 0, 0);
    glVertex3f(10, 48, 0);
    glVertex3f(29, 0, 0);
    glEnd();
    glPopMatrix();
    //Facade back
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslated(-4.5, 38, -92);
    glBegin(GL_POLYGON);
    glVertex3f(-9, 0, 0);
    glVertex3f(10, 48, 0);
    glVertex3f(29, 0, 0);
    glEnd();
    glPopMatrix();
    //Floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stoneMatAmbandDif);
    glPushMatrix();
    glTranslated(5, 0, -62);
    glScaled(35, 1, 60);
    glutSolidCube(1);
    glPopMatrix();
}

void drawFurniture()
{
    //Table 1
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, woodMatAmbandDif);
    glPushMatrix();
    glTranslated(-5, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 1
    glPushMatrix();
    glTranslated(-5, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 1
    glPushMatrix();
    glTranslated(-6.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 1
    glPushMatrix();
    glTranslated(-6.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 1
    glPushMatrix();
    glTranslated(-3.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 1
    glPushMatrix();
    glTranslated(-3.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    

    //Table 2
    glPushMatrix();
    glTranslated(2, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 2
    glPushMatrix();
    glTranslated(2, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 2
    glPushMatrix();
    glTranslated(.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 2
    glPushMatrix();
    glTranslated(.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 2
    glPushMatrix();
    glTranslated(3.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 2
    glPushMatrix();
    glTranslated(3.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 3
    glPushMatrix();
    glTranslated(10, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 3
    glPushMatrix();
    glTranslated(10, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 3
    glPushMatrix();
    glTranslated(8.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 3
    glPushMatrix();
    glTranslated(8.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 3
    glPushMatrix();
    glTranslated(11.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 3
    glPushMatrix();
    glTranslated(11.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 4
    glPushMatrix();
    glTranslated(17, 4, -60);
    glScaled(3, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Table beam 4
    glPushMatrix();
    glTranslated(17, 2, -60);
    glRotated(90, 0, 0, 1);
    glScaled(4, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench 4
    glPushMatrix();
    glTranslated(15.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Left bench beam 4
    glPushMatrix();
    glTranslated(15.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench 4
    glPushMatrix();
    glTranslated(18.5, 2, -60);
    glScaled(1.5, .5, 30);
    glutSolidCube(1);
    glPopMatrix();
    //Right bench beam 4
    glPushMatrix();
    glTranslated(18.5, 1, -60);
    glRotated(90, 0, 0, 1);
    glScaled(1.5, .25, 30);
    glutSolidCube(1);
    glPopMatrix();

    //Table 5
    glPushMatrix();
    glTranslated(5.5, 5, -87);
    glRotated(90, 0, 1, 0);
    glScaled(3, .5, 20);
    glutSolidCube(1);
    glPopMatrix();
}

void drawDoors(float R, float G, float B) {
    //Door Left
    glColor3f(R, G, B);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, woodMatAmbandDif);
    glPushMatrix();
    glTranslated(3.1 - doorX, 12.5, -32 + doorZ);
    glRotated(-doorAngle, 0, 1, 0);
    glRotated(90, 0, 1, 0);
    glScaled(.5, 24, 5.8);
    glutSolidCube(1);
    glPopMatrix();
    //Door Right
    glPushMatrix();
    glTranslated(8.9 + doorX, 12.5, -32 + doorZ);
    glRotated(doorAngle, 0, 1, 0);
    glRotated(-90, 0, 1, 0);
    glScaled(.5, 24, 5.8);
    glutSolidCube(1);
    glPopMatrix();
}

void animateDoorOpen(int value) {
    if (doorAngle < 90) {
        doorAngle += .5;
        doorX += .016;
        doorZ += .012;
    }
    glutPostRedisplay();
}

void animateDoorClose(int value) {
    if (doorAngle > 0) {
        doorAngle -= .5;
        doorX -= .016;
        doorZ -= .012;
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
    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        itemID = DOOR;
        cout << "Door Selected" << endl;
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
    if (isSelecting)
    {
        drawDoors(0.0, 1.0, 0.0);
    }
    else
    {
        drawDoors(70.0 / 255.0, 50.0 / 255.0, 34.0 / 255.0);
    }

    if (itemID == DOOR) {
        glutTimerFunc(.001, animateDoorOpen, 1);
    }
    else
    {
        glutTimerFunc(.001, animateDoorClose, 1);
    }
    
    //Draw sphere at location of light0
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteMatAmbandDif);
    glTranslated(light0posX, light0posY, light0posZ);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();


    drawBridge();
    drawCourtyard();
    drawHall();
    drawFurniture();

}

//Drawing routine 
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //Set camera view
    setCameraView();

    //Set specular and shininess for all items
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShin);


    //Draw everything with unique colors but don't display if user isSelecting
    if (isSelecting)
    {
        glDisable(GL_LIGHTING);
        drawObjects();
        getID(mouseX, mouseY);
    }
    //Draw everything normally
    else
    {
        glEnable(GL_LIGHTING);
        drawObjects();
        glutSwapBuffers();
    }
}

// Initialization routine
void setup(void)
{
    //Main lighting setup
    glEnable(GL_LIGHTING);

    glEnable(GL_NORMALIZE);

    float lightAmbLight0[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpecLight0[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPosLight0[] = { light0posX, light0posY, light0posZ, 1.0 };
    float globAmb[] = { 0.0, 0.0, 0.0, 1.0 };

    //Define properties for light0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpecLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpecLight0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosLight0);

    //Enable light0
    glEnable(GL_LIGHT0);

    //Set global properties of lighting
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //Enable 2 sided lighting
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //Global ambient
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); //Global ambient

    //Set world color
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
    case 'o':
        if (isDoorOpen == 0)
        {
            isDoorOpen = 1;
        }
        else
        {
            isDoorOpen = 0;
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
        isSelecting = true;
        mouseX = x;
        mouseY = height - y;
        glutPostRedisplay();
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        
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