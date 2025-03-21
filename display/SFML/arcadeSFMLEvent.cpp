//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeSFMLEvent.hpp"

#include <iostream>
#include <memory>

void arcadeSFMLEvent::init() {
}

IEvent::event_t arcadeSFMLEvent::pollEvents(std::pair<int, int> gridSize) {
    sf::Event event{};
    auto &sfmlWindow = static_cast<arcadeSFML &>(_window);

    if (sfmlWindow.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return IEvent::CLOSE;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    return IEvent::UP;
                case sf::Keyboard::Down:
                    return IEvent::DOWN;
                case sf::Keyboard::Left:
                    return IEvent::LEFT;
                case sf::Keyboard::Right:
                    return IEvent::RIGHT;
                case sf::Keyboard::Escape:
                    return IEvent::ESCAPE;
                case sf::Keyboard::Space:
                    return IEvent::SPACE;
                case sf::Keyboard::Enter:
                    return IEvent::ENTER;
            }
        }
        if (event.type == sf::Event::JoystickMoved) {
            if (event.joystickMove.axis== sf::Joystick::Axis::PovX) {
                if (sf::Joystick::getAxisPosition(event.joystickMove.joystickId, sf::Joystick::Axis::PovX) > 0)
                    return IEvent::UP;
                return IEvent::DOWN;
            }
            if (event.joystickMove.axis == sf::Joystick::PovY) {
                if (sf::Joystick::getAxisPosition(event.joystickMove.joystickId, sf::Joystick::Axis::PovY) > 0)
                    return IEvent::RIGHT;
                return IEvent::LEFT;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
            return IEvent::MOUSECLICK;
    }
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeSFMLEvent::getMousePos() {
	return {};
}

void arcadeSFMLEvent::cleanup() {
}

arcadeSFMLEvent::arcadeSFMLEvent(IWindow &window) : _window(window) { // Accept a reference and store as a raw pointer
}
