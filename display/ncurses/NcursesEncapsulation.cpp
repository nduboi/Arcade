//
// Created by roussierenoa on 3/26/25.
//

#include "NcursesEncapsulation.hpp"

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

namespace DisplayLib {
	bool NcursesEncapsulation::isOpen() const {
		return this->_isOpen;
	}

	void NcursesEncapsulation::close() {
		this->_isOpen = false;
		reset_shell_mode();
		reset_prog_mode();
	}

	void NcursesEncapsulation::clear() {
		if (this->_header)
			werase(this->_header);
		if (this->_game)
			werase(this->_game);
		erase();
		this->changeTitle("");
		int rows, cols;
		getmaxyx(stdscr, rows, cols);
		wresize(this->_header, 3, cols);
		wresize(this->_game, rows - 4, cols);
		wmove(this->_header, 0, 0);
		wmove(this->_game, 3, 0);
		box(this->_header, 0, 0);
		box(this->_game, 0, 0);
	}

	void NcursesEncapsulation::display() const {
		this->_drawHeader();
		if (this->_header && is_wintouched(this->_header))
			wrefresh(this->_header);
		if (this->_game && is_wintouched(this->_game))
			wrefresh(this->_game);
		refresh();
	}

	void NcursesEncapsulation::_drawHeader() const
	{
		int row, col;
		(void)row;
		getmaxyx(stdscr, row, col);
		int xPos = std::max(0, (col - static_cast<int>(this->_appTitle.size())) / 2);
		mvwprintw(this->_header, 1, xPos, "%s", this->_appTitle.c_str());
		box(this->_header, 0, 0);
	}

	void NcursesEncapsulation::drawGame(const std::string &text, const std::pair<int, int> &pos) const
	{
		mvwprintw(this->_game, pos.second, pos.first, "%s", text.c_str());
	}

	void NcursesEncapsulation::drawRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size,  const std::pair<int, int> &mapSize, int color) const
	{
		short ncursesColor;
		if (color == 0)
			return;

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
		std::pair<int, int> currentPos = {pos};
		if ((mapSize.first == 9 && mapSize.second == 9) || (mapSize.first == 16 && mapSize.second == 16) || (mapSize.first == 30 && mapSize.second == 30) || (mapSize.first == 30 && mapSize.second == 16)) {
			int startY = getmaxy(this->_game) / 2 - (mapSize.second / 2);
			int startX = getmaxx(this->_game) / 2 - mapSize.first;
			for (int y = 0; y < size.second * 1; y++) {
				for (int x = 0; x < size.first * 1; x++) {
					mvwaddch(this->_game, currentPos.second * 1 + startY + y, currentPos.first * 1 + startX  + x, ' ' | A_REVERSE);
				}
			}
		} else {
			int startY = getmaxy(this->_game) / 2 - mapSize.second;
			int startX = getmaxx(this->_game) / 2 - mapSize.first * 2;
			for (int y = 0; y < size.second * 2; y++) {
				for (int x = 0; x < size.first * 2; x++) {
					mvwaddch(this->_game, currentPos.second * 2 + startY + y, currentPos.first * 2 + startX  + x, ' ' | A_REVERSE);
				}
			}
		}

		if (color > 0) {
			wattroff(this->_game, COLOR_PAIR(color));
		}
	}

	void NcursesEncapsulation::drawThickRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size, int thickness, int color) const
	{
		(void)size;
		(void)pos;
		(void)color;
		(void)thickness;
		for (int y = 0; y < size.second; y++) {
			mvwprintw(this->_game, pos.second + y, pos.first, "|");
			mvwprintw(this->_game, pos.second + y, pos.first + size.first, "|");
			if (y != 0 && y != size.second - 1)
				continue;
			for (int x = 1; x < size.first - 1; x++) {
				mvwprintw(this->_game, pos.second + y, pos.first + x, "-");
			}
		}
	}

	void NcursesEncapsulation::drawText(const std::string &text, const std::pair<int, int> &pos, int color) const
	{
		(void)text;
		(void)pos;
		(void)color;
	}

	void NcursesEncapsulation::drawCharacter(char character, const std::pair<int, int> &pos, const std::pair<int, int> &size, const std::pair<int, int> &mapSize, int color) const
	{
		short ncursesColor;
		if (color == 0)
			return;

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
		std::pair<int, int> currentPos = {pos};
		int startY = (getmaxy(this->_game) - mapSize.second) / 2;
		int startX = (getmaxx(this->_game) - mapSize.first * 2) / 2;
		currentPos.second += startY;
		currentPos.first += startX;
		for (int y = 0; y < size.first; y++) {
			for (int x = 0; x < size.second; x++) {
				mvwaddch(this->_game, currentPos.second + x, currentPos.first + y, character | A_REVERSE);
			}
		}
		if (color > 0) {
			wattroff(this->_game, COLOR_PAIR(color));
		}
	}

	void NcursesEncapsulation::changeTitle(const std::string &title)
	{
		this->_appTitle = title;
	}

	void NcursesEncapsulation::appendToTitle(const std::string &title)
	{
		this->_appTitle += " " + title;
	}

	NcursesEncapsulation::NcursesEncapsulation() {
		this->_isOpen = false;
		this->_header = nullptr;
		this->_game = nullptr;
		this->_window = nullptr;

		this->_window = initscr();
		start_color();
		if (this->_window == nullptr)
			throw NcursesException("Error initializing ncurses");
		int rows, cols;
		getmaxyx(stdscr, rows, cols);
		this->_header = subwin(stdscr, 3, cols, 0, 0);
		if (!this->_header) {
			endwin();
			throw NcursesException("Error initializing Header ncurses");
		}
		this->_game = subwin(stdscr, rows - 4, cols, 3, 0);
		if (!this->_game) {
			delwin(this->_header);
			endwin();
			throw NcursesException("Error initializing Game ncurses");
		}
		noecho();
		cbreak();
		curs_set(0);
		nodelay(stdscr, TRUE);
		timeout(0);
		keypad(stdscr, TRUE);
		mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
		mouseinterval(0);
		this->_isOpen = true;
	}

	NcursesEncapsulation::~NcursesEncapsulation() {
		if (this->_game) {
			delwin(this->_game);
			this->_game = nullptr;
		}
		if (this->_header) {
			delwin(this->_header);
			this->_header = nullptr;
		}
		endwin();
		this->_isOpen = false;
	}
} // game