# opengl_msim541
An old and simple school project (msin541) using opengl.

1.	Introduction 
This assignment is an extension of P2 introducing several new concepts.  In this assignment you will see texture binding and mapping to manually built billboards.  This assignment also demonstrates texture blending through the use of glActiveTexture() and glMultTexCoord2f().  There are classes and methods for reading in PPM files, writing them, and performing vertical flips of char pointers arraignment in the PPM format.  This project also shows screen capture generation and writing, and automatic screen capture of traffic violations.  This assignment also shows encapsulation of the simulation using a simulation engine base class.
2.	Program Design
A.	Source Files
a.	Header files (.h)
i.	BillBoard
ii.	BoundingBox
iii.	Face
iv.	Material
v.	MultiBoard
vi.	Normal
vii.	ObjModel
viii.	PPMImage
ix.	Simulation
x.	Texture
xi.	TrafficLight
xii.	TransData
xiii.	TransportSimulation
xiv.	Utility
xv.	Vector3D
xvi.	Vertex
b.	Source file (.cpp)
i.	BillBoard
ii.	Main
iii.	MultiBoard
iv.	ObjModle
v.	PPMImage
vi.	Simulation
vii.	TrafficLight
viii.	TransportSimulation
ix.	utility
B.	Functional Block Diagram
 

















C.	Class Diagram
 
