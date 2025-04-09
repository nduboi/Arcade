//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeQTEvent.hpp"

#include <iostream>
#include <memory>
#include <utility>

void arcadeQTEvent::init()
{
}

IEvent::event_t arcadeQTEvent::pollEvents(std::pair<int, int> gridSize) {
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeQTEvent::getMousePos()
{
    return {0, 0};
}

void arcadeQTEvent::setMapSize(std::pair<int, int> size) {
    _mapSize = size;
}

void arcadeQTEvent::cleanup() {
}

std::string arcadeQTEvent::getUsername()
{
    return _input;
}

void arcadeQTEvent::renderWrittiing()
{
}

arcadeQTEvent::arcadeQTEvent(std::shared_ptr<IWindow> window) : _window(window) {
}
