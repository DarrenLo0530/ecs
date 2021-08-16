#pragma once
#include "Window.h"
#include "Component.h"

struct PlayerInput : public Component<PlayerInput> {
	const Window::Input* input;
};