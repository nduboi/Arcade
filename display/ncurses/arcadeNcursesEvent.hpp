//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADENcursesEVENT_HPP
#define ARCADENcursesEVENT_HPP

#include <memory>
#include "IEvent.hpp"
#include "IWindow.hpp"
#include "arcadeNcurses.hpp"

class arcadeNcursesEvent : public IEvent {
private:
	IWindow &_window;
public:
	void init() override;

	IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

	std::pair<int, int> getMousePos() override;

	void cleanup() override;

	arcadeNcursesEvent(IWindow &window);

	~arcadeNcursesEvent() = default;
};

#endif //ARCADENcursesEVENT_HPP
