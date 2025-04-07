/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeSDL
*/

#include <iostream>
#include "arcadeSDL.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
    const int hudOffset = 100;

    windowPosition.first = (position.first * windowSize.first) / this->_mapSize.first;
    windowPosition.second = hudOffset + (position.second * (windowSize.second - hudOffset)) / this->_mapSize.second;
    return windowPosition;
}

void arcadeSDL::_resizeTexture(SDL_Rect &rect, std::pair<int, int> position)
{
    auto windowSize = this->sdl->getWindowSize();
    windowSize.second -= 100;

    rect.w = windowSize.first / this->_mapSize.first + 0.1;
    rect.h = windowSize.second / this->_mapSize.second + 0.1;
}

void arcadeSDL::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position)
{
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

void arcadeSDL::drawRectangle(int color, std::pair<size_t, size_t> position)
{
    std::pair<int, int> windowPosition = this->_getWindowPosition(position);
	SDL_Rect rect = {windowPosition.first, windowPosition.second, 0, 0};
    this->_resizeTexture(rect, position);
    this->sdl->setColor(color);
    this->sdl->drawRectangle(rect);
}

void arcadeSDL::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position)
{
    this->sdl->drawSpriteMenu(size, asset, position);
}

void arcadeSDL::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color)
{
    this->sdl->drawRectangleMenu(size, position, {static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), 255});
}

void arcadeSDL::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness)
{
    this->sdl->drawThickRectangle(position, size, thickness);
}

void arcadeSDL::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize)
{
    this->sdl->drawTextMenu(text, position, {static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), 255}, charSize);
}

std::pair<int, int> arcadeSDL::getWindowSize()
{
    return this->sdl->getWindowSize();
}

bool arcadeSDL::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    return (mouseX >= position.first &&
            mouseX <= position.first + size.first &&
            mouseY >= position.second &&
            mouseY <= position.second + size.second);
}

void arcadeSDL::drawText(std::string text, int color, std::pair<size_t, size_t> position)
{
    this->sdl->drawText(text, color, position);
}

void arcadeSDL::setMapSize(std::pair<size_t, size_t> size)
{
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

arcadeSDL::~arcadeSDL() {
    try {
        if (this->sdl) {
#ifdef _DEBUG
            std::cout << "Destroying SDL resources..." << std::endl;
#endif
            this->sdl.reset();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error during SDL destruction: " << e.what() << std::endl;
    }
}
