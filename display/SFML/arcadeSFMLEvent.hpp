//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADESFMLEVENT_HPP
#define ARCADESFMLEVENT_HPP

#include <memory>
#include <chrono>

#include "arcadeSFML.hpp"
#include "IEvent.hpp"
#include "IWindow.hpp"

class arcadeSFMLEvent : public IEvent {
private:
	std::shared_ptr<IWindow> _window;
	std::pair<int, int> _mapSize;
	std::pair<int, int> _mousePos;
	std::string _input;
	bool _iswritting;
	std::chrono::time_point<std::chrono::steady_clock> _timePoint;

public:
	void init() override;

	IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

	std::pair<int, int> getMousePos() override;

	void setMapSize(std::pair<int, int> size) override;

	void cleanup() override;

	std::string getUsername();

	void renderWrittiing();

	arcadeSFMLEvent(std::shared_ptr<IWindow> window);

	~arcadeSFMLEvent() = default;
};

#endif //ARCADECACAEVENT_HPP
