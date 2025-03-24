//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADE_NCURSES_EVENT_HPP
#define ARCADE_NCURSES_EVENT_HPP

#include "IEvent.hpp"
#include "IWindow.hpp"
#include <ncurses.h>

class arcadeNcursesEvent : public IEvent {
	public:
		// Constructor
		explicit arcadeNcursesEvent(IWindow &window);
		~arcadeNcursesEvent() override = default;

		// Method
		void init() override;
		IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;
		void cleanup() override;

		void setMapSize(std::pair<int, int> size) override;

		// Getter
		std::pair<int, int> getMousePos() override;

	private:
		// Variable
		IWindow &_window;
};

#endif // ARCADE_NCURSES_EVENT_HPP
