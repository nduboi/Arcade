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
			wrefresh(this->_game);
		if (this->_window)
			refresh();
	}

	void NcursesEncapsulation::_drawHeader() const
	{
		box(this->_header, 0, 0);
		mvwprintw(this->_header, 1, static_cast<int>(COLS - this->_appTitle.size()) / 2, "%s", this->_appTitle.c_str());
	}

	void NcursesEncapsulation::drawGame(const std::string &text, const std::pair<int, int> &pos) const
	{
		mvwprintw(this->_game, pos.first, pos.second, "%s", text.c_str());
	}

	void NcursesEncapsulation::drawRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size, int color) const
	{
		short ncursesColor;
		switch (color) {
			case 0: ncursesColor = COLOR_BLACK; break;
			case 1: ncursesColor = COLOR_WHITE; break;
			case 2: ncursesColor = COLOR_RED; break;
			case 3: ncursesColor = COLOR_GREEN; break;
			case 4: ncursesColor = COLOR_BLUE; break;
			default: ncursesColor = COLOR_BLACK; break;
		}

		if (color > 0) {
			init_pair(color, ncursesColor, COLOR_BLACK);
			wattron(this->_game, COLOR_PAIR(color));
		}
		for (int y = 0; y < size.second; y++) {
			for (int x = 0; x < size.first; x++) {
				mvwaddch(this->_game, pos.first + y, pos.second + x, ' ' | A_REVERSE);
			}
		}
		if (color > 0) {
			wattroff(this->_game, COLOR_PAIR(color));
		}
	}

	void NcursesEncapsulation::drawThickRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size, int thickness, int color) const
	{
		short ncursesColor;
		switch (color) {
			case 0: ncursesColor = COLOR_BLACK; break;
			case 1: ncursesColor = COLOR_WHITE; break;
			case 2: ncursesColor = COLOR_RED; break;
			case 3: ncursesColor = COLOR_GREEN; break;
			case 4: ncursesColor = COLOR_BLUE; break;
			default: ncursesColor = COLOR_BLACK; break;
		}

		if (color > 0) {
			init_pair(color, ncursesColor, COLOR_BLACK);
			wattron(this->_game, COLOR_PAIR(color));
		}
		for (int t = 0; t < thickness; t++) {
			for (int x = t; x < size.first - t; x++) {
				mvwaddch(this->_game, pos.first + t, pos.second + x, ' ' | A_REVERSE);
				mvwaddch(this->_game, pos.first + size.second - t - 1, pos.second + x, ' ' | A_REVERSE);
			}
			for (int y = t; y < size.second - t; y++) {
				mvwaddch(this->_game, pos.first + y, pos.second + t, ' ' | A_REVERSE);
				mvwaddch(this->_game, pos.first + y, pos.second + size.first - t - 1, ' ' | A_REVERSE);
			}
		}
		if (color > 0) {
			wattroff(this->_game, COLOR_PAIR(color));
		}
	}

	void NcursesEncapsulation::drawText(const std::string &text, const std::pair<int, int> &pos, int color) const
	{
		// Map color codes to match SFML: 0=Black, 1=White, 2=Red, 3=Green, 4=Blue
		short ncursesColor;
		switch (color) {
			case 0: ncursesColor = COLOR_BLACK; break;
			case 1: ncursesColor = COLOR_WHITE; break;
			case 2: ncursesColor = COLOR_RED; break;
			case 3: ncursesColor = COLOR_GREEN; break;
			case 4: ncursesColor = COLOR_BLUE; break;
			default: ncursesColor = COLOR_WHITE; break; // Default to white for visibility
		}
		
		if (color > 0) {
			init_pair(color, ncursesColor, COLOR_BLACK);
			wattron(this->_game, COLOR_PAIR(color));
		}
		mvwprintw(this->_game, pos.first, pos.second, "%s", text.c_str());
		if (color > 0) {
			wattroff(this->_game, COLOR_PAIR(color));
		}
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

		start_color();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(0);
		nodelay(stdscr, TRUE);
		timeout(0);

		this->_header = subwin(this->_window, 3, COLS, 0, 0);
		if (this->_header == nullptr)
			throw NcursesException("Failed to create header window");

		this->_game = subwin(this->_window, 20, COLS, 4, 0);
		if (this->_game == nullptr)
			throw NcursesException("Failed to create game window");

		box(this->_header, 0, 0);
		box(this->_game, 0, 0);
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