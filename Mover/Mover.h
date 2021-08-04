#pragma once
#include "Game.h"

class Mover : public Game {
public:
	void render(float interpolation);
	void update();
};