#pragma once
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
	GLFWwindow* window;
	int width, height;
	const char* title;
	
	inline Window(const char* title, int width, int height)
	{
		this->width = width;
		this->height = height;
		this->title = title;
	}
	inline void create()
	{
		glfwInit();
		this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
		glfwMakeContextCurrent(this->window);
		glewInit();
	}
	inline bool shouldClose()
	{
		return glfwWindowShouldClose(this->window);
	}
	inline void clear(float x, float y, float z, float w)
	{
		glClearColor(x, y, z, w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	inline void update()
	{
		glfwPollEvents();
	}
	inline void render()
	{
		glfwSwapBuffers(this->window);
	}
};