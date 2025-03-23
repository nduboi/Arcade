/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDL
*/

#include <iostream>
#include "arcadeSDL.hpp"
#include <SDL2/SDL_image.h>

void arcadeSDL::initWindow()
{
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

std::pair<int, int> arcadeSDL::_getWindowPosition(std::pair<int, int> position)
{
    std::pair<int, int> windowPosition;
    int width, height;

    SDL_GetWindowSize(this->_window, &width, &height);
    windowPosition.first = (position.first * width) / this->_mapSize.first;
    windowPosition.second = (position.second * height) / this->_mapSize.second;

    return windowPosition;
}

void arcadeSDL::_resizeTexture(SDL_Rect &rect, std::pair<int, int> position)
{
    int width, height;

    SDL_GetWindowSize(this->_window, &width, &height);
    rect.w = width / this->_mapSize.first + 0.1;
    rect.h = height / this->_mapSize.second + 0.1;
}

void arcadeSDL::drawSprite(std::string asset, int color, std::pair<int, int> position) {
    SDL_Surface *surface = IMG_Load(asset.c_str());
    if (!surface) {
        std::cerr << "Error loading image: " << IMG_GetError() << std::endl;
        this->drawRectangle(color, position);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    SDL_FreeSurface(surface); // Free the surface right after creating the texture

    if (!texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        this->drawRectangle(color, position);
        return;
    }

    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
    SDL_Rect destRect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(destRect, position);

    SDL_RenderCopy(this->_renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture); // Always destroy the texture after use
}

void arcadeSDL::drawRectangle(int color, std::pair<int, int> position) {
    (void)color;
    (void)position;
}

void arcadeSDL::drawText(std::string text, int color, std::pair<int, int> position) {
    (void)text;
    (void)color;
    (void)position;
}

void arcadeSDL::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

arcadeSDL::arcadeSDL() : _window(nullptr), _renderer(nullptr)
{
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }
    if (SDL_NumJoysticks() > 0) {
        SDL_JoystickOpen(0);
    }
    this->_window = SDL_CreateWindow("Arcade - SDL2",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    800, 800,
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
    this->_mapSize = {0, 0};
}

arcadeSDL::~arcadeSDL() {
    std::cout << "Calling SDL destructor" << std::endl;
    if (this->isOpen()) {
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);
        IMG_Quit();
        SDL_Quit();
    }
}
