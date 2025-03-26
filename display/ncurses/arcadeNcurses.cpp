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
		//TODO: Dessiner un rectangle
		// this->_ncurses.drawGame();
	}

	void arcadeNcurses::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
		this->_ncurses.drawGame(text, {position.first, position.second});
	}

	void arcadeNcurses::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
	}

	void arcadeNcurses::setMapSize(std::pair<size_t, size_t> size) {
		//TODO Implémenter l'appel vers la NCURSES, pour le moment la game == x = COLS et y = LINES
	}

	void arcadeNcurses::resizeWindow(size_t x, size_t y) {
		//TODO Implémenter l'appel vers la NCURSES, pour le moment la game == x = COLS et y = LINES
	}
}