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

void arcadeAllegro::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    ALLEGRO_BITMAP* image = al_load_bitmap(asset.c_str());
    if (!image) {
        std::cerr << "Failed to load image: " << asset << std::endl;
        return;
    }

    al_draw_bitmap(image, position.first, position.second, 0);
    al_destroy_bitmap(image);
}

void arcadeAllegro::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
    ALLEGRO_BITMAP* image = al_load_bitmap(asset.c_str());
    if (!image) {
        std::cerr << "Failed to load image: " << asset << std::endl;
        return;
    }

    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
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
