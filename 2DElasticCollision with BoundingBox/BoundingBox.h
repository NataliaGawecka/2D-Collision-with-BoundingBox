#pragma once
#include <iostream>
typedef struct {
	float upper_left_x;
	float upper_left_y;
	float upper_right_x;
	float upper_right_y;
	float lower_right_x;
	float lower_right_y;
	float lower_left_x;
	float lower_left_y;
}BoundingBox;

BoundingBox makeBoundingBox(float upper_left_x, float upper_left_y, float upper_right_x, float upper_right_y, float lower_right_x, float lower_right_y, float lower_left_x, float lower_left_y);