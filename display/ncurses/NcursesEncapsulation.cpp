//
// Created by roussierenoa on 3/26/25.
//

#include "NcursesEncapsulation.hpp"

#include <iostream>
#include <ncurses.h>
#include <ncurses.h>
#include <unistd.h>

namespace Display {
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
			werase(this->_window);
	}

	void NcursesEncapsulation::display() const {
		this->_drawHeader();
		if (this->_header && is_wintouched(this->_header))
			wnoutrefresh(this->_header);
		if (this->_game && is_wintouched(this->_game))
			wnoutrefresh(this->_game);
		doupdate();
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
		for (int y = 0; y < size.first; y++) {
			for (int x = 0; x < size.second; x++) {
				mvwaddch(this->_game, pos.second + x, pos.first + y, ' ' | A_REVERSE);
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
	}

	void NcursesEncapsulation::drawText(const std::string &text, const std::pair<int, int> &pos, int color) const
	{
		(void)text;
		(void)pos;
		(void)color;
	}

	void NcursesEncapsulation::changeTitle(const std::string &title)
	{
		this->_appTitle = title;
	}

	NcursesEncapsulation::NcursesEncapsulation() {
		this->_isOpen = false;

		this->term_out = fopen("/dev/tty", "w");
		this->term_in = fopen("/dev/tty", "r");
		if (!this->term_out || !this->term_in) {
			throw NcursesException("Failed to open /dev/tty");
		}
		this->screen = newterm(nullptr, this->term_out, this->term_in);
		if (!this->screen) {
			throw NcursesException("Failed to create new Ncurses screen");
		}
		set_term(this->screen);
		this->_window = newwin(LINES, COLS, 0, 0);
		if (!this->_window) {
			throw NcursesException("Failed to create main window");
		}
		start_color();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(0);
		nodelay(stdscr, TRUE);
		timeout(0);
		int row, col;
		(void) row;
		getmaxyx(this->_window, row, col);
		this->_header = subwin(this->_window, 3, col, 0, 0);
		if (!this->_header)
			throw NcursesException("Failed to create header window");
		this->_game = subwin(this->_window, 20, col, 4, 0);
		if (!this->_game)
			throw NcursesException("Failed to create game window");
		box(this->_header, 0, 0);
		box(this->_game, 0, 0);
		touchwin(this->_header);
		touchwin(this->_game);
		wnoutrefresh(this->_header);
		wnoutrefresh(this->_game);
		doupdate();
		this->_isOpen = true;
	}

	NcursesEncapsulation::~NcursesEncapsulation() {
		if (this->_header) {
			delwin(this->_header);
			this->_header = nullptr;
		}
		if (this->_game) {
			delwin(this->_game);
			this->_game = nullptr;
		}
		if (this->_window) {
			delwin(this->_window);
			this->_window = nullptr;
		}

		if (this->screen) {
			endwin();
			delscreen(this->screen);
			this->screen = nullptr;
		}

		if (this->term_out) {
			fclose(this->term_out);
			this->term_out = nullptr;
		}
		if (this->term_in) {
			fclose(this->term_in);
			this->term_in = nullptr;
		}
	}
} // game