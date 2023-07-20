#include "Figure.h"
#include "ShaderManipulator.h"
#include "Coordinates.h"
#include <string>
#include <iostream>
#include <cstring>

Figure::Figure(const std::vector<Coordinate> &coordinates)
{
	for (int i = 0; i < coordinates.size(); ++i)
	{
		Coordinate coordinate = coordinates[i];
		vertices.push_back(coordinate.x);
		vertices.push_back(coordinate.y);
		vertices.push_back(coordinate.z);
	}
}

GLuint Figure::getVBO()
{
	return VBO;
}

GLuint Figure::getVAO()
{
	return VAO;
}

GLuint Figure::getShader()
{
	return shader;
}

void Figure::draw()
{
	std::cout << "Implement class method" << std::endl;
}

Figure::~Figure() {}

bool Figure::compileShader()
{
	shader = glCreateProgram();

	if (!shader)
	{
		std::cout << "Gl create program error occured" << std::endl;
		return false;
	}

	std::string vertexPath(ASSETS_DIR);
	vertexPath += "/vertex.glsl";
	std::string vShader = loadShaderFromFile(vertexPath);

	std::string colourPath(ASSETS_DIR);
	colourPath += "/colour.glsl";
	std::string fShader = loadShaderFromFile(colourPath);

	AddShader(vShader.c_str(), GL_VERTEX_SHADER);
	AddShader(fShader.c_str(), GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Linking shaders error" << std::endl;
		return false;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error validation program" << std::endl;
		return false;
	}
	return true;
}

void Figure::createFigure()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	auto vectorSize = sizeof(vertices[0]) * vertices.size();
	glBufferData(GL_ARRAY_BUFFER, vectorSize, vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool Figure::AddShader(const char *shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar *theCode[1] = {shaderCode};

	const GLint codeLength[1] = {(GLint)(std::strlen(shaderCode))};

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error while compiling the shader" << std::endl;
		return false;
	}

	glAttachShader(shader, theShader);
	return true;
}
