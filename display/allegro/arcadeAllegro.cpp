#include "arcadeAllegro.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <iostream>

arcadeAllegro::arcadeAllegro() {
    this->allegro = std::make_unique<Display::AllegroEncapsulation>();
    this->_mapSize = {0, 0};
}

arcadeAllegro::~arcadeAllegro() {
    this->allegro.reset();
}

void arcadeAllegro::display() {
    if (this->allegro)
        this->allegro->display();
}

void arcadeAllegro::closeWindow() {
    this->allegro.reset();
}

bool arcadeAllegro::isOpen() {
    return this->allegro && this->allegro->isOpen();
}

void arcadeAllegro::clear() {
    if (this->allegro)
        this->allegro->clear();
}

std::pair<int, int> arcadeAllegro::_resizeTexture(std::pair<int, int> position)
{
    std::pair<int, int> windowSize = this->allegro->getWindowSize();
    windowSize.second -= 100;

    int w = static_cast<int>(windowSize.first / static_cast<float>(this->_mapSize.first) + 0.1f);
    int h = static_cast<int>(windowSize.second / static_cast<float>(this->_mapSize.second) + 0.1f);

    return {w, h};
}

std::pair<int, int> arcadeAllegro::_getWindowPosition(std::pair<int, int> position)
{
    std::pair<int, int> windowPosition;
    auto windowSize = this->allegro->getWindowSize();
    const int hudOffset = 100;

    windowPosition.first = (position.first * windowSize.first) / this->_mapSize.first;
    windowPosition.second = hudOffset + (position.second * (windowSize.second - hudOffset)) / this->_mapSize.second;

    return windowPosition;
}


void arcadeAllegro::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    ALLEGRO_BITMAP* image = al_load_bitmap(asset.c_str());
    if (!image) {
        this->drawRectangle(color, position);
        return;
    }

    std::pair<int, int> windowPosition = this->_getWindowPosition(position);

    int spriteWidth = al_get_bitmap_width(image);
    int spriteHeight = al_get_bitmap_height(image);

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);

    std::pair<int, int> scaledSize = this->_resizeTexture(position);
    float scaleX = static_cast<float>(scaledSize.first) / spriteWidth;
    float scaleY = static_cast<float>(scaledSize.second) / spriteHeight;

    al_scale_transform(&transform, scaleX, scaleY);
    al_translate_transform(&transform, windowPosition.first, windowPosition.second);
    al_use_transform(&transform);
    al_draw_bitmap(image, 0, 0, 0);
    al_identity_transform(&transform);
    al_use_transform(&transform);

    al_destroy_bitmap(image);
    (void)text;
}

void arcadeAllegro::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position,
    color_t color) {
    this->allegro->drawRectangleMenu(size, position, {static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), 255});
}

void arcadeAllegro::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
    ALLEGRO_BITMAP* image = al_load_bitmap(asset.c_str());
    if (!image) {
        std::cerr << "Failed to load image: " << asset << std::endl;
        return;
    }

    al_draw_scaled_bitmap(image, position.first, position.second, al_get_bitmap_width(image), al_get_bitmap_height(image),
        position.first, position.second, size.first, size.second, 0);
    al_destroy_bitmap(image);
}

void arcadeAllegro::drawRectangle(int color, std::pair<size_t, size_t> position) {
    Display::Color allegroColor = {255, 255, 255, 255}; // Default to white
    switch (color) {
        case 0: allegroColor = {0, 0, 0, 255}; break;    // Black
        case 1: allegroColor = {255, 255, 255, 255}; break; // White
        case 2: allegroColor = {255, 0, 0, 255}; break;  // Red
        case 3: allegroColor = {0, 255, 0, 255}; break;  // Green
        case 4: allegroColor = {0, 0, 255, 255}; break;  // Blue
    }
    this->allegro->setColor(allegroColor);
    this->allegro->drawRectangle(position.first, position.second, 50, 50); // Example size
}

void arcadeAllegro::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
    Display::Color allegroColor = {255, 255, 255, 255}; // Default to white
    switch (color) {
        case 0: allegroColor = {0, 0, 0, 255}; break;    // Black
        case 1: allegroColor = {255, 255, 255, 255}; break; // White
        case 2: allegroColor = {255, 0, 0, 255}; break;  // Red
        case 3: allegroColor = {0, 255, 0, 255}; break;  // Green
        case 4: allegroColor = {0, 0, 255, 255}; break;  // Blue
    }
    this->allegro->drawText(text, position.first, position.second, allegroColor, 20);
}

void arcadeAllegro::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) {
    Display::Color allegroColor = {color.r, color.g, color.b, 255};
    this->allegro->drawText(text, position.first, position.second, allegroColor, charSize);
}

void arcadeAllegro::setMapSize(std::pair<size_t, size_t> size) {
    this->_mapSize = size;
}

void arcadeAllegro::resizeWindow(size_t x, size_t y) {
    if (this->allegro)
        this->allegro->resizeWindow(x, y);
}

std::pair<int, int> arcadeAllegro::getWindowSize() {
    return this->allegro->getWindowSize();
}

bool arcadeAllegro::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    return (mouse_state.x >= static_cast<int>(position.first) &&
            mouse_state.x <= static_cast<int>(position.first + size.first) &&
            mouse_state.y >= static_cast<int>(position.second) &&
            mouse_state.y <= static_cast<int>(position.second + size.second));
}
