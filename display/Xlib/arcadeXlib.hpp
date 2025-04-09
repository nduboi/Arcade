#ifndef ARCADEXLIB_HPP
#define ARCADEXLIB_HPP

#include <string>
#include <memory>
#include "IWindow.hpp"
#include "XlibEncapsulation.hpp"

class arcadeXlib : public IWindow {
private:
    std::string _libName = "Arcade Xlib";
    std::pair<size_t, size_t> _mapSize;

public:
    std::unique_ptr<DisplayLib::XlibEncapsulation> xlib;
    
    arcadeXlib();
    ~arcadeXlib();

    void display() override;
    void closeWindow() override;
    bool isOpen() override;
    void clear() override;
    
    void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;
    void drawRectangle(int color, std::pair<size_t, size_t> position) override;
    void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;
    
    void drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) override;
    void drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) override;
    void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) override;
    void drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) override;
    
    bool isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) override;
    
    void setMapSize(std::pair<size_t, size_t> size) override;
    void resizeWindow(size_t x, size_t y) override;
    std::pair<int, int> getWindowSize() override;
};

#endif // ARCADEXLIB_HPP
