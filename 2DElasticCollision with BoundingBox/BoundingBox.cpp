#include "BoundingBox.h"

BoundingBox makeBoundingBox(float upper_left_x, float upper_left_y, float upper_right_x, float upper_right_y, float lower_right_x, float lower_right_y, float lower_left_x, float lower_left_y) {
	BoundingBox boundingBox;
	boundingBox.upper_left_x = upper_left_x;
	boundingBox.upper_left_y = upper_left_y;
	boundingBox.upper_right_x= upper_right_x;
	boundingBox.upper_right_y= upper_right_y;
	boundingBox.lower_right_x= lower_right_x;
	boundingBox.lower_right_y= lower_right_y;
	boundingBox.lower_left_x= lower_left_x;
	boundingBox.lower_left_y= lower_left_y;
	return boundingBox;
}