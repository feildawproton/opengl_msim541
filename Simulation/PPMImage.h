#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PPMImage
{
public:
	PPMImage(void);
	~PPMImage(void);
	int width, height;
	unsigned char* image; //the image itself
	void AllocateMemory(int width, int height);
	void ReadFile(string fileName);
	//use this function to take a screen capture
	void VerticalFlip(int X, int Y, int width, int height, string fileName); 
	void WriteFile(string fileName, string fileType);

private:
	char c, buf[128];
	ifstream file;
	ofstream outFile;
	void CheckComment();
};

