#include "MultiBoard.h"

#include "PPMImage.h"


multiBoard::multiBoard(void)
{
	//defaults
	_width = 4;
	_height = 3;
	_location.x = 0;
	_location.y = 4;
	_location.z = 0;
	_orientation = 0;
}

multiBoard::~multiBoard(void)
{
}

void multiBoard::ReadFile(string fileName)
{
	std::cout << "reading " << fileName << std::endl;

	PPMImage texture;
	texture.ReadFile(fileName);

	GLuint texNum; //a temp gluint

	glGenTextures(1, &texNum);  //generate the texture

	glBindTexture(GL_TEXTURE_2D, texNum);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture.image);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//add GLuint to vector of texture numers
	textureNumbers.push_back(texNum);
}


void multiBoard::Draw()
{
	glPushMatrix();
	glTranslatef(_location.x, 0, _location.z); //save y for drawing latter
	glRotatef(_orientation, 0, 1, 0);  //about y axis

	glColor4f(.5, .5, .5, .5);
	//cubic piller
	glBegin(GL_POLYGON);
	glVertex3f(-.1, 0, -.1);
	glVertex3f(.1, 0, -.1);
	glVertex3f(.1, _location.y, -.1);
	glVertex3f(-.1, _location.y, -.1);

	glVertex3f(-.1, 0, .1);
	glVertex3f(.1, 0, .1);
	glVertex3f(.1, _location.y, .1);
	glVertex3f(-.1, _location.y, .1);
	glEnd();

	//multitexture portion
	if (textureNumbers.size() >= 2)
	{
		//bind texture 0 to imgage 0
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureNumbers[img0]);

		//bind texture 1 to imgage 1
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureNumbers[img1]);
		//decreas black alpha to make image 1 brighter over time
		GLfloat constOtherColor[4] = { 0.0, 0.0, 0.0, (1 - alphaCounter) };
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, constOtherColor);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
		glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE0);
		glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE1);
		glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
		glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
		glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_ALPHA);

		//draw quad and bind
		glBegin(GL_QUADS);

		glNormal3f(0, 0, 1);

		glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
		glVertex3f(-_width / 2, _location.y, 0);

		glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
		glVertex3f(_width / 2, _location.y, 0);

		glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
		glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
		glVertex3f(_width / 2, _location.y + _height, 0);

		glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
		glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
		glVertex3f(-_width / 2, _location.y + _height, 0);

		glEnd();

		//set targets to zero instead of disabling
		//possible quicker than disabling
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		//make sure texture 0 is active for use by other objects
		glActiveTexture(GL_TEXTURE0);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);
		glVertex3f(-_width / 2, _location.y, 0);
		glVertex3f(_width / 2, _location.y, 0);
		glVertex3f(_width / 2, _location.y + _height, 0);
		glVertex3f(-_width / 2, _location.y + _height, 0);

		glEnd();
	}
}

void multiBoard::update()
{
	alphaCounter += 0.02;

	if (alphaCounter >= 1)
	{
		alphaCounter = 0;

		img0 += 1;
		img1 += 1;

		if (img0 >= textureNumbers.size())
		{
			img0 = 0;
		}
		if (img1 >= textureNumbers.size())
		{
			img1 = 0;
		}

		std::cout << "img0: " << img0 << ", img1: " << img1 << std::endl;
	}


}