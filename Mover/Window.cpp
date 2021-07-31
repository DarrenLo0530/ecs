#include <iostream>

#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const std::string& title, unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	id = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	// Check that GLFW was initiailized properly
	if (id == NULL) {
		glfwTerminate();
		std::cout << "Unable to create window" << std::endl;
	}

	glfwMakeContextCurrent(id);
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set callbacks
	glfwSetWindowUserPointer(id, this);
	glfwSetKeyCallback(id, key_callback);
	glfwSetFramebufferSizeCallback(id, framebuffer_size_callback);
	glfwSetCursorPosCallback(id, )

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, width, height);
}

Window::~Window() {
	glfwTerminate();
}

void Window::clear() const {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() const {
	glfwPollEvents();
	glfwSwapBuffers(id);
}

bool Window::isClosed()  const {
	return glfwWindowShouldClose(id);
}

/* Getters and setters */
unsigned int Window::getWidth() const {
	return width;
}

unsigned int Window::getHeight() const {
	return height;
}

void Window::key_callback(GLFWwindow* id, int key, int scancode, int action, int mods) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(id));
}

void Window::framebuffer_size_callback(GLFWwindow* id, int width, int height) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(id));
	window->height = height;
	window->width = width;
	glViewport(0, 0, width, height);
}

void Window::cursor_pos_callback(GLFWwindow* id, double xPos, double yPos) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(id));

}
