//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeCacaEvent.hpp"

void arcadeCacaEvent::init() {
}

int arcadeCacaEvent::pollEvents() {
	return 0;
}

void arcadeCacaEvent::cleanup() {
}

arcadeCacaEvent::arcadeCacaEvent(IWindow &window) : _window(window){
}
