/*
 Updated by Bounif Moncif on 30/12/2015.
 Copyright 2015 Cassio Diego Campos. All rights reserved.
 */

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

//Variables globales définie

#define ESC 27
#define SPACE 32
#define BASE_HEIGHT 4.0/2
#define BASE_RADIUS 1.0/2
#define TETE_HEIGHT 1.25/2
#define TETE_RADIUS 0.75/2
#define OEIL_LEVEL 0.75/2
#define NEZ_LENGTH 0.5/2
#define BRAS_HEIGHT 2.0/2
#define BRAS_WIDTH 0.5/2
#define AVANT_BRAS_HEIGHT 1.25/2
#define AVANT_BRAS_WIDTH 0.5/2
#define ARM_TRANSLATION 0.22/2
#define alpha 0.0
#define pi 3.14159265

// Vecteurs qui representent la direction de la camera
GLfloat lx=0.0f,lz=-1.0f;

// Position X et Z de la camera
GLfloat z=10.0f;
GLfloat tzg = 0.2;
GLfloat angle = 0.0f;
GLfloat trb = -30.0f;

// Positionnement du robot qui sera manipulé par les fonctions claviers
static GLfloat theta[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLUquadricObj *p;
GLfloat x = 0.0;
GLfloat y = 0.0;
GLfloat xpos = 0.0;
GLfloat ypos = 0.0;
GLfloat zpos = 0.0;

// Composant des matériaux
GLfloat ambient[3];
GLfloat diffuse[3];
GLfloat specular[3];
GLfloat shiness[] = {50.0f};

// Largeur et hauteur de la fenetre
GLfloat width = 1000;
GLfloat height = 650;

// Couleur qui sera manipulé par les fonctions claviers
GLfloat Acolor1 = 0.5;
GLfloat Acolor2 = 0.3;
GLfloat Acolor3 = 0.3;

GLfloat Dcolor1 = 0.1;
GLfloat Dcolor2 = 0.1;
GLfloat Dcolor3 = 0.0;

GLfloat Scolor1 = 0.7;
GLfloat Scolor2 = 0.9;
GLfloat Scolor3 = 0.5;

int state = 0;

void baseRobot (void) {
    double angle, angleInc;
    angle = pi / 180;
    angleInc = angle;
    
    glPushMatrix();
        ambient[0] = Acolor1; ambient[1] = Acolor2; ambient[2] = Acolor3;
        diffuse[0] = Dcolor1; diffuse[1] = Dcolor2; diffuse[2] = Dcolor3;
        specular[0] = Scolor1; specular[1] = Scolor2; specular[2] = Scolor3;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glRotatef (-90.0, 1.0, 0.0, 0.0);
        gluQuadricDrawStyle(p, GLU_FILL);
        gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
        gluQuadricDrawStyle (p, GLU_FILL);
        glTranslatef (0.0, BASE_HEIGHT, 0.0);
        glRotatef (-90.0, 1.0, 0.0, 0.0);
        gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
        glTranslatef (0.0, 0.0, -BASE_HEIGHT);
        gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
    glPopMatrix();
}


void couRobot (void) {
    glPushMatrix();
        ambient[0] = Acolor1; ambient[1] = Acolor2; ambient[2] = Acolor3;
        diffuse[0] = Dcolor1; diffuse[1] = Dcolor2; diffuse[2] = Dcolor3;
        specular[0] = Scolor1; specular[1] = Scolor2; specular[2] = Scolor3;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glTranslatef(0.0, BASE_HEIGHT, 0.0);
        glRotatef (-90.0, 1.0, 0.0, 0.0);
        gluQuadricDrawStyle(p, GLU_FILL);
        gluCylinder (p, TETE_RADIUS/2, TETE_RADIUS/2, TETE_HEIGHT, 8, 6);
    glPopMatrix();
}

void teteRobot (void)
{
    glPushMatrix();
        ambient[0] = Acolor1; ambient[1] = Acolor2; ambient[2] = Acolor3;
        diffuse[0] = Dcolor1; diffuse[1] = Dcolor2; diffuse[2] = Dcolor3;
        specular[0] = Scolor1; specular[1] = Scolor2; specular[2] = Scolor3;

    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glRotatef (-90.0, 1.0, 0.0, 0.0);
        gluQuadricDrawStyle(p, GLU_FILL);
        gluCylinder (p, TETE_RADIUS, TETE_RADIUS, TETE_HEIGHT, 20, 20);
    
        glPushMatrix();
            gluDisk (p, 0.0, TETE_RADIUS, 20, 20);
            glTranslatef (0.0, 0.0, TETE_HEIGHT);
            gluDisk (p, 0.0, TETE_RADIUS, 20, 20);
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef (0.25, -TETE_RADIUS+0.12, OEIL_LEVEL);
            ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
            diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
            specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;
    
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
            gluQuadricDrawStyle(p, GLU_FILL);
            gluSphere (p, 0.125, 6, 6);
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef (-0.25, -TETE_RADIUS+0.12, OEIL_LEVEL);
            ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
            diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
            specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;
    
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
            gluQuadricDrawStyle(p, GLU_FILL);
            gluSphere (p, 0.125, 6, 6);
        glPopMatrix();
    
        glPushMatrix();
            ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
            diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
            specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;
    
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
            glTranslatef(0.0, -TETE_RADIUS, NEZ_LENGTH);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            gluQuadricDrawStyle(p, GLU_FILL);
            gluCylinder(p, 0.07, 0, NEZ_LENGTH, 8,6);
        glPopMatrix();
    glPopMatrix();
}

void brasDroit(void)
{
    glPushMatrix();
        ambient[0] = Acolor1; ambient[1] = Acolor2; ambient[2] = Acolor3;
        diffuse[0] = Dcolor1; diffuse[1] = Dcolor2; diffuse[2] = Dcolor3;
        specular[0] = Scolor1; specular[1] = Scolor2; specular[2] = Scolor3;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glTranslatef(0.0, 0.5 * BRAS_HEIGHT, ARM_TRANSLATION);
        glScalef(BRAS_WIDTH, BRAS_HEIGHT, BRAS_WIDTH);
        glutSolidCube(1.0);
    glPopMatrix();
}

void brasGauche(void)
{
    glPushMatrix();
        ambient[0] = Acolor1; ambient[1] = Acolor2; ambient[2] = Acolor3;
        diffuse[0] = Dcolor1; diffuse[1] = Dcolor2; diffuse[2] = Dcolor3;
        specular[0] = Scolor1; specular[1] = Scolor2; specular[2] = Scolor3;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glTranslatef(0.0, 0.5 * BRAS_HEIGHT, -ARM_TRANSLATION);
        glScalef(BRAS_WIDTH, BRAS_HEIGHT, BRAS_WIDTH);
        glutSolidCube(1.0);
    glPopMatrix();
}

void avantBrasDroit(void)
{
    glPushMatrix();
    ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
    diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
    specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glTranslatef(0.0, 0.5 * AVANT_BRAS_HEIGHT, ARM_TRANSLATION);
        glScalef(AVANT_BRAS_WIDTH, AVANT_BRAS_HEIGHT, AVANT_BRAS_WIDTH);
        glutSolidCube(1.0);
    glPopMatrix();
}

void avantBrasGauche(void)
{
    glPushMatrix();
    ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0;
    diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
    specular[0] = 0.5; specular[1] = 0.5; specular[2] = 0.5;
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glTranslatef(0.0, 0.5 * AVANT_BRAS_HEIGHT, -ARM_TRANSLATION);
        glScalef(AVANT_BRAS_WIDTH, AVANT_BRAS_HEIGHT, AVANT_BRAS_WIDTH);
        glutSolidCube(1.0);
    glPopMatrix();
}


void init1(void)
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {150.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat white_light[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat lmodel_ambient[] = {1.0, 1.0, 0.0, 1.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(  x, 2.5f, z, x+lx, 2.6f, z+lz, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
        ambient[0] = 0.1; ambient[1] = 0.2; ambient[2] = 0.1;
        diffuse[0] = 0.5; diffuse[1] = 0.7; diffuse[2] = 0.5;
        specular[0] = 0.5; specular[1] = 0.7; specular[2] = 0.1;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shiness);
    
        glBegin(GL_POLYGON);
            glVertex3f(10.0, 0.0, 10.0);
            glVertex3f(10.0, 0.0, -10.0);
            glVertex3f(-10.0, 0.0, -10.0);
            glVertex3f(-10.0, 0.0, 10.0);
            glVertex3f(10.0, 0.0, 10.0);
        glEnd();
    
    glPopMatrix();
    
    glTranslatef (xpos, ypos, zpos);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    baseRobot();
    couRobot();
    
    glPushMatrix();
        glTranslatef(0.0, BASE_HEIGHT + TETE_HEIGHT/2, 0.0);
        glRotatef(theta[2], 1.0, 0.0, 0.0);
        glRotatef(theta[1], 0.0, 1.0, 0.0);
        teteRobot();
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
        glRotatef(180.0, 0.0, 0.0, 1.0);
        glRotatef(270.0, 0.0, 1.0, 0.0);
        glRotatef(theta[4], 0.0, 0.0, 1.0);
        brasDroit();
        glTranslatef(0.0, BRAS_HEIGHT, 0.0);
        glRotatef(0.0, 0.0, 0.0, 180.0);
        glRotatef(theta[6], 0.0, 0.0, 1.0);
        avantBrasDroit();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
        glRotatef(180.0, 0.0, 0.0, 1.0);
        glRotatef(270.0, 0.0, 1.0, 0.0);
        glRotatef(theta[3], 0.0, 0.0, 1.0);
        brasGauche();
        glTranslatef(0.0, BRAS_HEIGHT, 0.0);
        glRotatef(0.0, 0.0, 0.0, 180.0);
        glRotatef(theta[5], 0.0, 0.0, 1.0);
        avantBrasGauche();
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void update(int value)
{
    theta[0] += 20.0;


    glutPostRedisplay();
    glutTimerFunc(80, update, 0);
}

void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case '=': theta[1] += 5.0;
            if (theta[1] > 90.0)
                theta[1] = 90.0;
            break;
            
        case '-': theta[1] -= 5.0;
            if (theta[1] < -90.0)
                theta[1] = -90.0;
            break;
            
        case 'o': theta[2] += 5.0;
            if (theta[2] > 45.0)
                theta[2] = 45.0;
            break;
            
        case 'p': theta[2] -= 5.0;
            if (theta[2] < -45.0)
                theta[2] = -45.0;
            break;
            
        case 'k': theta[3] -= 5.0;
            break;
        case 'l': theta[3] += 5.0;
            break;
            
        case 'h': theta[4] -= 5.0;
            break;
        case 'j': theta[4] += 5.0;
            break;
            
        case 'n': theta[5] -= 5.0;
            break;
        case 'm': theta[5] += 5.0;
            break;
            
        case 'v': theta[6] -= 5.0;
            break;
        case 'b': theta[6] += 5.0;
            break;
            
        case 't': theta[0] = theta[1] = theta[2] = theta[3] = theta[4] = theta[5] = theta[6] = xpos = ypos = zpos = 0.0;
            break;
            
        case 'r': theta[0] = theta[1] = theta[2] = theta[3] = theta[4] = theta[5] = theta[6] = 0.0;
            break;
        case 'w':
            xpos -= cos(90 * pi/180 + theta[0] * pi/180);
            zpos += sin(90 * pi/180 + theta[0] * pi/180);
            if (xpos > 10)
                xpos = 10;
            if (zpos > 10)
                zpos = 10;
            if (xpos < -10)
                xpos = -10;
            if (zpos < -10)
                zpos = -10;
            break;
        case 's':
            xpos += cos(90 * pi/180 + theta[0] * pi/180);
            zpos -= sin(90 * pi/180 + theta[0] * pi/180);
            if (xpos > 10)
                xpos = 10;
            if (zpos > 10)
                zpos = 10;
            if (xpos < -10)
                xpos = -10;
            if (zpos < -10)
                zpos = -10;
            break;
        case 'a':
            theta[0] -= 10.0;
            break;
        case 'd':
            theta[0] += 10.0;
            break;
        case 'q':
            ypos += 1.0;
            break;
        case 'e':
            ypos -= 1.0;
            break;
        case '1':
            Acolor1 = 0.5;
            Acolor2 = 0.3;
            Acolor3 = 0.3;
            Dcolor1 = 0.1;
            Dcolor2 = 0.1;
            Dcolor3 = 0.0;
            Scolor1 = 0.7;
            Scolor2 = 0.9;
            Scolor3 = 0.5;
            break;
        case '2':
            Acolor1 = 1.3;
            Acolor2 = 0.0;
            Acolor3 = 0.0;
            Dcolor1 = 0.2;
            Dcolor2 = 0.8;
            Dcolor3 = 1.0;
            Scolor1 = 0.2;
            Scolor2 = 0.9;
            Scolor3 = 0.2;
            break;
        case '3':
            Acolor1 = 0.0;
            Acolor2 = 1.3;
            Acolor3 = 0.0;
            Dcolor1 = 0.5;
            Dcolor2 = 1.3;
            Dcolor3 = 0.0;
            Scolor1 = 0.7;
            Scolor2 = 0.9;
            Scolor3 = 0.5;
            break;
        case '4':
            Acolor1 = 0.0;
            Acolor2 = 0.0;
            Acolor3 = 1.3;
            Dcolor1 = 0.5;
            Dcolor2 = 1.1;
            Dcolor3 = 1.0;
            Scolor1 = 1.0;
            Scolor2 = 1.0;
            Scolor3 = 1.5;
            break;
        case '6':
            glutTimerFunc(80, update, 0);
            break;
        case '7':
            theta[0] = theta[1] = theta[2] = theta[3] = theta[4] = theta[5] = theta[6] = xpos = ypos = zpos = 0.0;
            break;
        case 27: exit(0);
            break;
    }
    glutPostRedisplay();
}


void processSpecialKeys(int key, int x, int y) {
    float fractionAvancement = 0.5f;
    
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP :
            x += lx * fractionAvancement;
            z += lz * fractionAvancement;
            tzg-=0.005;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fractionAvancement;
            z -= lz * fractionAvancement;
            tzg+=0.005;
            glutPostRedisplay();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init (void) {
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f}; 
    GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f}; 
    
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    p = gluNewQuadric();
}



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("MINI PROJET OPENGL");
    init();
    init1();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc (processSpecialKeys);
    
    
    glutMainLoop();
    return 0;
}

