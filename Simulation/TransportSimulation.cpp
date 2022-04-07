#include "TransportSimulation.h"
#include "TransData.h"
#include "utility.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace transData;

transportSimulation::transportSimulation(void)
{
}

transportSimulation::~transportSimulation(void)
{
}

//separate function for clarity
void transportSimulation::loadModels()
{
	std::cout << "initializing simulation, loading models" << endl;
	//guess I should load the models here
	// Load the 3D models.
	std::cout << "reading in traffic light: ";
	trafficLight.ReadFile("Models/TrafficLight.obj");
	std::cout << "model loaded" << endl;

	std::cout << "reading in surveillance camer: ";
	surveillanceCamera.ReadFile("Models/camera.obj");
	std::cout << "model loaded" << endl;

	std::cout << "reading in car: ";
	car.ReadFile("Models/taxi.obj");
	std::cout << "model loaded" << endl;

	//read in the props
	std::cout << "reading in building1: ";
	building1.ReadFile("Models/building1.obj");
	std::cout << "model loaded" << endl;

	std::cout << "reading in building2: ";
	building2.ReadFile("Models/building2.obj");
	std::cout << "model loaded" << endl;

	std::cout << "reading in building3: ";
	building3.ReadFile("Models/BUILDING3.obj");
	std::cout << "model loaded" << endl;

	std::cout << "reading in building4: ";
	building4.ReadFile("Models/building4.obj");
	std::cout << "model loaded" << endl;

	//std::cout << "reading in character: ";
	//shepard.ReadFile("Models/me3ExpTest.obj");
	//std::cout << "model loaded" << endl;

	//sidewalk
	std::cout << "reading in sidewalk: ";
	sidewalk.ReadFile("Models/sidewalk.obj");
	std::cout << "model loaded" << endl;

	std::cout << "all models loaded" << endl;

	//billboards~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::cout << "set up billboards:" << endl;;

	bill1.ReadFile("Models/joust.ppm");
	Vector3 bill1Loc = { 15, 4, -70 };
	bill1.SetLocation(bill1Loc);
	bill1.SetOrientation(-45);
	bill1.SetSize(12, 6);
	std::cout << "billboard 1 loaded" << endl;;

	bill2.ReadFile("Models/abarth.ppm");
	Vector3 bill2Loc = { 15, 3, -110 };
	bill2.SetLocation(bill2Loc);
	bill2.SetOrientation(-45);
	bill2.SetSize(6, 6);
	std::cout << "billboard 2 loaded" << endl;;

	bill3.ReadFile("Models/Bingham.ppm");
	Vector3 bill3Loc = { -15, 2, -70 };
	bill3.SetLocation(bill3Loc);
	bill3.SetOrientation(45);
	bill3.SetSize(12, 6);
	std::cout << "billboard 3 loaded" << endl;

	bill4.ReadFile("Models/R390.ppm");
	Vector3 bill4Loc = { -15, 4, -130 };
	bill4.SetLocation(bill4Loc);
	bill4.SetOrientation(45);
	bill4.SetSize(12, 6);
	std::cout << "billboard 4 loaded" << endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::cout << "set up multi image billboard" << endl;
	mBoard.ReadFile("Models/bow2.ppm");
	mBoard.ReadFile("Models/bow1.ppm");
	mBoard.ReadFile("Models/bow3.ppm");
	mBoard.ReadFile("Models/bow4.ppm");
	Vector3 billMLoc = { -15, 3, -160 };
	mBoard.SetLocation(billMLoc);
	mBoard.SetOrientation(45);
	mBoard.SetSize(6, 12);
	std::cout << "nulti image board loaded" << endl;


	std::cout << "initializing list" << endl;
}

