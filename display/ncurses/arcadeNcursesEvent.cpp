/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNcursesEvent
*/

#include <iostream>
#include <memory>
#include "arcadeNcursesEvent.hpp"

void arcadeNcursesEvent::init() {
}

IEvent::event_t arcadeNcursesEvent::pollEvents(std::pair<int, int> gridSize)
{
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeNcursesEvent::getMousePos() {
    return {0, 0};
}

void arcadeNcursesEvent::cleanup() {
}

arcadeNcursesEvent::arcadeNcursesEvent(IWindow &window) : _window(window) {
}
