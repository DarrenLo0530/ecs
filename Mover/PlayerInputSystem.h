#pragma once
#include "System.h"

class PlayerInputSystem : public UpdateSystem {
private:
	bool firstMousePoll = true;
	float prevMouseX, prevMouseY;
public:
	void init() override;
	void update() override;
};	