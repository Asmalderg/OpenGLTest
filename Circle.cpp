#include "Circle.h"
#include <iostream>
#include <gl/glut.h>
#include <cmath>

Circle::Circle(const std::vector<Coordinate>& coordinates) : Figure(coordinates)
{
	Coordinate center = {vertices[0], vertices[1], vertices[2]};
	Coordinate radiusDot = {vertices[3], vertices[4], vertices[5]};

	vertices.clear();
	radius = sqrt(pow(center.x - radiusDot.x,2) + pow(center.y - radiusDot.y,2));

	float pi2 = 3.14 * 2;

	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	

	for (int i = 0; i < numberOfVerticis; ++i) 
	{
		float x = radius * cos((pi2 * i)/360);
		float y = radius * sin((pi2 * i)/360);
		float z = 0;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}
	vertices.push_back(radius);
	vertices.push_back(0);
	vertices.push_back(0);
}

void Circle::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
    
}

Circle::~Circle()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
