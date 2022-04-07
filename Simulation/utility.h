#pragma once
#include <string>
#include <gl/glut.h>
#include "Vector3D.h"

using namespace std;

void printString(string str);
void printLargeString(string str);

Vector3 computeRotatedVector(Vector3 input, float angle);

Vector3 project(const Vector3& a, const Vector3& b);

float dot(const Vector3& a, const Vector3& b);