#pragma once
#include "Figure.h"

class Circle : public Figure
{
public:
	Circle(const std::vector<Coordinate>& coordinates);
	void draw() override;
	~Circle();
private:
    int numberOfVerticis = 362;
    float radius;
};
