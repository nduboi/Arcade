//
// Created by roussierenoa on 3/26/25.
//

#include "arcadeNcursesEvent.hpp"
#include <iostream>


namespace Display {
	void arcadeNcursesEvent::init() {
	}

	IEvent::event_t arcadeNcursesEvent::pollEvents(std::pair<int, int> gridSize) {
		int ch = wgetch(stdscr);
		(void)gridSize;

		MEVENT event;
		if (ch == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				_mousePos = {event.x, event.y};

				if (event.bstate & BUTTON1_PRESSED)
					return IEvent::MOUSELEFTCLICK;
				if (event.bstate & BUTTON3_PRESSED)
					return IEvent::MOUSERIGHTCLICK;
			}
		}

		switch (ch) {
			case 'n':
				return IEvent::NEXTGRAPHIC;
			case 'g':
				return IEvent::NEXTGAME;
			case 'r':
				return IEvent::REFRESH;
			case ' ':
				return IEvent::SPACE;
			case 'q':
				return IEvent::CLOSE;
			case 'm':
				return IEvent::MENU;
			case 0x1B:
				return IEvent::ESCAPE;
			case KEY_UP:
				return IEvent::UP;
			case KEY_DOWN:
				return IEvent::DOWN;
			case KEY_LEFT:
				return IEvent::LEFT;
			case KEY_RIGHT:
				return IEvent::RIGHT;
			case BUTTON1_CLICKED:
				return IEvent::MOUSELEFTCLICK;
			case BUTTON2_CLICKED:
				return IEvent::MOUSERIGHTCLICK;
			case KEY_ENTER:
				return IEvent::ENTER;
			default:
				return IEvent::NOTHING;
		}
	}

	std::pair<int, int> arcadeNcursesEvent::getMousePos() {
		std::pair<int, int> tmp = this->_mousePos;

		tmp.second -= 4;
		tmp.first /= 2;
		return tmp;
	}

	void arcadeNcursesEvent::setMapSize(std::pair<int, int> size) {
		(void)size;
	}

	void arcadeNcursesEvent::cleanup() {
	}

	std::string arcadeNcursesEvent::getUsername() {
		return "";
	}

	void arcadeNcursesEvent::renderWrittiing() {
	}

	arcadeNcursesEvent::arcadeNcursesEvent(std::shared_ptr<IWindow> window) {
		(void) window;
	}
} // game