void transportSimulation::init()
{
	glClearColor(0.5, 0.5, 1.0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Note that the light is defined in the eye or camera frame.
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

	GLfloat ambient[] = { 0.3, 0.3, 0.3, 1 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Generate display list for the surveillance camera.
	surveillanceCameraID = glGenLists(1);

	glNewList(surveillanceCameraID, GL_COMPILE);
	surveillanceCamera.Draw();
	glEndList();
	std::cout << "surveillance camera list generated" << endl;

	//list for props that i added
	build1ID = glGenLists(1);
	glNewList(build1ID, GL_COMPILE);
	building1.Draw();
	glEndList();
	std::cout << "build1 list generated" << endl;

	build2ID = glGenLists(1);
	glNewList(build2ID, GL_COMPILE);
	building2.Draw();
	glEndList();
	std::cout << "build2 list generated" << endl;

	build3ID = glGenLists(1);
	glNewList(build3ID, GL_COMPILE);
	building3.Draw();
	glEndList();
	std::cout << "build3 list generated" << endl;

	build4ID = glGenLists(1);
	glNewList(build4ID, GL_COMPILE);
	building4.Draw();
	glEndList();
	std::cout << "build4 list generated" << endl;

	//shepID = glGenLists(1);
	//glNewList(shepID, GL_COMPILE);
	//shepard.Draw();
	//glEndList();
	//std::cout << "character list generated" << endl;

	//sidewalk
	sidewalkID = glGenLists(1);
	glNewList(sidewalkID, GL_COMPILE);
	sidewalk.Draw();
	glEndList();
	std::cout << "sidewalk list generated" << endl;

	// Generate display list for the car.
	carID = glGenLists(1);
	glNewList(carID, GL_COMPILE);
	car.Draw();
	glEndList();
	std::cout << "car list generated" << endl;

	//static billboards~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bill1ID = glGenLists(1);
	glNewList(bill1ID, GL_COMPILE);
	bill1.Draw();
	glEndList();
	std::cout << "billboard 1 list generated" << endl;

	bill2ID = glGenLists(1);
	glNewList(bill2ID, GL_COMPILE);
	bill2.Draw();
	glEndList();
	std::cout << "billboard 2 list generated" << endl;

	bill3ID = glGenLists(1);
	glNewList(bill3ID, GL_COMPILE);
	bill3.Draw();
	glEndList();
	std::cout << "billboard 3 list generated" << endl;

	bill4ID = glGenLists(1);
	glNewList(bill4ID, GL_COMPILE);
	bill4.Draw();
	glEndList();
	std::cout << "billboard 4 list generated" << endl;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//not static so can't be here
	/*mBoardID = glGenLists(1);
	glNewList(mBoardID, GL_COMPILE);
	mBoard.Draw();
	glEndList();
	std::cout << "multi board generated" << endl;*/
	//Multi board


	// Generate the display list for terrain, including road and grass.
	terrainID = glGenLists(1);
	glNewList(terrainID, GL_COMPILE);
	glDisable(GL_LIGHTING);

	// Grass
	glColor3f(0, 0.7, 0);
	glBegin(GL_QUADS);
	glVertex3f(-1000, 0, 1000);
	glVertex3f(-10, 0, 1000);
	glVertex3f(-10, 0, 10);
	glVertex3f(-1000, 0, 10);

	glVertex3f(10, 0, 1000);
	glVertex3f(1000, 0, 1000);
	glVertex3f(1000, 0, 10);
	glVertex3f(10, 0, 10);

	glVertex3f(10, 0, -10);
	glVertex3f(1000, 0, -10);
	glVertex3f(1000, 0, -1000);
	glVertex3f(10, 0, -1000);

	glVertex3f(-1000, 0, -10);
	glVertex3f(-10, 0, -10);
	glVertex3f(-10, 0, -1000);
	glVertex3f(-1000, 0, -1000);
	glEnd();

	// Roads
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);

	glVertex3f(-10, 0, 1000);
	glVertex3f(10, 0, 1000);
	glVertex3f(10, 0, -1000);
	glVertex3f(-10, 0, -1000);

	glVertex3f(-1000, 0, 10);
	glVertex3f(1000, 0, 10);
	glVertex3f(1000, 0, -10);
	glVertex3f(-1000, 0, -10);
	glEnd();

	// Yellow line
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(-0.1, 0.05, 1000);
	glVertex3f(0.1, 0.05, 1000);
	//stop the south side yellow lines short of the intersection
	glVertex3f(0.1, 0.05, 10);
	glVertex3f(-0.1, 0.05, 10);
	glEnd();

	//the following addes the other yellow lines

	//norht side yellow
	glBegin(GL_POLYGON);
	glVertex3f(-0.1, 0.05, -1000);
	glVertex3f(0.1, 0.05, -1000);
	glVertex3f(0.1, 0.05, -10);
	glVertex3f(-0.1, 0.05, -10);
	glEnd();

	// Yellow line east/west, exchange x and z values from north/south lines
	glBegin(GL_POLYGON);
	glVertex3f(-1000, .05, -.1);
	glVertex3f(-10, .05, -.1);
	glVertex3f(-10, .05, .1);
	glVertex3f(-1000, .05, .1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1000, .05, -.1);
	glVertex3f(10, .05, -.1);
	glVertex3f(10, .05, .1);
	glVertex3f(1000, .05, .1);
	glEnd();

	//the following addes the white dashed lines to the list
	glColor3f(1, 1, 1);
	float offset = 10; //used for the begining of lines and there spacing (+12m ea. iteration)
	for (int i = 0; i < 83; i++)
	{
		//north side north bound
		glBegin(GL_POLYGON);
		glVertex3f(4.95, .05, -offset);
		glVertex3f(5.05, .05, -offset);
		glVertex3f(5.05, .05, -(offset + 3.0f));
		glVertex3f(4.95, .05, -(offset + 3.0f));
		glEnd();

		//north side south bound
		glBegin(GL_POLYGON);
		glVertex3f(-4.95, .05, -offset);
		glVertex3f(-5.05, .05, -offset);
		glVertex3f(-5.05, .05, -(offset + 3.0f));
		glVertex3f(-4.95, .05, -(offset + 3.0f));
		glEnd();

		//south side north bound
		glBegin(GL_POLYGON);
		glVertex3f(4.95, .05, offset);
		glVertex3f(5.05, .05, offset);
		glVertex3f(5.05, .05, (offset + 3.0f));
		glVertex3f(4.95, .05, (offset + 3.0f));
		glEnd();

		//south side south bound
		glBegin(GL_POLYGON);
		glVertex3f(-4.95, .05, offset);
		glVertex3f(-5.05, .05, offset);
		glVertex3f(-5.05, .05, (offset + 3.0f));
		glVertex3f(-4.95, .05, (offset + 3.0f));
		glEnd();

		//west side east bound
		glBegin(GL_POLYGON);
		glVertex3f(-offset, .05, 4.95);
		glVertex3f(-offset, .05, 5.05);
		glVertex3f(-(offset + 3.0f), .05, 5.05);
		glVertex3f(-(offset + 3.0f), .05, 4.95);
		glEnd();

		//west side west bound
		glBegin(GL_POLYGON);
		glVertex3f(-offset, .05, -4.95);
		glVertex3f(-offset, .05, -5.05);
		glVertex3f(-(offset + 3.0f), .05, -5.05);
		glVertex3f(-(offset + 3.0f), .05, -4.95);
		glEnd();

		//east side east bound
		glBegin(GL_POLYGON);
		glVertex3f(offset, .05, 4.95);
		glVertex3f(offset, .05, 5.05);
		glVertex3f((offset + 3.0f), .05, 5.05);
		glVertex3f((offset + 3.0f), .05, 4.95);
		glEnd();

		//east side west bound
		glBegin(GL_POLYGON);
		glVertex3f(offset, .05, -4.95);
		glVertex3f(offset, .05, -5.05);
		glVertex3f((offset + 3.0f), .05, -5.05);
		glVertex3f((offset + 3.0f), .05, -4.95);
		glEnd();

		offset += 12.0f; //3m + 9m
	}

	glEndList();

	std::cout << "terrain list generated" << endl;
}

void transportSimulation::InitializeSimulation(int argc, char** argv)
{
	Simulation::InitializeSimulation(argc, argv);

	//need to set the timer
	Simulation::SetClock(updateInterval);

	std::cout << "simulation initialized" << endl;
}

void transportSimulation::InitializeGraphics()
{
	//added the following to define the window
	positionX = 100;
	positionY = 100;
	width = 1300;
	height = 800;
	title = "traffic simulation";

	Simulation::InitializeGraphics();  //sets the above in glut and inits glew

	loadModels();

	init();

	std::cout << "graphics initialized" << endl;
}

void transportSimulation::Reshape(int w, int h)
{
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);

	glViewport(0, 0, w, h);*/

	winWidth = w, winHeight = h;

	// Update sWidth and sHeight here.
	sWidth = winWidth / 6;
	sHeight = winHeight / 6;
}

