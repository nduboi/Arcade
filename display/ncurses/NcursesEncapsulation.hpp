//
// Created by roussierenoa on 3/26/25.
//

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include "ncurses.h"
#include "Exception.hpp"

namespace Display {

	class NcursesEncapsulation {
	private:
		SCREEN *screen = nullptr;
		WINDOW *_window = nullptr;
		WINDOW *_header = nullptr;
		WINDOW *_game = nullptr;
		bool _isOpen;
		FILE *term_out;
		FILE *term_in;
		std::string _appTitle;

		void _drawHeader() const;

	public:
		bool isOpen() const;
		void close();
		void clear();
		void display() const;
		void drawGame(const std::string &text, const std::pair<int, int> &pos) const;
		void drawRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size, int color = 0) const;
		void drawCharacter(char character, const std::pair<int, int> &pos, const std::pair<int, int> &size, int color = 0) const;
		void drawThickRectangle(const std::pair<int, int> &pos, const std::pair<int, int> &size, int thickness, int color = 0) const;
		void drawText(const std::string &text, const std::pair<int, int> &pos, int color = 0) const;
		void changeTitle(const std::string &title);
		void appendToTitle(const std::string &title);

		NcursesEncapsulation();
		~NcursesEncapsulation();
	};

} // game

#endif //NCURSES_HPP
