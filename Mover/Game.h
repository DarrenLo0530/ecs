#pragma once

#include "Window.h"

class Game {
protected:
	const Window::Input* inputs = NULL;
public:
	virtual ~Game() = default;

	// Update components (including input component for player)
	virtual void update() = 0;

	// Render the game
	virtual void render(float interpolation) = 0;

	void setInputs(const Window::Input* inputs) {
		this->inputs = inputs;
	}
};