//simple method for doing a simple collision
Vector3 sideWalkCollide(Vector3 forVel)
{
	Vector3 reflectionVelocity = { 0, 0, 0 };

	if (carPosition.x > 10 && carPosition.x < 60)
	{
		//the car is on the eastside
		if (carPosition.z < -10 && carPosition.z > -60)
		{
			//the car is in the northeast block
			Vector3 Center;
			Center.x = 35;
			Center.y = 0;
			Center.z = -35;

			//find the vector that points to the cars direction
			Vector3 projectionVector = carPosition - Center;
			projectionVector.normalize();  //added this to the vector3 struct

			float velocity = forVel.mag();

			reflectionVelocity = projectionVector*velocity;
		}
		else if (carPosition.z > 10 && carPosition.z < 60)
		{
			//the car is in the southeast block
			Vector3 Center;
			Center.x = 35;
			Center.y = 0;
			Center.z = 35;

			//find the vector that points to the cars direction
			Vector3 projectionVector = carPosition - Center;
			projectionVector.normalize();  //added this to the vector3 struct

			float velocity = forVel.mag();

			reflectionVelocity = projectionVector*velocity;
		}
	}

	else if (carPosition.x < -10 && carPosition.x > -60)
	{
		//the car is on the west side
		if (carPosition.z < -10 && carPosition.z > -60)
		{
			//the car is in the northwest block
			Vector3 Center;
			Center.x = -35;
			Center.y = 0;
			Center.z = -35;

			//find the vector that points to the cars direction
			Vector3 projectionVector = carPosition - Center;
			projectionVector.normalize();  //added this to the vector3 struct

			float velocity = forVel.mag();

			reflectionVelocity = projectionVector*velocity;
		}
		else if (carPosition.z > 10 && carPosition.z < 60)
		{
			//the car is in the southwest block
			Vector3 Center;
			Center.x = -35;
			Center.y = 0;
			Center.z = 35;

			//find the vector that points to the cars direction
			Vector3 projectionVector = carPosition - Center;
			projectionVector.normalize();  //added this to the vector3 struct

			float velocity = forVel.mag();

			reflectionVelocity = projectionVector*velocity;
		}
	}

	return reflectionVelocity;
}

