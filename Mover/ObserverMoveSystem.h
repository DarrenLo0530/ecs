#pragma once

#include "System.h"
#include "Window.h"

class ObserverMoveSystem : UpdateSystem {
private:
	Window::Input* input;

public:
	void setInput(Window::Input* input);
};