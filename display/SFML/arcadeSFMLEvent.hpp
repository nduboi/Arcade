//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADESFMLEVENT_HPP
#define ARCADESFMLEVENT_HPP

#include <memory>

#include "arcadeSFML.hpp"
#include "IEvent.hpp"
#include "IWindow.hpp"

class arcadeSFMLEvent : public IEvent {
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

	arcadeSFMLEvent(std::shared_ptr<IWindow> window);

	~arcadeSFMLEvent() = default;
};

#endif //ARCADECACAEVENT_HPP
