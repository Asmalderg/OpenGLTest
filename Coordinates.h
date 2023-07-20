#pragma once
#include <glad/glad.h>

struct Coordinate
{
	Coordinate() : x(0), y(0), z(0)
	{
	}
	Coordinate(float i, float j, float k)
		: x(i), y(j), z(k)
	{
	}
	GLfloat x, y, z;
};