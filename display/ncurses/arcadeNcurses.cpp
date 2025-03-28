//
// Created by roussierenoa on 3/26/25.
//

#include "arcadeNcurses.hpp"

namespace Display {
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
        this->_ncurses.drawRectangle({static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, color);
	}

	void arcadeNcurses::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position,
	color_t color)
	{
		(void) size;
		(void) position;
		(void) color;
	}

	void arcadeNcurses::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
		(void) position;
		(void) size;
		(void) thickness;
	}

	void arcadeNcurses::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) {
		(void) text;
		(void) position;
		(void) color;
		(void)charSize;
	}

	std::pair<int, int> arcadeNcurses::getWindowSize() {
        return {COLS / 2, LINES - 4};
	}

	bool arcadeNcurses::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
		(void) position;
		(void) size;
        return false;
	}

	arcadeNcurses::arcadeNcurses() {
		this->_ncurses.changeTitle("");
	}

	void arcadeNcurses::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
		(void) color;
		(void) position;
		this->_ncurses.appendToTitle(text);
	}

	void arcadeNcurses::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
		(void) asset;
		(void) text;
        this->_ncurses.drawRectangle({static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, color);
	}

	void arcadeNcurses::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
		(void) size;
		(void) asset;
		(void) position;
	}

	void arcadeNcurses::setMapSize(std::pair<size_t, size_t> size) {
		this->_mapSize = size;
	}

	void arcadeNcurses::resizeWindow(size_t x, size_t y) {
		(void) x;
		(void) y;
	}
}
