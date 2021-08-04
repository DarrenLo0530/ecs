#pragma once

#include "Window.h"
#include "Game.h"

class Engine {
private:
	Window* window;
	Game* game;

	// FPS data
	float fps			= 0.0;
	float avgFps		= 0.0;
	int currSample		= 0;

	// Rendering data
	double prevTime		= 0.0;
	double accumulator  = 0.0;
public:
	Engine(Window* window, Game* game);

	void run();
private:
	void updateFPS(double timeElapsed);
};

