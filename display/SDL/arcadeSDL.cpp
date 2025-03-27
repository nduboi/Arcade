/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDL
*/

#include <iostream>
#include "arcadeSDL.hpp"
#include <SDL2/SDL_image.h>

void arcadeSDL::_initWindow()
{
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }
    if (SDL_NumJoysticks() > 0) {
        SDL_JoystickOpen(0);
    }

    if (this->window == nullptr || this->renderer == nullptr) {
        this->window = SDL_CreateWindow("Arcade - SDL2",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        800, 800,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if (!this->window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!this->renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(this->window);
            SDL_Quit();
            return;
        }
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);
        SDL_RenderPresent(this->renderer);
    }
}

void arcadeSDL::display() {
    SDL_RenderPresent(this->renderer);
}

void arcadeSDL::closeWindow() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
	this->window = nullptr;
	this->renderer = nullptr;
}

bool arcadeSDL::isOpen() {
    return (this->window != nullptr && this->renderer != nullptr);
}

void arcadeSDL::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

std::pair<int, int> arcadeSDL::_getWindowPosition(std::pair<int, int> position)
{
    std::pair<int, int> windowPosition;
    int width, height;

    SDL_GetWindowSize(this->window, &width, &height);
    windowPosition.first = (position.first * width) / this->_mapSize.first;
    windowPosition.second = (position.second * height) / this->_mapSize.second;

    return windowPosition;
}

void arcadeSDL::_resizeTexture(SDL_Rect &rect, std::pair<int, int> position)
{
    int width, height;

    SDL_GetWindowSize(this->window, &width, &height);
    rect.w = width / this->_mapSize.first + 0.1;
    rect.h = height / this->_mapSize.second + 0.1;
}

void arcadeSDL::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    SDL_Surface *surface = IMG_Load(asset.c_str());
    if (!surface) {
        this->drawRectangle(color, position);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface); // Free the surface right after creating the texture

    if (!texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return;
    }

    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
    SDL_Rect destRect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(destRect, position);

    SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture); // Always destroy the texture after use
    (void)text;
}

void arcadeSDL::drawRectangle(int color, std::pair<size_t, size_t> position) {
    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
    SDL_Rect rect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(rect, position);
    
    // Set color based on parameter
    switch (color) {
        case 0: SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); break;      // Black
        case 1: SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); break; // White
        case 2: SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255); break;    // Red
        case 3: SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255); break;    // Green
        case 4: SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255); break;    // Blue
        default: SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); break;     // Default Black
    }
    
    // Draw the filled rectangle
    SDL_RenderFillRect(this->renderer, &rect);
}

void arcadeSDL::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
    //TODO: À implémenter
}

void arcadeSDL::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color, color_t outline,  int thickness) {
    //TODO: À implémenter
}

void arcadeSDL::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
    //TODO: À implémenter
}

void arcadeSDL::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color) {
    //TODO: À implémenter
}

std::pair<int, int> arcadeSDL::getWindowSize() {
    //TODO: À implémenter
	return {0, 0};
}

bool arcadeSDL::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
    //TODO: À implémenter
    return false;
}

void arcadeSDL::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
    (void)text;
    (void)color;
    (void)position;
}

void arcadeSDL::setMapSize(std::pair<size_t, size_t> size) {
    this->_mapSize = size;
}

void arcadeSDL::resizeWindow(size_t x, size_t y) {
}

arcadeSDL::arcadeSDL()
{
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    this->arcadeSDL::_initWindow();
    this->_mapSize = {0, 0};
}

arcadeSDL::~arcadeSDL() {
    if (this->isOpen()) {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        IMG_Quit();
        SDL_Quit();
    }
}
