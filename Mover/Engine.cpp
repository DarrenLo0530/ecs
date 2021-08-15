#include "Engine.h"

#include <chrono>
#include <iostream>

const float UPS = 30.0f;
const float secondsPerUpdate = 1.0 / UPS;
const int maxFPSSamples = 5;

double getCurrentTime() {
	auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

Engine::Engine(Window* window, Game* game) {
	// Link window to game
	this->window = window;
	this->game = game;

	game->setWindow(*window);
	game->init();
}

void Engine::run() {
	prevTime = getCurrentTime();

	while (!window->isClosed()) {
		window->clear();

		double currTime = getCurrentTime();
		double timeElapsed = currTime - prevTime;
		prevTime = currTime;
		accumulator += timeElapsed;

		while (accumulator >= secondsPerUpdate) {
			// Update game logic in a fixed time step
			accumulator -= secondsPerUpdate;
			game->update();
		}

		// Calculate fps
		updateFPS(timeElapsed);

		// Render the game with interpolation for variable frame rate
		float renderInterpolation = (float)accumulator / (float) secondsPerUpdate;
		game->render(renderInterpolation);
		window->update();
	}
}

void Engine::updateFPS(double timeElapsed) {
	if (currSample == maxFPSSamples) {
		fps = avgFps / maxFPSSamples;

		currSample = 0;
		avgFps = 0.0;
	} else {
		avgFps += 1.0f / (float) timeElapsed;
	}
}