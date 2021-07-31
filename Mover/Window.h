#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string> 

#pragma once
class Window
{
private:
	GLFWwindow* id;
	unsigned int width;
	unsigned int height;
public:
	Window(const std::string& title, unsigned int width, unsigned int height);
	~Window();

	void clear() const;
	void update() const;
	bool isClosed() const;

	unsigned int getWidth() const ;
	unsigned int getHeight() const;

private:
	static void framebuffer_size_callback(GLFWwindow* id, int width, int height);
	static void key_callback(GLFWwindow* id, int key, int scancode, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* id, double xPos, double yPos);
};