D.	Class Descriptions – I will describe the classes unique to this assignment.
a.	Simulation – Base class that it used to derive transportSimulation
i.	Key variables:
1.	positionX, position: integer X and Y pixel coordinates at the start of the window
2.	width, height: integer width and height of the window in pixels
3.	title: character pointer name of the window
4.	timer: the integer timestep to use for the update function in milliseconds
5.	timerSet: bool for determining if the timer function has bee set of not
ii.	Key functions: Reshape(), Keyboard(), SpecialKey(), MouseMove(), and PassiveMouseMove are all designed to be overridden by a derived class.  They are overridden by transportSimulation.
1.	InitializeSimulation(): void that initializes glut and sets the glut display mode.  This is not repeated in transportSimulation, instead its InitializeSimulation calls this
2.	InitializeGraphics(): creates the window and initializes glew. This is not repeated in transportSimulation, instead its InitializeGraphics calls this.
3.	SetWindowPosition() and SetWindowSize(): call these before InitializeGraphics() to set the window variables
4.	RegisterCallbacks(): registers all the callback functions, calls SetClock() to set timerSet to true and registers the timer function
5.	Run(): calls the initialization and register callback functions, then enters gluts main loop.
b.	transPortSimulation: This class is used to handle and run the simulation.  To run the simulation, create an instance of it, call SetWindowXXX() if desired, call InitializeSimulation(), and finally call Run()
i.	This class has no unique data of its own.  However there is a namesSpace “transData” that is used to feed it otherwise global data.  This class needs to include that header (“TransData.h”) and use that namespace.  TransData has instances of ObjModel for the car, surveillanceCameras, and buildings. It also has instances of TrafficLight for the traffiLight model.  It also has data for the traffic signals.  TransData also has data on the car that must be maintained through updates, including: position, direction, heading, turn rate, acceleration, speed, velocity, speed limits and drag coefficients.  It also includes current camera offsets and positions.  It additionally has the dimensions of the other viewport.  TransData contains billboard instances and integer IDs for those billboards including one multiBoard.  There are also two PPMImage instances “fullScree” and “soutEastcam_NorthBound” for handing screen captures and traffic violations respectively. 
ii.	Key Functions:
1.	loadModels(): Handles in the reading of all models and images.  This is called during InitializeGraphics().
2.	Init():  Sets lighting, and generates the static display lists (i.e everything but the multi-image billboard).  This is also called during InitializeGraphics().
3.	InitializeSimulation(): calls the InitializeSimulation() in Simulation class and calls SetClock() in the Simulation class.
4.	InitialLizeGraphics(): sets default window properties, calls InitializeSimulation() in the Simulation class, loads models, initializes lighting, and generates display lists.
5.	Reshape(): updates viewport dimensions upon window shape change.
6.	sideWalkCollide(): Called during update() and used for sidewalk collision.
7.	Update():  Updates at a fixed interval from timer variable.  Determines cars forward direction, cars speed and velocity, and collisions and drag.  It also calls update on the multi-image board.  It also handles whether or not the traffic camera should be taking picture of a traffic violation.
8.	Keyboard(): Handles regular keys for resetting the car, instant breaking, camera toggle, and screen capture.
9.	SpecialKey(): Drives the car with the arrow keys and updates the cars direction.
10.	SetHeading(): Called by Draw() to handle on screen heading text.
11.	DrawScene(): Called by draw after camera setup.  Places and calls draw on all objects in the scene.
12.	Draw(): Configures cameras and calls Draw() after the appropriate cameras.  Also draws text and performs a buffer swap.
c.	Billboard: This class is used to create static billboards.  You can set the location, orientation, and size of the billboard with the SetXXX functions.  Use ReadFile to set an image to the billboard, and call draw during your draw function.
i.	Key Variables:
1.	_width and _height: Dimensions (in meters) of the billboard itself.
2.	_location.  Vector describing the location of the billboard.  The Y value is actually the height of the pillar that holds the billboard up.
3.	_orientation: orientation of the billboard (rotation about y).
4.	textureImage: an instance of the PPMImage class to open the desired image.
5.	textureNumer: A GLuint that will be bound as the name value of the loaded texture.
ii.	Key functions:
1.	SetSize(), SetLocation(), SetOrientation(): set the size (x and y), location (vector3), and orientation (about y).  If these are not used the constructor sets some default values.
2.	ReadFile(): reads the specified PPM file into a PPMimage instance.  Then binds textureNumber to a 2D texture, then generates that texture from the PPMimage.
3.	Draw(): Draws the post, then if there is a texture draws the billboard with the texture at the appropriate uv coordinates (otherwise draws a grey billboard).
d.	multiBoard:  This class is derived from Billboard and is used to create a billboard that transition between multiple images.  This class is used just like Billboard except that ReadFile() cam be called repeatedly to add images to be displayed and Update() must be called on it (from the simulation’s update function) to get the blending animation.
i.	Key variables:  multiBoard uses all the variables of Billboard except textureNumber and adds a few.
1.	textureNumbers: A vector that holds GLuints boand to specific images.  This is used to hold a reference (via GLuint) to all the desired images.  A vector is used so that we can resize.
2.	alphaCount: A float used to determine when to start a new transition and used to calculate an alpha value for the upcoming image.
3.	Img0 and img1: Index in textureNumbers of the images to be blended.
ii.	Key functions
1.	ReadFile(): works similarly to that in the Billboard class.  However, instead of writing to a single GLuint, a GLuint is bound to a texture and added to a vector of GLuints.  Calling ReadFile increases the size of the vector textureNumbers.
2.	Draw(): Draw the post the same.  However, it uses glActiveTexture() and glMultiTexCoord2f() to blend two textures together.  The alpha value of the second texture (TEXTURE1) is determined by alphaCounter.  Special care was taken here to unbind the texture when done using them here.  The value of alphaCount and therefore how much to blend the textures is determined by Update().  The two images to blend is also determined by Update().
3.	Update(): Increments alphacounter from 0 to 1 in .02 increments.  Every time alphacounter starts over, the index values img0 and img1 are changed.
e.	PPMImage: this class is used to read in PPM images and to right out screen captures as PPM images.  To read in an image for texture binding, call ReadFile, then the image is the character pointer image.
i.	Key variables
1.	Width, height: width and height of the image in pixels
2.	Image: the character pointer that points to the image in memory
3.	buf: characters used to define the buffer for writing ASCII type P3 PPM images
4.	c: character used to identify comments in the PPM file
5.	File and outfile: the in file stream and out file stream respectively
ii.	Key Functions:
1.	AllocateMemory(): allocates memory for image that is width*heigh*3 (3 bytes per pixel (RGB)).
2.	~PPImage(): deallocates image memory.
3.	ReadFile(): Reads in either binary (P6) or ASCII (P3) PPM images.  The bytes (chars) are them placed into image.
4.	WriteFile(): Writes image to either a P6 or P3 PPM image.  After writing P6, width, height, and character size the P6 image is directly written from the char pointer image.
5.	VerticalFilp():  This function writes a screen capture to a file.  The uses define the area to be captured and filename in the arguments.  glReadPixels() reads the pixels to image, then the image is flipped by storing a vertical flip into a temporary char pointer, then image takes a copy of the flipped image, image is written to file, and finally the temporary char pointers memory is deallocated.
f.	Short Summary of classes from P2:
i.	Material defines an inline struct which follows the structure of the statements following newmtl in an mtl file.
ii.	Vertex and Normal define structs with x, y, and z components.
iii.	Vector3d also defines an x,y, and struct, but it also contains functions for vector addition, subtraction, scaling, normalizing, conjugation, and computing the magnitude
iv.	Face declares and defines a struct with three integer vectors one for vertices, normal, and textures
v.	Texture declares and defines a struct with u and v texture coordinates
vi.	BoundingBox declares a cube that could be used to encapsulate the model
vii.	ObjModel contains facilities for reading a file, drawing the data, calculating a bounding box, calculating that’s box’s center of volume, and setting the display mode (from the enum DisplayMode
viii.	Traffic light declares additional facilities for changing materials
E.	Special Instructions:  The traffic cameras are off by default this time.  To toggle them on, press ‘c’.  The traffic cameras will need to be on for the South East Camera to capture the car running the northbound red light.
3. Results
3.1 Customized Car
I found the following image after searching for VA license plates:
 
I then modified and included “Feild, MSIM 541, F2015.”  But, I decided to put “Feild” and “MSIM” as the license plate identifier, and I placed “541” where the month sticker goes and “F2015” where the year goes:
 
Before export to PPM I reduced the size of the image to 128x64.  I learned firsthand that glew needs to be initialized before texture binding.  All images were vertically flipped in GIMP.  Below is a picture of the taxi with the license plate:
 
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
 
There are default values for location, orientation, and size.  The set commands are optional. The following is what is needed (with set calls) to set up the jousting rabbit billboard:
bill1.ReadFile("Models/joust.ppm");
	Vector3 bill1Loc = { 15, 4, -70 };
	bill1.SetLocation(bill1Loc);
	bill1.SetOrientation(-45);
	bill1.SetSize(12, 6);
I have billboards advertising the jousting movie, Bingham Bows (archery designs), Abarth (Fiat car company), and the R9 390 (AMD):
 
3.2 Extra Credit: Live Billboards
I Derived a class from Billboard called MultiBillboard.  Changed Billboard’s private members to protected so that we can access then from derived classes.  I included glew (in billboard base class and removed glut(not needed here)) to use the active texture function from the provided example.  I used a vector to store the texture numbers.  I added a variablesfor transition time and alpha (alphaCounter).  Inside draw I unbound the textures, and returned the active one to TEXTURE0:
glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE0);
I did this to avoid using texture 1 later and to return the default texture 0 back on for use by other objects.  On this class you can call ReadFile() repeatedly to add textures.  Each texture is named by a GLuint and this added to the vector via:
textureNumbers.push_back(texNum);

