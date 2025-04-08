//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeSFMLEvent.hpp"

#include <iostream>
#include <memory>
#include <utility>

void arcadeSFMLEvent::init()
{
    _textInput = "";
    _isInputActive = false;
}

IEvent::event_t arcadeSFMLEvent::pollEvents(std::pair<int, int> gridSize) {
    sf::Event event{};
    auto sfmlWindow = std::dynamic_pointer_cast<arcadeSFML>(_window);

    if (sfmlWindow->window .pollEvent(event)) {
        if (_isInputActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && !_textInput.empty()) {
                removeLastChar();
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                char character = static_cast<char>(event.text.unicode);
                if ((character >= 'a' && character <= 'z') ||
                    (character >= 'A' && character <= 'Z') ||
                    (character >= '0' && character <= '9') ||
                    character == '_') {
                    if (_textInput.length() < 15) {
                        addCharToInput(character);
                    }
                }
            }
            return IEvent::TYPING;
        }
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
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            this->_mousePos = {event.mouseButton.x, event.mouseButton.y};
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

std::string arcadeSFMLEvent::getUsername() {
    return "";
}

std::string arcadeSFMLEvent::getTextInput()
{
    return _textInput;
}

void arcadeSFMLEvent::setTextInput(const std::string& text)
{
    _textInput = text;
}

void arcadeSFMLEvent::clearTextInput()
{
    _textInput.clear();
}

void arcadeSFMLEvent::addCharToInput(char c)
{
    _textInput += c;
}

void arcadeSFMLEvent::removeLastChar()
{
    if (!_textInput.empty()) {
        _textInput.pop_back();
    }
}

bool arcadeSFMLEvent::isInputActive() const
{
    return _isInputActive;
}

void arcadeSFMLEvent::setInputActive(bool active)
{
    _isInputActive = active;
}

void arcadeSFMLEvent::renderWrittiing()
{
    
}

arcadeSFMLEvent::arcadeSFMLEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = std::make_pair(0, 0);
    this->_mapSize = std::make_pair(0, 0);
    this->_textInput = "";
    this->_isInputActive = false;
}
