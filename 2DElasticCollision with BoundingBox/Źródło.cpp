#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<iostream>
#include <windows.h>
#include <math.h>
#include "Circle.h"

using namespace std;
float xr = 0, yr = 0;
float xr2 = 0, yr2 = 0;


Circle* circle1 = new Circle(0, 0, 3, 20, 1);
Circle* circle2 = new Circle(7, 0, 3, 20, 1);

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20, 20, -20, 20);
}
// Basic collision
/*
void elastic_collision() {
 
    xr2 = xr;
    yr2 = yr;
    xr = -xr;
    yr = -yr;
}
*/

//elastic collision
void elastic_collision() {
    float  m21, dvx2, a, x21, y21, vx21, vy21, fy21, sign, vx_cm, vy_cm;
    float R = 1;
    m21 = circle2->m / circle1->m;
    x21 = circle2->x - circle1->x;
    y21 = circle2->y - circle1->y;
    vx21 = xr2 - xr;
    vy21 = yr2 - yr;

    vx_cm = (circle1->m * xr + circle2->m * xr2) / (circle1->m + circle2->m);
    vy_cm = (circle1->m * yr + circle2->m * yr2) / (circle1->m + circle2->m);

    if ((vx21 * x21 + vy21 * y21) >= 0) return;
    fy21 = 1.0E-12 * fabs(y21);
    if (fabs(x21) < fy21) {
        if (x21 < 0) { sign = -1; }
        else { sign = 1; }
        x21 = fy21 * sign;
    }
    a = y21 / x21;
    dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21));
    xr2 = xr2 + dvx2;
    yr2 = yr2 + a * dvx2;
    xr = xr - m21 * dvx2;
    yr = yr - a * m21 * dvx2;

    xr = (xr - vx_cm) * R + vx_cm;
    yr = (yr - vy_cm) * R + vy_cm;
    xr2 = (xr2 - vx_cm) * R + vx_cm;
    yr2 = (yr2 - vy_cm) * R + vy_cm;

   
}

//Checking collision between two circles using bounding box
void collision_check() {

    if ((circle1->boundingBox.upper_left_x + (circle1->radius * 2)) >= (circle2->boundingBox.upper_left_x) &&
        (circle1->boundingBox.upper_left_x)<=(circle2->boundingBox.upper_left_x+(circle2->radius*2))&&
        (circle1->boundingBox.upper_left_y+ (circle1->radius * 2))>=(circle2->boundingBox.upper_left_y)&&
         (circle1->boundingBox.upper_left_y)<=(circle2->boundingBox.upper_left_y + (circle2->radius*2))  ){
       elastic_collision();
        
    }

}
//Checking collision between two circles using pythagoras theorem
void collision_check2() {
    float a = abs((circle1->x + circle1->radius) - (circle2->x + circle2->radius));
    float b = abs((circle1->y + circle1->radius) - (circle2->y + circle2->radius));
    if (sqrtf(a * a + b * b) <= circle1->radius + circle2->radius)
    {
        elastic_collision();
    }
}
//Checking collision between circles and window frame
void window_collision_check() {
    //Circle 1
    if (circle1->boundingBox.upper_right_x >= 20.0) {
        xr =-xr;
    }
    if (circle1->boundingBox.upper_left_x <= -20.0) {
        xr = -xr;
    }
    if (circle1->boundingBox.upper_right_y >= 20.0) {
        yr = -yr;
    }
    if (circle1->boundingBox.lower_right_y <= -20.0) {
        yr = -yr;
    }
    //Circle 2
    if (circle2->boundingBox.upper_right_x >= 20.0) {
        xr2 = -xr2;
    }
    if (circle2->boundingBox.upper_left_x <= -20.0) {
        xr2 = -xr2;
    }
    if (circle2->boundingBox.upper_right_y >= 20.0) {
        yr2 = -yr2;
    }
    if (circle2->boundingBox.lower_right_y <= -20.0) {
        yr2 = -yr2;
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    circle1->x = circle1->x + xr;
    circle1->y = circle1->y + yr;

    circle2->x = circle2->x + xr2;
    circle2->y = circle2->y + yr2;

    circle1->draw_circle(circle1->radius, circle1->x, circle1->y, circle1->segments);
    circle1->setBoundingBox(makeBoundingBox(circle1->x-circle1->radius, circle1->y + circle1->radius, circle1->x + circle1->radius, circle1->y + circle1->radius, circle1->x + circle1->radius,circle1->y - circle1->radius, circle1->x - circle1->radius, circle1->y - circle1->radius));
    circle2->draw_circle(circle2->radius, circle2->x, circle2->y, circle2->segments);
    circle2->setBoundingBox(makeBoundingBox(circle2->x- circle2->radius, circle2->y+ circle2->radius, circle2->x+ circle2->radius, circle2->y  + circle2->radius, circle2->x + circle2->radius, circle2->y - circle2->radius, circle2->x- circle2->radius, circle2->y - circle2->radius));

    collision_check();
    //collision_check2();
    window_collision_check();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();

}

void keyboard(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP:
        yr = 0.009;
        xr = 0;
        break;
    case GLUT_KEY_DOWN:
        yr = -0.009;
        xr = 0;
        break;
    case GLUT_KEY_LEFT:
        xr = -0.009;
        yr = 0;
        break;
    case GLUT_KEY_RIGHT:
        xr = 0.009;
        yr = 0;
        break;
     }

}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(840, 680);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}