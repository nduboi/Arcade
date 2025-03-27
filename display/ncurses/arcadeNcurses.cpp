//
// Created by roussierenoa on 3/26/25.
//

#include "arcadeNcurses.hpp"

namespace Game {
	void arcadeNcurses::display() {
		this->_ncurses.display();
	}

	void arcadeNcurses::closeWindow() {
		return this->_ncurses.close();
	}

	bool arcadeNcurses::isOpen() {
		return this->_ncurses.isOpen();
	}

	void arcadeNcurses::clear() {
		this->_ncurses.clear();
	}

	void arcadeNcurses::drawRectangle(int color, std::pair<size_t, size_t> position) {
        this->_ncurses.drawRectangle({static_cast<int>(position.first), static_cast<int>(position.second)}, {1, 1}, color);
	}

	void arcadeNcurses::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position,
		color_t color, color_t outline,  int thickness)
	{
	}

	void arcadeNcurses::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
	}

	void arcadeNcurses::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color) {
	}

	std::pair<int, int> arcadeNcurses::getWindowSize() {
        return {COLS, LINES - 4};
	}

	bool arcadeNcurses::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
        return false;
	}

	arcadeNcurses::arcadeNcurses() {
		this->_ncurses.changeTitle("Arcade");
	}

	void arcadeNcurses::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
        // Pass color directly without modifying it
		this->_ncurses.drawText(text, {static_cast<int>(position.first), static_cast<int>(position.second)}, color);
	}

	void arcadeNcurses::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
        // Since ncurses can't display sprites, represent them with colored rectangles using the same color code
        this->_ncurses.drawRectangle({static_cast<int>(position.first), static_cast<int>(position.second)}, {1, 1}, color);
	}

	void arcadeNcurses::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
	}

	void arcadeNcurses::setMapSize(std::pair<size_t, size_t> size) {
		this->_mapSize = size;
	}

	void arcadeNcurses::resizeWindow(size_t x, size_t y) {
	}
}
