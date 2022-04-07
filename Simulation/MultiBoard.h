#pragma once

#include "BillBoard.h"
#include <vector>

using namespace std;

class multiBoard : public Billboard
{
public:
	multiBoard();
	~multiBoard();
	void ReadFile(string fileName0); //call multiple times with different images
	void Draw(); //call in the simulations draw function
	void update(); //call in the simulations update function
protected:  //chaned to protected so I can acces from derived class
	vector<GLuint> textureNumbers;//vector of GLuints bound to the images read in by ReadFile

	float alphaCounter = 0;//used to determine transitions and alpha value for blended textures

	int img0 = 0; //texture 0 index in textureNumbers
	int img1 = 1; //texture 1 index in textureNumbers

	//float alpha = 1;
};