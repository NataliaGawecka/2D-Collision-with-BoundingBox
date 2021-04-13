#pragma once
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<iostream>
#include <windows.h>
#include <math.h>
#include "BoundingBox.h"
 class Circle {
  
 public:
	BoundingBox boundingBox;
	float radius;
	float m;
	float x;
	float y;
	int segments;
	Circle(float c_x, float c_y, float c_radius, int c_segments, float c_m) {
		x = c_x;
		y = c_y;
		radius = c_radius;
		segments = c_segments;
		m = c_m;

    }

	void draw_circle(float radius,float x,float y,int segments);
	void setBoundingBox(BoundingBox boundingBox);
};