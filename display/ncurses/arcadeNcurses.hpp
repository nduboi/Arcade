/**
 * @file arcadeNcurses.hpp
 * @brief Header file for the arcadeNcurses class.
 *
 * This file contains the declaration of the arcadeNcurses class, which implements the IDisplayModule interface.
 * 
 * @author eliotttesnier
 * @date 3/17/25
 */

#ifndef arcadeNcurses_HPP
#define arcadeNcurses_HPP

#include "IWindow.hpp"
#include "IEvent.hpp"
#include <string>
#include <ncurses.h>

/**
 * @class arcadeNcurses
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeNcurses class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeNcurses : public IWindow {
	std::string _libName = "Arcade Ncurses"; ///< The name of the library.
	std::pair<int, int> _mapSize; ///< The size of the map.
	bool _isOpen = false;
private:
public:
	WINDOW* _window = nullptr;
	WINDOW* _renderer = nullptr;

	void initWindow() override;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	void drawSprite(std::string asset, int color, std::pair<int, int> position) override;

	void drawRectangle(int color, std::pair<int, int> position) override;

	void drawText(std::string text, int color, std::pair<int, int> position) override;

	void setMapSize(std::pair<int, int> size) override;

	arcadeNcurses();

	~arcadeNcurses() override;
};

#endif // arcadeNcurses_HPP
