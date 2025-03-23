/**
 * @file arcadeNCURSES.hpp
 * @brief Header file for the arcadeNCURSES class.
 *
 * This file contains the declaration of the arcadeNCURSES class, which implements the IDisplayModule interface.
 * 
 * @author eliotttesnier
 * @date 3/17/25
 */

#ifndef arcadeNCURSES_HPP
#define arcadeNCURSES_HPP

#include <string>
#include <ncurses.h>
#include "IWindow.hpp"
#include "IEvent.hpp"

/**
 * @class arcadeNCURSES
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeNCURSES class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeNCURSES : public IWindow {
	std::string _libName = "Arcade NCURSES"; ///< The name of the library.
	std::pair<int, int> _mapSize = {0, 0}; ///< The size of the map.

private:
	bool _isOpen = false;

	void _initHeader();

public:
	WINDOW *mainWindow = nullptr;
	WINDOW *header = nullptr;
	WINDOW *game = nullptr;

	int poxXCloseButton = 0;
	int poxYCloseButton = 0;

	void initWindow() override;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	void drawSprite(std::string asset, int color, std::pair<int, int> position) override;

	void drawRectangle(int color, std::pair<int, int> position) override;

	void drawText(std::string text, int color, std::pair<int, int> position) override;

	void setMapSize(std::pair<int, int> size) override;

	arcadeNCURSES();

	~arcadeNCURSES() override;
};

#endif // arcadeNCURSES_HPP
