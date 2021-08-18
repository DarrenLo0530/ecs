#pragma once
#include "Component.h"
#include "EntityHandle.h"

struct View : public Component<View> {
	EntityHandle viewCamera;
};