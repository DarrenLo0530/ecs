#pragma once
#include "System.h"

class PlayerInputSystem : public UpdateSystem {
public:
	void init() override;
	void update() override;
};