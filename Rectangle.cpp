#include "Rectangle.h"
#include <iostream>
Rectangle::Rectangle(const std::vector<Coordinate>& coordinates) : Figure(coordinates)
{
}

void Rectangle::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VAO);
	glDrawArrays(  GL_TRIANGLE_STRIP, 0, 4);
}

Rectangle::~Rectangle()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
