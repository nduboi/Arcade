/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDL
*/

#include <iostream>
#include "arcadeSDL.hpp"
#include <SDL2/SDL_image.h>

void arcadeSDL::display() {
    if (this->sdl)
        this->sdl->display();
}

void arcadeSDL::closeWindow() {
    this->sdl.reset(nullptr);
}

bool arcadeSDL::isOpen() {
    if (this->sdl)
        return this->sdl->isOpen();
    return false;
}

void arcadeSDL::clear() {
    if (this->sdl)
        this->sdl->clear();
}

std::pair<int, int> arcadeSDL::_getWindowPosition(std::pair<int, int> position)
{
    std::pair<int, int> windowPosition;
    auto windowSize = this->sdl->getWindowSize();

    windowPosition.first = (position.first * windowSize.first) / this->_mapSize.first;
    windowPosition.second = (position.second * windowSize.second) / this->_mapSize.second;

    return windowPosition;
}

void arcadeSDL::_resizeTexture(SDL_Rect &rect, std::pair<int, int> position)
{
    auto windowSize = this->sdl->getWindowSize();

    rect.w = windowSize.first / this->_mapSize.first + 0.1;
    rect.h = windowSize.second / this->_mapSize.second + 0.1;
}

void arcadeSDL::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    SDL_Surface *surface = IMG_Load(asset.c_str());
    if (!surface) {
        this->drawRectangle(color, position);
        return;
    }

    SDL_Texture *texture = this->sdl->createTextureFromSurface(surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return;
    }

    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
    SDL_Rect destRect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(destRect, position);
    this->sdl->renderImage(texture, &destRect);
    SDL_DestroyTexture(texture);
    (void)text;
}

void arcadeSDL::drawRectangle(int color, std::pair<size_t, size_t> position) {
    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
	SDL_Rect rect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(rect, position);
    this->sdl->setColor(color);
    this->sdl->drawRectangle(rect);
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
    if (this->sdl)
        this->sdl->resizeWindow(x, y);
}

arcadeSDL::arcadeSDL()
{
    this->sdl = std::make_unique<Display::SDLEncapsulation>();
    this->_mapSize = {0, 0};
}

arcadeSDL::~arcadeSDL() = default;
