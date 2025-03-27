//
// Created by roussierenoa on 3/26/25.
//

#include "arcadeNcursesEvent.hpp"


namespace Display {
	void arcadeNcursesEvent::init() {
	}

	IEvent::event_t arcadeNcursesEvent::pollEvents(std::pair<int, int> gridSize) {
		int ch = wgetch(stdscr);

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
		return {0, 0};
	}

	void arcadeNcursesEvent::setMapSize(std::pair<int, int> size) {
	}

	void arcadeNcursesEvent::cleanup() {
	}

	arcadeNcursesEvent::arcadeNcursesEvent(std::shared_ptr<IWindow> window) {
	}
} // game