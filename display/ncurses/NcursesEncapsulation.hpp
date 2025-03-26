//
// Created by roussierenoa on 3/26/25.
//

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include "ncurses.h"
#include "Exception.hpp"

namespace Game {

	class NcursesEncapsulation {
	private:
		WINDOW *_window = nullptr;
		WINDOW *_header = nullptr;
		WINDOW *_game = nullptr;
		bool _isOpen;
		std::string _appTitle;

		void _drawHeader() const;

	public:
		bool isOpen() const;
		void close();
		void clear() const;
		void display() const;
		void drawGame(const std::string &text, const std::pair<int, int> &pos) const;
		void changeTitle(const std::string &title);

		NcursesEncapsulation();
		~NcursesEncapsulation();
	};

} // game

#endif //NCURSES_HPP
