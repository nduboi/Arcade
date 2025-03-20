//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeCacaEvent.hpp"

void arcadeCacaEvent::init() {
}

int arcadeCacaEvent::pollEvents(std::pair<int, int> gridSize) {
	return 0;
}

std::pair<int, int> arcadeCacaEvent::getMousePos() {
	return {};
}

void arcadeCacaEvent::cleanup() {
}

arcadeCacaEvent::arcadeCacaEvent(IWindow &window) : _window(window){
}
