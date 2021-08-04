#include "Engine.h"

#include <chrono>
#include <iostream>

const double updateRate = 1.0 / 60.0;
const int maxSamples = 5;

double getCurrentTime() {
	auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

Engine::Engine(Window* window, Game* game) {
	// Link window to game
	this->window = window;
	this->game = game;

	game->setInputs(&(window->getInputs()));
}

void Engine::run() {
	prevTime = getCurrentTime();

	while (!window->isClosed()) {
		double currTime = getCurrentTime();
		double timeElapsed = currTime - prevTime;
		prevTime = currTime;
		accumulator += timeElapsed;

		while (accumulator >= updateRate) {
			// Update game logic in a fixed time step
			accumulator -= updateRate;
			game->update();
		}

		// Calculate fps
		updateFPS(timeElapsed);

		// Render the game with interpolation for variable frame rate
		float renderInterpolation = (float)accumulator / (float) updateRate;
		game->render(renderInterpolation);
	}
}

void Engine::updateFPS(double timeElapsed) {
	if (currSample == maxSamples) {
		fps = avgFps / maxSamples;

		currSample = 0;
		avgFps = 0.0;
	} else {
		avgFps += 1.0f / (float) timeElapsed;
	}
}