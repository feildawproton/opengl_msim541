#pragma once

#include <iostream>
#include <string>
#include "GL/glew.h"
//#include <gl/glut.h>

#include "PPMImage.h";
#include "Vector3D.h";

using namespace std;

class Billboard
{
public:
	Billboard(void);
	~Billboard(void);
	void ReadFile(string fileName);
	void SetSize(float width, float height);
	void SetLocation(Vector3 location);
	void SetOrientation(float orientation);
	void Draw(); //call in the simulations draw function

protected:  //chaned to protected so I can acces from derived class
	PPMImage textureImage;
	float _width, _height;
	// The variable location contains 3 variables: x, y, z, where y is really the elevation of the board.
	Vector3 _location;
	float _orientation;
	GLuint textureNumber;
};

