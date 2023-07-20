#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Figure.h"

namespace graphic
{
	class Window
	{
	public:
		explicit Window(const int width_, const int height_);
		bool drawFigure(Figure &figure);
		~Window();
	private:
		const GLint width, height;
		GLFWwindow *window;
		GLuint VAO, VBO, shader;

		bool compileShader();
		bool addShader(GLuint shaderId, const char *shaderCode, GLenum shaderType);
		void handleInput();
	};
	void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};