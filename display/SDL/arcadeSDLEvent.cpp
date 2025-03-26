/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDLEvent
*/

#include "arcadeSDLEvent.hpp"

#include <iostream>
#include <memory>

void arcadeSDLEvent::init() {
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        if (SDL_NumJoysticks() > 0) {
            SDL_JoystickOpen(0);
        }
    }
}

IEvent::event_t arcadeSDLEvent::pollEvents(std::pair<int, int> gridSize) {
    SDL_Event event;
    auto &sdlWindow = static_cast<arcadeSDL &>(_window);

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return IEvent::CLOSE;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return IEvent::UP;
                case SDLK_DOWN:
                    return IEvent::DOWN;
                case SDLK_LEFT:
                    return IEvent::LEFT;
                case SDLK_RIGHT:
                    return IEvent::RIGHT;
                case SDLK_ESCAPE:
                    return IEvent::ESCAPE;
                case SDLK_SPACE:
                    return IEvent::SPACE;
                case SDLK_RETURN:
                    return IEvent::ENTER;
                case SDLK_F4:
                    return IEvent::NEXTGAME;
                case SDLK_F5:
                    return IEvent::REFRESH;
                case SDLK_F6:
                    return IEvent::NEXTGRAPHIC;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&this->_mousePos.first, &this->_mousePos.second);
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    return IEvent::MOUSELEFTCLICK;
                case SDL_BUTTON_RIGHT:
                    return IEvent::MOUSERIGHTCLICK;
                case SDL_BUTTON_MIDDLE:
                    return IEvent::MOUSECLICK;
            }
        }
        if (event.type == SDL_JOYAXISMOTION) {
            if (event.jaxis.axis == 0) { // X axis
                if (event.jaxis.value > 3200)
                    return IEvent::RIGHT;
                else if (event.jaxis.value < -3200)
                    return IEvent::LEFT;
            }
            if (event.jaxis.axis == 1) { // Y axis
                if (event.jaxis.value > 3200)
                    return IEvent::DOWN;
                else if (event.jaxis.value < -3200)
                    return IEvent::UP;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
            return IEvent::MOUSECLICK;
    }
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeSDLEvent::getMousePos()
{
    auto &sdlWindow = static_cast<arcadeSDL &>(_window);

    if (_mapSize.first > 0 && _mapSize.second > 0) {
        int winWidth, winHeight;
        SDL_GetWindowSize(sdlWindow._window, &winWidth, &winHeight);
        return {
            (this->_mousePos.first * _mapSize.first) / winWidth,
            (this->_mousePos.second * _mapSize.second) / winHeight
        };
    }
    return this->_mousePos;
}

void arcadeSDLEvent::setMapSize(std::pair<int, int> size) {
    _mapSize = size;
}

void arcadeSDLEvent::cleanup() {
}

arcadeSDLEvent::arcadeSDLEvent(IWindow &window) : _window(window) {
    _mousePos = std::make_pair(0, 0);
    _mapSize = std::make_pair(0, 0);
}
