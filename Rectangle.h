#pragma once
#include "Figure.h"

class Rectangle : public Figure
{
public:
	Rectangle(const std::vector<Coordinate>& coordinates);
	void draw() override;
	~Rectangle();
};
