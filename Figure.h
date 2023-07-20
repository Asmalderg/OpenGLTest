#pragma once
#include "Coordinates.h"
#include <vector>

class Figure
{
public:
	Figure(const std::vector<Coordinate> &coordinates);
	GLuint getVBO();
	GLuint getVAO();
	GLuint getShader();
	virtual void draw();
	virtual ~Figure();
	void createFigure();
	bool compileShader();

protected:
	bool AddShader(const char *shaderCode, GLenum shaderType);
	std::vector<GLfloat> vertices;
	GLuint VAO, VBO, shader;
};