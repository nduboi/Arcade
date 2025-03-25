/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNcursesEvent
*/

#include "arcadeNcursesEvent.hpp"

arcadeNcursesEvent::arcadeNcursesEvent(IWindow &window) : _window(window)
{

}

void arcadeNcursesEvent::init()
{

}

IEvent::event_t arcadeNcursesEvent::pollEvents(std::pair<int, int> gridSize)
{
    int ch = getch();

    if (ch == -1)
        return IEvent::NOTHING;
    switch (ch) {
        case KEY_UP: return IEvent::UP;
        case KEY_DOWN: return IEvent::DOWN;
        case KEY_LEFT: return IEvent::LEFT;
        case KEY_RIGHT: return IEvent::RIGHT;
        case 'n' : return IEvent::NEXTGRAPHIC;
        case 'g' : return IEvent::NEXTGAME;
        case 'r' : return IEvent::REFRESH;
        case 'q': return IEvent::CLOSE;
        default: return IEvent::NOTHING;
    }
}

std::pair<int, int> arcadeNcursesEvent::getMousePos()
{
    // je sais pas trop comment faire
    return {0, 0};
}

void arcadeNcursesEvent::cleanup()
{

}

void arcadeNcursesEvent::setMapSize(std::pair<int, int> size) {
}
