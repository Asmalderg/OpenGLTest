#pragma once
#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle(const std::vector<Coordinate>& coordinates);
	void draw() override;
	~Triangle();
};
