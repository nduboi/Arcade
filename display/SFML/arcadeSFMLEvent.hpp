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
	std::string _textInput;
	bool _isInputActive;
public:
	void init() override;

	IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;

	std::pair<int, int> getMousePos() override;

	void setMapSize(std::pair<int, int> size) override;

	void cleanup() override;

	std::string getTextInput();
    void setTextInput(const std::string& text);
    void clearTextInput();
    void addCharToInput(char c);
    void removeLastChar();
    bool isInputActive() const;
    void setInputActive(bool active);

	std::string getUsername();

	void renderWrittiing();

	arcadeSFMLEvent(std::shared_ptr<IWindow> window);

	~arcadeSFMLEvent() = default;
};

#endif //ARCADECACAEVENT_HPP
