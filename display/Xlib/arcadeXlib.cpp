#include "arcadeXlib.hpp"
#include <iostream>

arcadeXlib::arcadeXlib() {
    this->xlib = std::make_unique<DisplayLib::XlibEncapsulation>();
    this->_mapSize = {0, 0};
}

arcadeXlib::~arcadeXlib() = default;

void arcadeXlib::display() {
    this->xlib->display();
}

void arcadeXlib::closeWindow() {
    this->xlib.reset();
}

bool arcadeXlib::isOpen() {
    return this->xlib && this->xlib->isOpen();
}

void arcadeXlib::clear() {
    this->xlib->clear();
}

void arcadeXlib::drawRectangle(int color, std::pair<size_t, size_t> position) {
    auto [width, height] = this->xlib->getWindowSize();
    int rectWidth = width / this->_mapSize.first;
    int rectHeight = height / this->_mapSize.second;
    this->xlib->drawRectangle(position.first * rectWidth, position.second * rectHeight, rectWidth, rectHeight, {255, 0, 0});
}

void arcadeXlib::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
    auto [width, height] = this->xlib->getWindowSize();
    int x = position.first * (width / this->_mapSize.first);
    int y = position.second * (height / this->_mapSize.second);
    this->xlib->drawText(text, x, y, {255, 255, 255});
}

void arcadeXlib::setMapSize(std::pair<size_t, size_t> size) {
    this->_mapSize = size;
}

void arcadeXlib::resizeWindow(size_t x, size_t y) {
    this->xlib->resizeWindow(x, y);
}

std::pair<int, int> arcadeXlib::getWindowSize() {
    return xlib->getWindowSize();
}

void arcadeXlib::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    // Since Xlib doesn't easily support image loading, we'll draw a colored rectangle instead
    this->drawRectangle(color, position);
    // If there's text, we can display it
    if (!text.empty()) {
        auto [width, height] = this->xlib->getWindowSize();
        int x = position.first * (width / this->_mapSize.first);
        int y = position.second * (height / this->_mapSize.second) + 15; // Offset a bit to be visible within rectangle
        this->xlib->drawText(text, x, y, {255, 255, 255});
    }
}

void arcadeXlib::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) {
    DisplayLib::Color xlibColor = {static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), 255};
    this->xlib->drawRectangle(position.first, position.second, size.first, size.second, xlibColor);
}

void arcadeXlib::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
    // Since Xlib doesn't easily support image loading, we'll draw a colored rectangle instead
    DisplayLib::Color color = {255, 255, 255, 255}; // Default white color
    this->xlib->drawRectangle(position.first, position.second, size.first, size.second, color);
}

void arcadeXlib::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
    // Draw outer rectangle
    DisplayLib::Color white = {255, 255, 255, 255};
    this->xlib->drawRectangle(position.first, position.second, size.first, size.second, white);
    
    // Draw inner rectangle
    DisplayLib::Color black = {0, 0, 0, 255};
    this->xlib->drawRectangle(
        position.first + thickness, 
        position.second + thickness, 
        size.first - 2 * thickness, 
        size.second - 2 * thickness, 
        black
    );
}

void arcadeXlib::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) {
    DisplayLib::Color xlibColor = {static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), 255};
    this->xlib->drawText(text, position.first, position.second, xlibColor);
}

bool arcadeXlib::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
    // Implementation would require tracking mouse position
    // This is a basic implementation that always returns false
    return false;
}
