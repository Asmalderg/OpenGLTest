#include "Triangle.h"
#include <iostream>
Triangle::Triangle(const std::vector<Coordinate>& coordinates) : Figure(coordinates)
{
}

void Triangle::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
