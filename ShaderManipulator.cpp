#include "ShaderManipulator.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string loadShaderFromFile(std::string filePath)
{
	std::ifstream file;
	std::stringstream ss;

	file.open(filePath);
	if (file.is_open())
	{
		ss << file.rdbuf();
		return ss.str();
	}
	else
	{
		std::cout << "File open Error" << std::endl;
	}
	file.close();
	return "";
}