/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNCURSESEvent
*/

#include "arcadeNCURSESEvent.hpp"

#include <complex.h>
#include <iostream>
#include <memory>
#include <ncurses.h>

void arcadeNCURSESEvent::init() {
}

IEvent::event_t arcadeNCURSESEvent::pollEvents(std::pair<int, int> gridSize) {
    int ch = getch();
    MEVENT event;
    arcadeNCURSES &window = static_cast<arcadeNCURSES &>(this->_window);

    switch(ch) {
        case 27:
            return IEvent::ESCAPE;
        case KEY_UP:
            return IEvent::UP;
        case KEY_DOWN:
            return IEvent::DOWN;
        case KEY_LEFT:
            return IEvent::LEFT;
        case KEY_RIGHT:
            return IEvent::RIGHT;
        case KEY_F(6):
            return IEvent::NEXTGRAPHIC;
        case KEY_F(5):
            return IEvent::REFRESH;
        case KEY_F(4):
            return IEvent::NEXTGAME;
    }
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    if (ch == KEY_MOUSE) {
        if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {
            if (event.y == window.poxYCloseButton && event.x >= window.poxXCloseButton && event.x <= window.poxXCloseButton + 2) {
                return IEvent::CLOSE;
            }
        }
    }
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeNCURSESEvent::getMousePos() {
    return {};
}

void arcadeNCURSESEvent::cleanup() {
}

arcadeNCURSESEvent::arcadeNCURSESEvent(IWindow &window) : _window(window) {
}