Where texNum is the GLuint assigned to that texture.  I added an update function that is called from the simulations update to run the counter.  When the counter reaches 1 it starts over.  Alpha for a black color tied to the second image (img1) is reduced by this amoumt (from starting value of 1).  The following is a video of the billboard working.  My apologies for the watermark, I did not know it would have one until after I installed the movavi software:
 
The billboard shows bows built by Bingham customers.  Adding these images to the billboard only required calling ReadFile() multiple times (mBoard is the billboard with bows):
mBoard.ReadFile("Models/bow2.ppm");
	mBoard.ReadFile("Models/bow1.ppm");
	mBoard.ReadFile("Models/bow3.ppm");
	mBoard.ReadFile("Models/bow4.ppm");

3.3 
- We need to flip the image before saving the image because glReadPixels() starts at the lower left corner and image programs (like GIMP) start in the upper left.  I flipped the image by starting at the first byte that describes the last row of the original image, and decremented by the size of the row.  Each row was copied to the flipped image, starting at the first row and incrementing by the size of the row:
for (int i = (width * height * 3) - (width*3), l = 0; i >= 0; i -= (width * 3), l += (width * 3))
	{
		for (int j = 0; j < (width * 3); j++)
		{
			int k = i + j; //image
			int m = l + j; //flipped image
			flippedImage[m] = image[k];
		}
}
After this the program copies flippedImage to image, writes the file, and calls delete[] on flippedImage.
	- We need to allocate memory (on the heap) for the character pointer array to hold the image for us before writing the image.  Otherwise image would be empty.  glReadPixels does not allocate memory for us.
	- The destructor for PPMimage deallocates memory used by the character pointer image.  We need to do this so that we release the memory for other processes when we are done, or else suffer a memory leak.  There are a pair of square brackets [] because this points to an array of characters (our bytes for the image).  I also had to deallocate memory for the flipped image when done with it: 
