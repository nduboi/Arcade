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

std::pair<int, int> arcadeSDLEvent::getMousePos() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return {x, y};
}

void arcadeSDLEvent::cleanup() {
}

arcadeSDLEvent::arcadeSDLEvent(IWindow &window) : _window(window) {
}