void transportSimulation::Update()
{
	//car's forward direction
	Vector3 forward;
	forward.x = 0;
	forward.y = 0;
	forward.z = 1;
	Vector3 carForward = computeRotatedVector(forward, carDirection); //should be normalized

																	  //clamp the speed
	if (carSpeed > forwardLimit)
	{
		carSpeed = forwardLimit;
	}
	else if (carSpeed < reverseLimit)
	{
		carSpeed = reverseLimit;
	}

	/*carVelocity = sideWalkCollide();*/
	Vector3 carVelocity = carForward*carSpeed;
	otherVelocity = sideWalkCollide(carVelocity) * 2;

	totalVelocity = carVelocity + otherVelocity;

	carPosition = carPosition + totalVelocity; //movement due to collsisions as well

											   //for placing the camera
	Vector3 localCamRot = computeRotatedVector(localCameraOffset, carDirection);
	worldCameraOffset = carPosition + localCamRot;

	//add some drag for next time around
	carSpeed = carSpeed - drag*carSpeed;

	//stop other velocity if its low
	if (otherVelocity.mag() >= .1)
	{
		otherVelocity.x = 0;
		otherVelocity.y = 0;
		otherVelocity.z = 0;
	}
	else //reduce it like normal
	{
		otherVelocity = otherVelocity - otherVelocity*otherDrag;
	}

	//need to update multi billboard~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	mBoard.update();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//glViewport(winWidth - sWidth, winHeight - sHeight, sWidth, sHeight);  //this if for reference
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

}

