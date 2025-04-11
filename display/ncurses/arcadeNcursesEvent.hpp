//
// Created by roussierenoa on 3/26/25.
//

#ifndef ARCADENCURSESEVENT_HPP
#define ARCADENCURSESEVENT_HPP

#include <memory>
#include <ncurses.h>
#include <chrono>

#include "IWindow.hpp"
#include "IEvent.hpp"

namespace DisplayLib {

	class arcadeNcursesEvent : public IEvent {
	private:
		std::shared_ptr<IWindow> _window;
		std::pair<int, int> _mapSize;
		std::pair<int, int> _mousePos;
		bool _isWriting = false;
		std::string _input;
		std::chrono::time_point<std::chrono::steady_clock> _timePoint;

	public:
		void init() override;

		IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

		std::pair<int, int> getMousePos() override;

		void setMapSize(std::pair<int, int> size) override;

		void cleanup() override;

		virtual std::string getUsername();

		virtual void renderWrittiing();

		arcadeNcursesEvent(std::shared_ptr<IWindow> window);

		~arcadeNcursesEvent() = default;
	};

} // game

#endif //ARCADENCURSESEVENT_HPP
