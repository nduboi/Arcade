//
// Created by roussierenoa on 3/26/25.
//

#include "NcursesEncapsulation.hpp"

#include <iostream>

namespace Game {
	bool NcursesEncapsulation::isOpen() const {
		return this->_isOpen;
	}

	void NcursesEncapsulation::close() {
		this->_isOpen = false;
	}

	void NcursesEncapsulation::clear() const {
		if (this->_header)
			werase(this->_header);
		if (this->_game)
			werase(this->_game);
		if (this->_window)
			erase();
	}

	void NcursesEncapsulation::display() const {
		this->_drawHeader();
		if (this->_header)
			wrefresh(this->_header);
		if (this->_game)
			wrefresh(this->_header);
		if (this->_window)
			refresh();
	}

	void NcursesEncapsulation::_drawHeader() const
	{
		mvwprintw(this->_header, 1, static_cast<int>(COLS - this->_appTitle.size()) / 2, "%s", this->_appTitle.c_str());
	}

	void NcursesEncapsulation::drawGame(const std::string &text, const std::pair<int, int> &pos) const
	{
		mvwprintw(this->_game, pos.first, pos.second, "%s", text.c_str());
	}

	void NcursesEncapsulation::changeTitle(const std::string &title)
	{
		this->_appTitle = title;
	}

	NcursesEncapsulation::NcursesEncapsulation()
	{
		this->_appTitle =  "Arcade Ncurses";
		this->_isOpen = false;
		this->_window = initscr();
		if (this->_window == nullptr || this->_window != stdscr) {
			throw NcursesException("Failed to initscr()");
		}
		//TODO : A modifier sur le header
		this->_header = subwin(this->_window, 3, 80, 0, 0);
		if (this->_header == nullptr)
			throw NcursesException("Failed to subWin the header()");
		//TODO : A modifier sur le game
		this->_game = subwin(this->_window, 20, 80, 4, 0);
		if (this->_game == nullptr)
			throw NcursesException("Failed to subWin the header()");
		this->_isOpen = true;
	}

	NcursesEncapsulation::~NcursesEncapsulation() {
		delwin(this->_header);
		delwin(this->_game);
		endwin();
		this->_header = nullptr;
		this->_game = nullptr;
		this->_window = nullptr;
	}
} // game