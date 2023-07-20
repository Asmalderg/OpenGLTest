#include "Graphics.h"
#include <iostream>
#include "ShaderManipulator.h"

graphic::Window::Window(const int width_, const int height_)
	: width(width_), height(height_)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool graphic::Window::drawFigure(Figure &figure)
{
	window = glfwCreateWindow(width, height, "OpenGL driven window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, width, height);

	figure.createFigure();
	figure.compileShader();

	VAO = figure.getVAO();
	VBO = figure.getVBO();
	shader = figure.getShader();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		// Wait for input
		handleInput();

		// Clear the window
		glClearColor(.1f, .1f, .1f, .2f);
		glClear(GL_COLOR_BUFFER_BIT);

		figure.draw();

		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return true;
}

graphic::Window::~Window()
{
	glfwTerminate();
}

void graphic::framebuffer_size_callback(GLFWwindow *window_, int width,
										 int height)
{
	glViewport(0, 0, width, height);
}

void graphic::Window::handleInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

bool graphic::Window::compileShader() {
        shader = glCreateProgram();

	if (!shader)
	{
		std::cout << "Gl create program error occured" << std::endl;
		return false;
	}

	std::string vertexPath = std::string(ASSETS_DIR) +  "/vertex.glsl";
	std::string vShader = loadShaderFromFile(vertexPath);

	std::string colourPath = std::string(ASSETS_DIR) + "/colour.glsl";
	std::string fShader = loadShaderFromFile(colourPath);

	addShader(shader, vShader.c_str(), GL_VERTEX_SHADER);
	addShader(shader, fShader.c_str(), GL_FRAGMENT_SHADER);

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

bool graphic::Window::addShader(GLuint shaderId, const char *shaderCode,
								 GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar *theCode[1] = {shaderCode};
	const GLint codeLength[1] = {(GLint)strlen(shaderCode)};

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

	glAttachShader(shaderId, theShader);
	return true;
}
