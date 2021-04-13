#define _USE_MATH_DEFINES
#include "Circle.h"

void Circle::draw_circle(float radius, float x, float y, int segments) {
	float phi, x1, y1;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(255, 0, 0);
	glVertex2f(x, y);
	for (int j = 0; j <= segments; j++) {	
		phi = 2 * M_PI * j / segments;	
		x1 = radius * cos(phi) + x;
		y1= radius * sin(phi) + y;
		glVertex2f(x1, y1);
	}
	glEnd();
}

void Circle::setBoundingBox(BoundingBox _boundingBox) {
	boundingBox = _boundingBox;
}