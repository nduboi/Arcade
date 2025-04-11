//
// Created by roussierenoa on 3/26/25.
//

#include <iostream>
#include "arcadeNcursesEvent.hpp"
#include "arcadeNcurses.hpp"

namespace DisplayLib {
	void arcadeNcursesEvent::init() {
	}

	IEvent::event_t arcadeNcursesEvent::pollEvents(std::pair<int, int> gridSize) {
        int ch = wgetch(stdscr);
        (void)gridSize;
		if (ch == -1)
			return NOTHING;

        MEVENT event;
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                this->_mousePos = {event.x, event.y};
				auto pos = getMousePos();

                if (pos.first >= 725 && pos.first <= 900 &&
                    pos.second >= 120 && pos.second <= 180) {
                    this->_isWriting = true;
                } else {
                    this->_isWriting = false;
                }
            	if (event.bstate & BUTTON1_PRESSED)
                    return IEvent::MOUSELEFTCLICK;
                if (event.bstate & BUTTON3_PRESSED)
                    return IEvent::MOUSERIGHTCLICK;
            }
        }

        if (this->_isWriting) {
            if (ch >= 32 && ch <= 126) {
                if (this->_input.length() <= 15) {
                    this->_input += static_cast<char>(ch);
                }
                return IEvent::NOTHING;
            }
            if (ch == 27) {
                this->_input.clear();
                return IEvent::NOTHING;
            }
            if (ch == 10) {
                return IEvent::ENTER;
            }
            if (ch == KEY_BACKSPACE) {
                if (!this->_input.empty()) {
                    this->_input.pop_back();
                }
                return IEvent::NOTHING;
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
            case 'h':
                return IEvent::NEXTDIFFICULTY;
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
            default:
                return IEvent::NOTHING;
        }
    }

	std::pair<int, int> arcadeNcursesEvent::getMousePos() {
		std::pair<int, int> tmp = this->_mousePos;
		auto ncurses = std::dynamic_pointer_cast<arcadeNcurses>(this->_window);
		if (!ncurses) {
			throw std::runtime_error("Failed to cast _window to arcadeNcurses");
		}
		auto mapSize = ncurses->getMapSize();
		if (mapSize.first == 0 && mapSize.second == 0) {
			tmp.second = (900 * (tmp.second) / (LINES - 4)) - 54;
			tmp.first = (1600 * tmp.first / COLS);
		} else {
			int startY = (LINES - (mapSize.second + 2) + 4) / 2;
			tmp.second -= (startY);
			tmp.first -= ((COLS - 2)) / 2 - mapSize.first + 1;
			tmp.first /= 2;
		}
#ifdef _DEBUG
		std::cout << "Mouse POS: x= " << tmp.first << " y=" << tmp.second << std::endl;
		std::cout << "MAP SIZE: x= " << mapSize.first << " y=" << mapSize.second << std::endl;
#endif
		return tmp;
	}

	void arcadeNcursesEvent::setMapSize(std::pair<int, int> size) {
		(void)size;
	}

	void arcadeNcursesEvent::cleanup() {
	}

	std::string arcadeNcursesEvent::getUsername() {
		return this->_input;
	}

	void arcadeNcursesEvent::renderWrittiing() {
		this->_window->drawTextMenu(
			this->_input,
			{685, 407},
			{0, 0, 0},
			24
		);
	}

	arcadeNcursesEvent::arcadeNcursesEvent(std::shared_ptr<IWindow> window) {
		this->_window = window;
	}
} // game