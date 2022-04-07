#include "Billboard.h"
#include "PPMImage.h"


Billboard::Billboard(void)
{
	//sets some defaults
	_width = 4;
	_height = 3;
	_location.x = 0;
	_location.y = 4;
	_location.z = 0;
	_orientation = 0;
}

Billboard::~Billboard(void)
{
}

void Billboard::ReadFile(string fileName)
{
	// Read the texture file, generate the texture object, and configure
	// the texturing parameters.

	std::cout << "reading " << fileName << std::endl;

	PPMImage texture;
	texture.ReadFile(fileName);

	glGenTextures(1, &textureNumber);  //generate the texture

	glBindTexture(GL_TEXTURE_2D, textureNumber);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture.image);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void Billboard::SetSize(float width, float height)
{
	// Your code
	_width = width;
	_height = height;
}

void Billboard::SetLocation(Vector3 location)
{
	// Your code
	_location.x = location.x;
	_location.y = location.y;
	_location.z = location.z;
}

void Billboard::SetOrientation(float orientation)
{
	// Your code
	_orientation = orientation;
}

void Billboard::Draw()
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
	//post
	// Draw the board and pillar.  Use texture mapping for the board only.
	// The pillar is drawn just using simple geometry, i.e., a rectangle.

	// Use glEnable() and glDisable() to change OpenGL states.

	if (textureNumber != NULL)
	{
		glEnable(GL_TEXTURE_2D); //
		glBindTexture(GL_TEXTURE_2D, textureNumber); // check repeat of myself
		glBegin(GL_QUADS);

		glNormal3f(0, 0, 1);

		glTexCoord2f(0, 0);
		glVertex3f(-_width / 2, _location.y, 0);

		glTexCoord2f(1, 0);
		glVertex3f(_width / 2, _location.y, 0);

		glTexCoord2f(1, 1);
		glVertex3f(_width / 2, _location.y + _height, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-_width / 2, _location.y + _height, 0);

		glEnd();
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

	glDisable(GL_TEXTURE_2D);
}
