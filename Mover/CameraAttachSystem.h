#pragma once
#include "System.h"

class CameraAttachSystem : public UpdateSystem {
public:
	void init() override;
	void update() override;
};