delete[] flippedImage;
	- The two types of PPM images supported are the raw (P6) and ASCII (P3).  P6 uses binary representation and P3 uses ASCII.  The binary P6 can be faster that P3, and the ASCII P3 can be more human readable.  The documentation states that a goal of PPM is the ease of writing parsers, and we see that both are fairly short, though P6 is even shorter than P3.  Writing both files involves first the magic number (P6 or P3), the image width, the image height, and the character size (byte).  After that P6 only needs the bytes written directly to the file.  P3 on the other hand requires that these be converted to ASCII integers first (this requires an additional loop to ensure the correct integer is written). Here is the same file written in P6 and P3:
 
The following is a video of me capturing a screen shot.  I did a video with the destination folder open so that the viewer can see the capture being created (again sorry for the watermark).  The destination folder is called “Captures” and it lives under the source folder (included the image as well, converted to jpg):
 
 
The screen capture is taken under the keyboard callback with: 
fullScreen.VerticalFlip(0, 0, winWidth, winHeight, "Captures/FullScreen.ppm");
3.3 Extra Credit
I included the <ctime> header and created a function that returns a string in the form YYYYMMDD_HH_MM_SS, where each is an integer.  This happens in the update function and only works when the traffic cameras are on (they are off by default nor, press ‘c’ to turn on).  The following code show that I let the car get further into the intersection (5 meters from center) but can take a pictures further out going north (-10 meters) to capture it’s license plate.
if (carPosition.z < 5 && carPosition.z > -10)
	{
		if (carPosition.x < 10 && carPosition.x > -10)
		{
			if (northRed && carHeading == "North" && additionalCameras)
			{
				time_t currentTime = time(0);
				tm *ltime = localtime(&currentTime);

				int year = 1900 + ltime->tm_year;
				int month = ltime->tm_mon;
				int day = ltime->tm_mday;
				int hours = ltime->tm_hour;
				int min = ltime->tm_min;
				int sec = ltime->tm_sec;
				string DTG = to_string(year) + to_string(month) + to_string(day) + "_" + to_string(hours) + "_" + to_string(min) + "_" + to_string(sec);

				string file = "Captures/NorthBoundViolation" + DTG + ".ppm";

				soutEastcam_NorthBound.VerticalFlip(winWidth - sWidth, winHeight - sHeight, sWidth, sHeight, file);
			}
		}
	}
The following is a video showing the traffic camera working (with movavi watermarks).  The camera takes multiple pictures.  You can see the ppm images created in the folder on the right.  Please remember to delete captures you do not need.
 
I converted the screen captures to jpg to show here.  This is from one violation put two pictures were taken, as shown in the movie.
 
 
3.4 Simulation Engine (Extra Credit)
I used the simulation engine provided to implement the transportation simulation.  I actual started with the provided simulation example and added the code from p2 to it.  The only thing I changed in the base Simulation class was to enable depth testing.  I added a namespace called “transData” to hold otherwise global data for the transportation simulation (to clean up the global namespace).  I also added cout statements so that there is some feedback while the simulation is loading. I added a few private functions specific to the transportation simulation:
loadModels() – I separated the reading in of models.  This function is called during InitializeGraphics() and is part of this step.
Init() – also called during  InitializeGraphics().  This sets up lighting and draw lists.
SetHeading() – part of Draw().  This sets the heading text for the car.
drawScene – part of Draw().  When the cameras are set up in draw, this function is called to draw the scene.
With the transportSimulation class, main now looks like this:
#include "TransportSimulation.h"

using namespace std;

int main(int argc, char** argv)
{
	transportSimulation transSim;

	//there are defualt values for window size and title
	//you can set them here but it is not neccessary
	transSim.InitializeSimulation(argc, argv);
	transSim.Run();

	return 0;
}
As per the comments, you can set window size and title, but here I’m using defaults that I set in code.
4.	Discussion
In this assignment I learned about texture mapping, using a simulation engine architecture, and reading and writing images to a file.  I created a custom texture for the license plate of the taxi.  In this assignment we learned to read in PPM images and to bind textures then map them to a rectangular billboard by using uv coordinates.  I also learned how to use glActiveTexture() and glMultiTexCoord2f() to combine two texture on one mesh and to vary alpha values to make smooth, fading transitions.  I learned about keeping GLuint references to textures and how to appropriately handle texture bindings and texture state as to not misuse the openGL state machine.  We also learned how to write out PPM images from a screen capture generated by glReadPixels() and stored in a character pointer.  I became further familiar with PPM images by vertically flipping a char pointer before writing directly into the P6 format.  I also learned about encapsulating a simulation by utilizing the provided format to implement the transportation simulation.

