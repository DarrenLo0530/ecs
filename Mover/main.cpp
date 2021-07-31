#include "Window.h"
#include <iostream>


int main() {
	Window window = Window("Hello", 1920, 1080);
	while (!window.isClosed()) {
		window.clear();
		window.update();
	}
}