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

    // Copier la texture
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

void arcadeSDL::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position)
{
    SDL_Surface* surface = IMG_Load(asset.c_str());
    if (!surface) {
        SDL_Log("Impossible de charger l'image : %s", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!texture) {
        SDL_Log("Impossible de créer la texture : %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect;
    destRect.x = position.first;
    destRect.y = position.second;
    destRect.w = size.first;
    destRect.h = size.second;

    SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void arcadeSDL::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color)
{
    SDL_Color sdlColor = {static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), 255};

    SDL_SetRenderDrawColor(this->renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

    SDL_Rect rect;
    rect.x = position.first;
    rect.y = position.second;
    rect.w = size.first;
    rect.h = size.second;

    SDL_RenderFillRect(this->renderer, &rect);
}

void arcadeSDL::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness)
{
    SDL_Rect outerRect = {
        position.first,
        position.second,
        static_cast<int>(size.first),
        static_cast<int>(size.second)
    };
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(this->renderer, &outerRect);

    SDL_Rect innerRect = {
        position.first + thickness,
        position.second + thickness,
        static_cast<int>(size.first - 2 * thickness),
        static_cast<int>(size.second - 2 * thickness)
    };
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(this->renderer, &innerRect);
}

void arcadeSDL::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize)
{
    // Charger la police
    TTF_Font* font = TTF_OpenFont("assets/Arial.ttf", charSize);
    if (!font) {
        SDL_Log("Impossible de charger la police : %s", TTF_GetError());
        return;
    }

    SDL_Color sdlColor = {static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), 255};

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
    if (!surface) {
        SDL_Log("Impossible de créer la surface de texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!texture) {
        SDL_Log("Impossible de créer la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect destRect;
    destRect.x = position.first;
    destRect.y = position.second;
    destRect.w = surface->w;
    destRect.h = surface->h;

    SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

std::pair<int, int> arcadeSDL::getWindowSize()
{
    int width, height;
    SDL_GetWindowSize(this->window, &width, &height);
    return {width, height};
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
    // Charger la police
    TTF_Font* font = TTF_OpenFont("path/to/your/font.ttf", 20);
    if (!font) {
        SDL_Log("Impossible de charger la police : %s", TTF_GetError());
        return;
    }

    SDL_Color sdlColor = {255, 255, 255, 255};

    // Créer la surface de texte
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
    if (!surface) {
        SDL_Log("Impossible de créer la surface de texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Créer la texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!texture) {
        SDL_Log("Impossible de créer la texture de texte : %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    // Définir le rectangle de destination
    SDL_Rect destRect;
    destRect.x = position.first;
    destRect.y = position.second;
    destRect.w = surface->w;
    destRect.h = surface->h;

    // Copier la texture
    SDL_RenderCopy(this->renderer, texture, NULL, &destRect);

    // Libérer les ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
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

arcadeSDL::~arcadeSDL() = default;
