/**
 * @file arcadeQT.hpp
 * @brief Header file for the arcadeQT class.
 *
 * This file contains the declaration of the arcadeQT class, which implements the IDisplayModule interface.
 * 
 * @author roussierenoa
 * @date 3/17/25
 */

#ifndef arcadeQT_HPP
#define arcadeQT_HPP

#include "IWindow.hpp"
#include "IEvent.hpp"
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @class arcadeQT
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeQT class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeQT : public IWindow {
	std::string _libName = "Arcade QT5"; ///< The name of the library.
	std::pair<size_t, size_t> _mapSize; ///< The size of the map.
private:
	std::pair<int, int> _getWindowPosition(std::pair<int, int> position);
	void _resizeData(sf::Sprite &sprite, std::pair<int, int> position);
	void _resizeData(sf::RectangleShape &sprite, std::pair<int, int> position);

public:
	sf::RenderWindow window;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	void drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) override;

	void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;

	void drawRectangle(int color, std::pair<size_t, size_t> position) override;

	void drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) override;

	void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) override;

	void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

	void drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) override;

	void setMapSize(std::pair<size_t, size_t> size) override;

	void resizeWindow(size_t x, size_t y) override;

	std::pair<int, int> getWindowSize() override;

	bool isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) override;

	arcadeQT();

	~arcadeQT() = default;
};

#endif // arcadeQT_HPP
