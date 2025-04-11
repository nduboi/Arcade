//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeSFMLEvent.hpp"

#include <iostream>
#include <memory>
#include <utility>

void arcadeSFMLEvent::init()
{
}

IEvent::event_t arcadeSFMLEvent::pollEvents(std::pair<int, int> gridSize) {
    sf::Event event{};
    auto sfmlWindow = std::dynamic_pointer_cast<arcadeSFML>(_window);

    if (sfmlWindow->window .pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return IEvent::CLOSE;

        if (event.type == sf::Event::TextEntered && this->_iswritting == true) {
            if (event.text.unicode >= 32 && event.text.unicode <= 126 && _input.length() <= 15)
                _input += static_cast<char>(event.text.unicode);
            else if (event.text.unicode == 8 && !_input.empty())
                _input.pop_back();
            else if (event.text.unicode == 13) {
                this->_iswritting = false;
                this->_mousePos = {730, 480};
                return IEvent::MOUSELEFTCLICK;
            }
            return IEvent::NOTHING;
        }
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
                case sf::Keyboard::M:
                    return IEvent::MENU;
                case sf::Keyboard::N:
                    return IEvent::NEXTGRAPHIC;
                case sf::Keyboard::R:
                    return IEvent::REFRESH;
                case sf::Keyboard::G:
                    return IEvent::NEXTGAME;
                case sf::Keyboard::H:
                    return IEvent::NEXTDIFFICULTY;
                case sf::Keyboard::Q:
                    return IEvent::CLOSE;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            this->_mousePos = {event.mouseButton.x, event.mouseButton.y};
            if (this->_mousePos.first >= 725 && this->_mousePos.first <= 900 && this->_mousePos.second >= 120 && this->_mousePos.second <= 180)
                this->_iswritting = true;
            if (_iswritting && (this->_mousePos.first >= 690 && this->_mousePos.first <= 790 && this->_mousePos.second >= 470 && this->_mousePos.second <= 510))
                this->_iswritting = false;
            if (_iswritting && (this->_mousePos.first >= 840 && this->_mousePos.first <= 940 && this->_mousePos.second >= 470 && this->_mousePos.second <= 510))
                this->_iswritting = false;
            if (event.mouseButton.button == sf::Mouse::Right)
                return MOUSERIGHTCLICK;
            if (event.mouseButton.button == sf::Mouse::Left)
                return MOUSELEFTCLICK;
            if (event.mouseButton.button == sf::Mouse::Middle)
                return MOUSECLICK;
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

std::pair<int, int> arcadeSFMLEvent::getMousePos()
{
    auto sfmlWindow = std::dynamic_pointer_cast<arcadeSFML>(this->_window);
    const int hudOffset = 100;

    if (_mousePos.first < 0 || _mousePos.second < hudOffset)
        return {-1, -1};
    if (this->_mapSize.first > 0 && this->_mapSize.second > 0) {
        sf::Vector2u winSize = sfmlWindow->window.getSize();
        return {
            (this->_mousePos.first * this->_mapSize.first) / static_cast<int>(winSize.x),
            ((this->_mousePos.second - hudOffset) * this->_mapSize.second) / static_cast<int>(winSize.y - hudOffset)
        };
    }
    return this->_mousePos;
}

void arcadeSFMLEvent::setMapSize(std::pair<int, int> size) {
    _mapSize = size;
}

void arcadeSFMLEvent::cleanup() {
}

std::string arcadeSFMLEvent::getUsername()
{
    return _input;
}

void arcadeSFMLEvent::renderWrittiing()
{
    std::string username = _input;

    if (username.empty()) {
        this->_window->drawTextMenu(
            "No Name",
            {685, 407},
            {127, 127, 127},
            24
        );
        return;
    }

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - this->_timePoint;
    if (elapsed_seconds.count() > 0.5)
        username += "|";
    if (elapsed_seconds.count() > 1)
        this->_timePoint = std::chrono::steady_clock::now();

    this->_window->drawTextMenu(
        username,
        {685, 407},
        {0, 0, 0},
        24
    );
}

arcadeSFMLEvent::arcadeSFMLEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = std::make_pair(0, 0);
    this->_mapSize = std::make_pair(0, 0);
    this->_iswritting = false;
    this->_input = "";
    this->_timePoint = std::chrono::steady_clock::now();
}
