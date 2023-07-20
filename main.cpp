#include <iostream>
#include "ShaderManipulator.h"
#include "Graphics.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

int main(int argc, char *argv[])
{
	Coordinate one{-0.5f, 0.0f, 0.0f}, two{0.0f, 0.5f, 0.0f}, three{0.5f, 0.0f, 0.0f};
	const std::vector<Coordinate> v = {one, two, three};
	Triangle figure(v);

	// Coordinate one{-0.5f,-0.5f, 0.0f}, two{-0.5f, 0.5f, 0.0f}, three{0.5f, -0.5f, 0.0f}, four{0.5f, 0.5f, 0.0f};
	// const std::vector<Coordinate> v = {one, two, three, four};
	// Rectangle figure(v);

	// Coordinate center{.0f, .5f, .0f}, radius{0.5f, 0.5f, 0.0f};
	// const std::vector<Coordinate> v = {center, radius};
	// Circle figure(v);


	graphic::Window win(1024, 768);
	win.drawFigure(figure);
	return 0;
}