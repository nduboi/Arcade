//
// Created by roussierenoa on 3/20/25.
//

#ifndef ARCADECACAEVENT_HPP
#define ARCADECACAEVENT_HPP

#include <IEvent.hpp>
#include <IWindow.hpp>
#include "IEvent.hpp"


class arcadeCacaEvent : public IEvent {
private:
	IWindow & _window;
public:
	void init() override;

	int pollEvents() override;

	void cleanup() override;

	arcadeCacaEvent(IWindow &window);

	~arcadeCacaEvent() = default;
};



#endif //ARCADECACAEVENT_HPP
