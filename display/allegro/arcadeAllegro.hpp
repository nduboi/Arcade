#ifndef ARCADEALLEGRO_HPP
#define ARCADEALLEGRO_HPP

#include <string>
#include <memory>
#include <allegro5/allegro.h>
#include "IWindow.hpp"
#include "AllegroEncapsulation.hpp"

/**
 * @class arcadeAllegro
 * @brief A class that implements the IWindow interface using Allegro.
 */
class arcadeAllegro : public IWindow {
private:
    std::pair<size_t, size_t> _mapSize;

public:
    std::unique_ptr<Display::AllegroEncapsulation> allegro;
    void display() override;
    void closeWindow() override;
    bool isOpen() override;
    void clear() override;

    std::pair<int, int> _resizeTexture(std::pair<int, int> position);

    std::pair<int, int> _getWindowPosition(std::pair<int, int> position);

    void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;
    void drawRectangle(int color, std::pair<size_t, size_t> position) override;
    void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;
    void setMapSize(std::pair<size_t, size_t> size) override;
    void resizeWindow(size_t x, size_t y) override;
    std::pair<int, int> getWindowSize() override;
    bool isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) override;
    void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) override {};
    void drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) override;
    void drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) override;
    void drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) override;

    arcadeAllegro();
    ~arcadeAllegro();
};

#endif // ARCADEALLEGRO_HPP
