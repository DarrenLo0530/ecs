#pragma once

#include "Window.h"
#include <iostream>
class Game {
public:
	const Window::Input* inputs = NULL;
	const Window::Dimensions* dimensions;
public:
	virtual ~Game() = default;

	virtual void init() = 0;

	// Update components (including input component for player)
	virtual void update() = 0;

	// Render the game
	virtual void render(float interpolation) = 0;

	void setWindow(const Window& window) {
		this->inputs = &(window.getInputs());
		this->dimensions = &(window.getDimensions());
	}

};

