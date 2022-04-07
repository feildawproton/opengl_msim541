# opengl_msim541
An old and simple school project (msin541) using opengl.

## 1.	Introduction 
This assignment is an extension of P2 introducing several new concepts.  In this assignment you will see texture binding and mapping to manually built billboards.  This assignment also demonstrates texture blending through the use of glActiveTexture() and glMultTexCoord2f().  There are classes and methods for reading in PPM files, writing them, and performing vertical flips of char pointers arraignment in the PPM format.  This project also shows screen capture generation and writing, and automatic screen capture of traffic violations.  This assignment also shows encapsulation of the simulation using a simulation engine base class.

## B.	Functional Block Diagram
![image](https://user-images.githubusercontent.com/56926839/162270367-922b6481-3928-4935-a08c-1ff8b0a15224.png)

## C.	Class Diagram
![image](https://user-images.githubusercontent.com/56926839/162270506-50af92ad-b460-41c1-a7c5-5688f28531c5.png)

## D.	Class Descriptions – I will describe the classes unique to this assignment.

a.	Simulation – Base class that it used to derive transportSimulation

b.	transPortSimulation: This class is used to handle and run the simulation.  To run the simulation, create an instance of it, call SetWindowXXX() if desired, call InitializeSimulation(), and finally call Run()

c.	Billboard: This class is used to create static billboards.  You can set the location, orientation, and size of the billboard with the SetXXX functions.  Use ReadFile to set an image to the billboard, and call draw during your draw function.

d.	multiBoard:  This class is derived from Billboard and is used to create a billboard that transition between multiple images.  This class is used just like Billboard except that ReadFile() cam be called repeatedly to add images to be displayed and Update() must be called on it (from the simulation’s update function) to get the blending animation.

e.	PPMImage: this class is used to read in PPM images and to right out screen captures as PPM images.  To read in an image for texture binding, call ReadFile, then the image is the character pointer image.

Special Instructions:  The traffic cameras are off by default this time.  To toggle them on, press ‘c’.  The traffic cameras will need to be on for the South East Camera to capture the car running the northbound red light.

## 3. Results

3.1 Customized Car

![image](https://user-images.githubusercontent.com/56926839/162271177-d66cf19c-fca6-44a2-8976-113e25ee42da.png)
Before export to PPM I reduced the size of the image to 128x64.  I learned firsthand that glew needs to be initialized before texture binding.  All images were vertically flipped in GIMP.  Below is a picture of the taxi with the license plate:
![image](https://user-images.githubusercontent.com/56926839/162271208-1b9b060c-b28a-46fe-9629-fef76ce5e9f4.png)

3.2. Billboards

	- glBindTexture() binds our texture name to a target.  The target is a single unique type of texture that can be rebound to work with another texture.  The texture name is an unsigned integer.  We need to do this so that we can refer to our texture by reference.  It is much faster to load all our textures then bind them as necessary instead of reloading them.
	- GL_REPEAT will repeat the texture when the texture coordinates are exceeded (like ground texture).  For example if we go past 1 on the u axis we will start back over at 0.  With GL_CLAMP coordinates cannot go out of the range (0,1).  I used clamp here.
	- We need to enable texture sampling and therefore texture mapping and drawing when we want to apply a texture.  We when don’t want to use a texture (ex: straight color) we need to disable  it.
I found that texture sizes need to be base 2 or aliasing will occur.  The simple mapping for the billboard looks like this:
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
  The above just maps the corners of the image to the corners of the quad that makes up the billboard.  The billboard below shows an image of a rabbit and man jousting.  I’m pretending it’s a movie poster:




