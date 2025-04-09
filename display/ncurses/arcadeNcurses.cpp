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
		if (this->_mapSize == std::pair<size_t, size_t>{9, 9} || this->_mapSize == std::pair<size_t, size_t>{16, 16} || this->_mapSize == std::pair<size_t, size_t>{30, 30} || this->_mapSize == std::pair<size_t, size_t>{30, 16})
			this->_ncurses.drawRectangle({static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, this->_mapSize, color);
		else
			this->_ncurses.drawRectangle({static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, this->_mapSize, color);
	}

	void arcadeNcurses::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position,
	color_t color)
	{
		(void) size;
		(void) position;
		(void) color;
		this->_ncurses.drawThickRectangle({position.first * COLS / 1620, position.second * LINES / 900}, {size.first * COLS / 1620,  size.second * LINES / 900}, 1, 0);
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
		(void) charSize;
		if (text == "Arcade Games" || text == "Arcade" || text == "Arcade Menu" || text == "Menu") {
			this->_ncurses.changeTitle(text);
		} else
			this->_ncurses.drawGame(text, {position.first * COLS / 1600, position.second * LINES / 900});
	}

	std::pair<int, int> arcadeNcurses::getWindowSize() {
        return {COLS * 7 , LINES * 14.5};
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
		if (!text.empty() && (text.size() == 1 && (text != "a" && text != "b" && text != "h" && text != "#")) )
			this->_ncurses.drawCharacter(text[0], {static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, this->_mapSize, color);
		else
        	this->_ncurses.drawRectangle({static_cast<int>(position.first * 2), static_cast<int>(position.second)}, {2, 1}, this->_mapSize, color);
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
