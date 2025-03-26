//
// Created by roussierenoa on 3/26/25.
//

#ifndef ARCADENCURSESEVENT_HPP
#define ARCADENCURSESEVENT_HPP

#include <memory>
#include <ncurses.h>
#include "IWindow.hpp"
#include "IEvent.hpp"

namespace Game {

	class arcadeNcursesEvent : public IEvent {
	private:
		std::shared_ptr<IWindow> _window;
		std::pair<int, int> _mapSize;
		std::pair<int, int> _mousePos;
	public:
		void init() override;

		IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

		std::pair<int, int> getMousePos() override;

		void setMapSize(std::pair<int, int> size) override;

		void cleanup() override;

		arcadeNcursesEvent(std::shared_ptr<IWindow> window);

		~arcadeNcursesEvent() = default;
	};

} // game

#endif //ARCADENCURSESEVENT_HPP
