/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDL
*/

#include <iostream>
#include "arcadeSDL.hpp"

void arcadeSDL::initWindow() {
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }
    if (SDL_NumJoysticks() > 0) {
        SDL_JoystickOpen(0);
    }

    if (this->_window == nullptr || this->_renderer == nullptr) {
        this->_window = SDL_CreateWindow("Arcade - SDL2",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        800, 600,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if (!this->_window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        this->_renderer = SDL_CreateRenderer(this->_window, -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!this->_renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(this->_window);
            SDL_Quit();
            return;
        }
        SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->_renderer);
        SDL_RenderPresent(this->_renderer);
    }
}

void arcadeSDL::display() {
    SDL_RenderPresent(this->_renderer);
}

void arcadeSDL::closeWindow() {
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
	this->_window = nullptr;
	this->_renderer = nullptr;
}

bool arcadeSDL::isOpen() {
    return (this->_window != nullptr && this->_renderer != nullptr);
}

void arcadeSDL::clear() {
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);
}

arcadeSDL::arcadeSDL() : _window(nullptr), _renderer(nullptr)
{
}

arcadeSDL::~arcadeSDL() {
    if (this->isOpen()) {
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);
        SDL_Quit();
    }
}
