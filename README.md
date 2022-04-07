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
  
  ![image](https://user-images.githubusercontent.com/56926839/162271352-bb104d04-15ef-48c5-8294-6ae9e69732a0.png)
There are default values for location, orientation, and size.  The set commands are optional. The following is what is needed (with set calls) to set up the jousting rabbit billboard:
bill1.ReadFile("Models/joust.ppm");
	Vector3 bill1Loc = { 15, 4, -70 };
	bill1.SetLocation(bill1Loc);
	bill1.SetOrientation(-45);
	bill1.SetSize(12, 6);
I have billboards advertising the jousting movie, Bingham Bows (archery designs), Abarth (Fiat car company), and the R9 390 (AMD):

![image](https://user-images.githubusercontent.com/56926839/162271400-58ec084b-7755-4ba0-8cd9-81ad459f310b.png)

## Extra Credit: Live Billboards

I Derived a class from Billboard called MultiBillboard.  Changed Billboard’s private members to protected so that we can access then from derived classes.  I included glew (in billboard base class and removed glut(not needed here)) to use the active texture function from the provided example.  I used a vector to store the texture numbers.  I added a variablesfor transition time and alpha (alphaCounter).  Inside draw I unbound the textures, and returned the active one to TEXTURE0:
glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE0);
I did this to avoid using texture 1 later and to return the default texture 0 back on for use by other objects.  On this class you can call ReadFile() repeatedly to add textures.  Each texture is named by a GLuint and this added to the vector via:
textureNumbers.push_back(texNum);

Where texNum is the GLuint assigned to that texture.  I added an update function that is called from the simulations update to run the counter.  When the counter reaches 1 it starts over.  Alpha for a black color tied to the second image (img1) is reduced by this amoumt (from starting value of 1).  The following is a video of the billboard working.  My apologies for the watermark, I did not know it would have one until after I installed the movavi software:
![image](https://user-images.githubusercontent.com/56926839/162271488-17c6a5e0-c24d-4ef7-ba97-eb317b2dea9e.png)

The billboard shows bows built by Bingham customers.  Adding these images to the billboard only required calling ReadFile() multiple times (mBoard is the billboard with bows):
mBoard.ReadFile("Models/bow2.ppm");
	mBoard.ReadFile("Models/bow1.ppm");
	mBoard.ReadFile("Models/bow3.ppm");
	mBoard.ReadFile("Models/bow4.ppm");

## 3.3




