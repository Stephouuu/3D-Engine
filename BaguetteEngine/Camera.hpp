#pragma once

#include "ofVec3f.h"

struct Camera
{
	Camera(ofVec3f p, ofVec3f o)
		: position(p), orientation(o)
	{
	}

	void calibrate(void)
	{
		axis_z = orientation;
		axis_x = ofVec3f(viewport_width * fov / viewport_height);
		axis_y = axis_x.cross(axis_z).normalize() * fov;
	}

	ofVec3f position;
	ofVec3f orientation;
	ofVec3f target;

	ofVec3f axis_x;
	ofVec3f axis_y;
	ofVec3f axis_z;

	ofVec3f up;

	float viewport_width;
	float viewport_height;

	float fov;
};