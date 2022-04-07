#ifndef TRANSDATA_H
#define TRANSDATA_H

#include "ObjModel.h"
#include "TrafficLight.h"
#include "BillBoard.h"
#include "MultiBoard.h"

#include <ctime>
#include <string>>

namespace transData
{
	// Counter for the traffic signal.  Only one is needed.
	int counter = 0;

	// 20 miliseconds
	int updateInterval = 20;

	// 3D models
	ObjModel car, surveillanceCamera;
	//added declarations for my buildings I made in blender
	ObjModel building1, building2, building3, building4, shepard; //Shepard is the name of the ME3 character, whom I believe was named after Alan Shepard the first American in space
	TrafficLight trafficLight;

	// The display list IDs for car, surveillanceCamera, and terrain.
	int carID, surveillanceCameraID, terrainID;

	//add id's for buildings and character;
	int build1ID, build2ID, build3ID, build4ID, shepID;

	//added sidewalk
	ObjModel sidewalk;
	int sidewalkID;

	// Signals for North-South traffic and West-East traffic
	Signal NS_Signal = Green, WE_Signal = Red;

	// Car data
	Vector3 carPosition = { 3, 0, 45 };

	float carDirection = 180;
	string carHeading = "N";

	//more car data
	float turnRate = 4.5; //over keyboard update, this will be multiplied by speed
	float acceleration = .15; //over 20ms 
	float decell = .3;
	float carSpeed = 0; //over 20ms
	Vector3 carVelocity = { 0, 0, 0 };
	float forwardLimit = 10; //over 20msec
	float reverseLimit = -1; //over 20msec
	float drag = .01;

	Vector3 otherVelocity;
	Vector3 totalVelocity;
	float otherDrag = .1;
	// Third person camera offset in the car's local frame and world frame.
	//changed the offset
	Vector3	localCameraOffset = { 0, 2, -12 }, worldCameraOffset;

	// Width and height for the window and three small viewports.
	int winWidth, winHeight, sWidth, sHeight;

	bool additionalCameras = false;

	//billboards
	Billboard bill1, bill2, bill3, bill4;
	//display lists for billboards
	int bill1ID, bill2ID, bill3ID, bill4ID;

	//for the multi image billBoard
	multiBoard mBoard;
	int mBoardID;

	//PPM image for the fullscreen capture
	PPMImage fullScreen;

	//for the traffic violation
	PPMImage soutEastcam_NorthBound;
	bool northRed = true;
}

#endif // !TRANSDATA_H