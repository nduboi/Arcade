//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADESFMLEVENT_HPP
#define ARCADESFMLEVENT_HPP

#include <IEvent.hpp>
#include <IWindow.hpp>
#include <memory>

#include "arcadeSFML.hpp"
#include "IEvent.hpp"


class arcadeSFMLEvent : public IEvent {
private:
	IWindow &_window;
public:
	void init() override;

	IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

	std::pair<int, int> getMousePos() override;

	void cleanup() override;

	arcadeSFMLEvent(IWindow &window);

	~arcadeSFMLEvent() = default;
};



#endif //ARCADECACAEVENT_HPP
