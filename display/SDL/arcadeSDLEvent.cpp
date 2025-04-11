/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDLEvent
*/

#include "arcadeSDLEvent.hpp"

#include <iostream>
#include <memory>
#include <utility>

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
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return IEvent::CLOSE;

        if (this->_iswritting) {
            if (event.type == SDL_TEXTINPUT) {
                if (this->_input.length() <= 15)
                    this->_input += event.text.text;
                return IEvent::NOTHING;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) {
                if (!this->_input.empty())
                    this->_input.pop_back();
                return IEvent::NOTHING;
            }
        }
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
                case SDLK_g:
                    return IEvent::NEXTGAME;
                case SDLK_r:
                    return IEvent::REFRESH;
                case SDLK_n:
                    return IEvent::NEXTGRAPHIC;
                case SDLK_m:
                    return IEvent::MENU;
                case SDLK_h:
                    return IEvent::NEXTDIFFICULTY;
                case SDLK_q:
                    return IEvent::CLOSE;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&this->_mousePos.first, &this->_mousePos.second);
            if (this->_mousePos.first >= 725 && this->_mousePos.first <= 900 && this->_mousePos.second >= 120 && this->_mousePos.second <= 180)
                this->_iswritting = true;
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
    auto sdlWindow = std::dynamic_pointer_cast<arcadeSDL>(this->_window);
    const int hudOffset = 100;

    if (_mousePos.first < 0 || _mousePos.second < hudOffset)
        return {-1, -1};
    if (this->_mapSize.first > 0 && this->_mapSize.second > 0) {
        auto WinSize = sdlWindow->sdl->getWindowSize();
        return {
            (this->_mousePos.first * this->_mapSize.first) / WinSize.first,
            ((this->_mousePos.second - hudOffset) * this->_mapSize.second) / (WinSize.second - hudOffset)
        };
    }
    return this->_mousePos;
}

void arcadeSDLEvent::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

void arcadeSDLEvent::cleanup() {
}

std::string arcadeSDLEvent::getUsername()
{
    return this->_input;
}

void arcadeSDLEvent::renderWrittiing()
{
    this->_window->drawTextMenu(
        _input,
        {685, 407},
        {0, 0, 0},
        24
    );
}

arcadeSDLEvent::arcadeSDLEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = std::make_pair(0, 0);
    this->_mapSize = std::make_pair(0, 0);
    this->_iswritting = false;
}
