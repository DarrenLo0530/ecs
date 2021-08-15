#pragma once
#include "Game.h"
#include "World.h"
#include "EntityHandle.h"

class Mover : public Game {
private:
	World* gameWorld;
	EntityHandle camera;
public:
	void init() override;
	void render(float interpolation) override;
	void update() override;
};