//keyboard commands
void transportSimulation::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		// Add code for reset
		carPosition = { 3, 0, 45 };
		carSpeed = 0;
		carDirection = 180;
		break;
	case 'b':
		// Add code for breaking.
		carSpeed = 0;
		break;
	case 'c':
		//added code for toggling additional camera on and off
		if (additionalCameras == true)
		{
			additionalCameras = false;
		}
		else
		{
			additionalCameras = true;
		}
		break;
	case 's':
		//screen capture
		fullScreen.VerticalFlip(0, 0, winWidth, winHeight, "Captures/FullScreen.ppm");
		cout << "screen capture written" << endl;
		break;
	case 27:
		exit(0);
		break;
	}

	//glutPostRedisplay();
}

//drive car
void transportSimulation::SpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		carDirection += turnRate*carSpeed; //so the car does not move at idle and turns faster as you go faster
	}
	if (key == GLUT_KEY_RIGHT)
	{
		// Handle the right turns.
		carDirection -= turnRate*carSpeed;
	}
	if (key == GLUT_KEY_UP)
	{
		// acceleration
		carSpeed += acceleration;
	}
	if (key == GLUT_KEY_DOWN)
	{
		//deceleration
		carSpeed -= acceleration;
	}
	if (carDirection > 360)
	{
		carDirection -= 360;
	}
	else if (carDirection < 0)
	{
		carDirection += 360;
	}
}

void transportSimulation::MouseMove(int x, int y)
{
}

void transportSimulation::PassiveMouseMove(int x, int y)
{
}

//set heading text
void transportSimulation::setHeading()
{
	if (carDirection > 337.5 || carDirection < 22.5)
	{
		carHeading = "South";
	}
	else if (carDirection > 22.5 && carDirection< 67.5)
	{
		carHeading = "SouthEast";
	}
	else if (carDirection > 67.5 && carDirection< 112.5)
	{
		carHeading = "East";
	}
	else if (carDirection > 112.5 && carDirection< 157.5)
	{
		carHeading = "NorthEast";
	}
	else if (carDirection > 157.5 && carDirection< 202.5)
	{
		carHeading = "North";
	}
	else if (carDirection > 202.5 && carDirection< 247.5)
	{
		carHeading = "NorthWest";
	}
	else if (carDirection > 247.5 && carDirection< 292.5)
	{
		carHeading = "West";
	}
	else if (carDirection > 292.5 && carDirection< 337.5)
	{
		carHeading = "SouthWest";
	}
}

