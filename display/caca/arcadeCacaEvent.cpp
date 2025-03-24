//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeCacaEvent.hpp"

void arcadeCacaEvent::init() {
}

IEvent::event_t arcadeCacaEvent::pollEvents(std::pair<int, int> gridSize) {
	return static_cast<IEvent::event_t>(-1);
}

std::pair<int, int> arcadeCacaEvent::getMousePos() {
	return {};
}

void arcadeCacaEvent::cleanup() {
}

arcadeCacaEvent::arcadeCacaEvent(IWindow &window) : _window(window){
}
