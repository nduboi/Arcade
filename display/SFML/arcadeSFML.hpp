/**
 * @file arcadeSFML.hpp
 * @brief Header file for the arcadeSFML class.
 *
 * This file contains the declaration of the arcadeSFML class, which implements the IDisplayModule interface.
 * 
 * @author roussierenoa
 * @date 3/17/25
 */

#ifndef arcadeSFML_HPP
#define arcadeSFML_HPP

#include "IWindow.hpp"
#include "IEvent.hpp"
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @class arcadeSFML
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeSFML class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeSFML : public IWindow {
	std::string _libName = "Arcade SFML"; ///< The name of the library.
	std::pair<size_t, size_t> _mapSize; ///< The size of the map.
private:
	std::pair<int, int> _getWindowPosition(std::pair<int, int> position);
	void _resizeSprite(sf::Sprite &sprite, std::pair<int, int> position);
public:
	sf::RenderWindow window;

	void initWindow() override;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;

	void drawRectangle(int color, std::pair<size_t, size_t> position) override;

	void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

	void setMapSize(std::pair<size_t, size_t> size) override;

	arcadeSFML();

	~arcadeSFML() = default;
};

#endif // arcadeSFML_HPP
