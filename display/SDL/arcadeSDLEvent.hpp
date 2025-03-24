//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADESDLEVENT_HPP
#define ARCADESDLEVENT_HPP

#include "IEvent.hpp"
#include "IWindow.hpp"
#include <memory>

#include "arcadeSDL.hpp"

class arcadeSDLEvent : public IEvent {
private:
	IWindow &_window;
	std::pair<int, int> _mapSize;
	std::pair<int, int> _mousePos;
public:
	void init() override;

	IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

	std::pair<int, int> getMousePos() override;

	void setMapSize(std::pair<int, int> size) override;

	void cleanup() override;

	arcadeSDLEvent(IWindow &window);

	~arcadeSDLEvent() = default;
};

#endif //ARCADESDLEVENT_HPP