void transportSimulation::drawScene()
{
	// Draw terrain
	glCallList(terrainID);

	glEnable(GL_LIGHTING);

	// North-East (NS_Signal)
	glPushMatrix();
	glTranslatef(10, 0, -10.5);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	trafficLight.setSignal(NS_Signal);
	trafficLight.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -10);
	glRotatef(-45, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// South-West (NS_Signal)
	glPushMatrix();
	glTranslatef(-10, 0, 10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	trafficLight.setSignal(NS_Signal);
	trafficLight.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 10);
	glRotatef(135, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// South-East (WE_Signal)
	glPushMatrix();
	glTranslatef(10, 0, 10.5);
	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	trafficLight.setSignal(WE_Signal);
	trafficLight.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 10);
	glRotatef(-135, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// North-West (WE_Signal)
	glPushMatrix();
	glTranslatef(-10, 0, -10.5);
	glRotatef(90, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	trafficLight.setSignal(WE_Signal);
	trafficLight.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -10);
	glRotatef(45, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	//draw the props I added
	glPushMatrix();
	glTranslatef(25, 0, -25);
	glRotatef(-45, 0, 1, 0);
	glCallList(build4ID);
	glPopMatrix();


	//character is looking at building 4
	glPushMatrix();
	glTranslatef(15, 0, -15);
	glRotatef(45, 0, 1, 0);
	//scaled this model inside blender
	glCallList(shepID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, -20);
	glRotatef(90, 0, 1, 0);
	glCallList(build1ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, -40);
	glRotatef(90, 0, 1, 0);
	glCallList(build1ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 0, -20);
	//no rot face road
	glCallList(build1ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0, 20);
	glRotatef(180, 0, 1, 0);
	glCallList(build1ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0, 20);
	glRotatef(-90, 0, 1, 0);
	glCallList(build2ID);
	glPopMatrix();

	//multiple of these
	//rotate to face road
	glPushMatrix();
	glTranslatef(-20, 0, 20);
	glRotatef(90, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, 30);
	glRotatef(90, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, 40);
	glRotatef(90, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 0, 20);
	glRotatef(180, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 0, 20);
	glRotatef(180, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0, 40);
	glRotatef(-90, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0, 50);
	glRotatef(-90, 0, 1, 0);
	glCallList(build3ID);
	glPopMatrix();

	//sidewalks
	glPushMatrix();
	glTranslatef(35, 0, 35);
	glCallList(sidewalkID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, 35);
	glCallList(sidewalkID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, -35);
	glCallList(sidewalkID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35, 0, -35);
	glCallList(sidewalkID);
	glPopMatrix();

	//billboards~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glPushMatrix();
	glCallList(bill1ID);
	glPopMatrix();

	glPushMatrix();
	glCallList(bill2ID);
	glPopMatrix();

	glPushMatrix();
	glCallList(bill3ID);
	glPopMatrix();

	glPushMatrix();
	glCallList(bill4ID);
	glPopMatrix();

	//multi board
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glPushMatrix();
	mBoard.Draw();
	glPopMatrix();

	// Draw the car.
	glPushMatrix();
	glTranslatef(carPosition.x, carPosition.y, carPosition.z);
	glRotatef(carDirection, 0, 1, 0);
	glCallList(carID);
	glPopMatrix();

	//draw text
	glLoadIdentity();
	glColor3f(1, 0, 0);

	glRasterPos2f(0, 0);

	stringstream stream;
	stream << carSpeed;
	string speed = stream.str();
	printLargeString(speed);
}

void transportSimulation::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup viewport, projection, and camera for the main view.
	glViewport(0, 0, winWidth, winHeight); //removed a small offest and let other vieports draw over this on
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)winWidth / (winHeight), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//changed to worldCameral offset.  Updated for third person
	gluLookAt(worldCameraOffset.x, worldCameraOffset.y, worldCameraOffset.z, carPosition.x, carPosition.y + 1.5, carPosition.z, 0, 1, 0);

	// Generate head-up display (HUD)
	float realSpead = totalVelocity.mag();
	float speed = realSpead * 20;

	if (carSpeed < 0)
	{
		speed *= -1;
	}

	//draw the text
	glColor3f(1, 0, 0);
	glRasterPos3f(carPosition.x, (carPosition.y + 2), carPosition.z);

	stringstream stream;
	stream << speed;
	stream << " KPH";
	string speedString = stream.str();
	printLargeString(speedString);

	glRasterPos3f(carPosition.x, (carPosition.y + 2.5), carPosition.z);;
	setHeading();
	printLargeString(carHeading);

	drawScene();

	//this following condition is here to allow the option of better perfomance by turning these cameras off
	if (additionalCameras)
	{
		// Setup viewport, projection, and camera for the South-East camera and draw the scene again.
		glViewport(winWidth - sWidth, winHeight - sHeight, sWidth, sHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(30, (float)sWidth / (sHeight), 1, 100); //doesn't need to see far
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(10, 2, 10, 0, 1, 0, 0, 1, 0);
		drawScene();

		// Setup the viewport, projection, camera for the top view and draw the scene again.
		glViewport(winWidth / 2 - sWidth / 2, winHeight - sHeight, sWidth, sHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-100, 100, -100 * sHeight / sWidth, 100 * sHeight / sWidth, -1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(carPosition.x, 400, carPosition.z, carPosition.x, carPosition.y, carPosition.z, 0, 0, -1);
		drawScene();

		// Setup viewport, projection, camera for the South-West camera and draw the scene again.
		glViewport(0, winHeight - sHeight, sWidth, sHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(30, (float)sWidth / (sHeight), 1, 100); //doesn't need to see far
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-10, 2, 10, 0, 1, 0, 0, 1, 0);
		drawScene();
	}
	glutSwapBuffers();
	glFlush();

}