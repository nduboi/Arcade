//
// Created by roussierenoa on 3/20/25.
//

#include "arcadeQTEvent.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCoreApplication>

void arcadeQTEvent::init()
{
}

IEvent::event_t arcadeQTEvent::pollEvents(std::pair<int, int> gridSize) {
    auto qtWindow = std::dynamic_pointer_cast<arcadeQT>(_window);

    if (!qtWindow || !qtWindow->_app)
        return IEvent::NOTHING;

    QCoreApplication::processEvents();

    auto& eventData = qtWindow->_lastEvent;

    if (eventData.processed || eventData.type == -1)
        return IEvent::NOTHING;

    eventData.processed = true;
    if (eventData.type == QEvent::KeyPress) {
        if (this->_iswritting) {
            int key = eventData.key;
            if (key >= Qt::Key_Space && key <= Qt::Key_AsciiTilde && _input.length() <= 15) {
                char c = key;
                if (key >= Qt::Key_A && key <= Qt::Key_Z) {
                    c = 'a' + (key - Qt::Key_A);
                }
                _input += c;
                return IEvent::NOTHING;
            } else if (key == Qt::Key_Backspace && !_input.empty()) {
                _input.pop_back();
                return IEvent::NOTHING;
            }
        }

        switch (eventData.key) {
            case Qt::Key_Up:
                return IEvent::UP;
            case Qt::Key_Down:
                return IEvent::DOWN;
            case Qt::Key_Left:
                return IEvent::LEFT;
            case Qt::Key_Right:
                return IEvent::RIGHT;
            case Qt::Key_Escape:
                return IEvent::ESCAPE;
            case Qt::Key_Space:
                return IEvent::SPACE;
            case Qt::Key_Return:
            case Qt::Key_Enter:
                return IEvent::ENTER;
            case Qt::Key_M:
                return IEvent::MENU;
            case Qt::Key_N:
                return IEvent::NEXTGRAPHIC;
            case Qt::Key_R:
                return IEvent::REFRESH;
            case Qt::Key_G:
                return IEvent::NEXTGAME;
            case Qt::Key_H:
                return IEvent::NEXTDIFFICULTY;
            case Qt::Key_Q:
                return IEvent::CLOSE;
            default:
                break;
        }
    } else if (eventData.type == QEvent::MouseButtonPress) {
        this->_mousePos = {eventData.mouseX, eventData.mouseY};

        if (this->_mousePos.first >= 725 && this->_mousePos.first <= 900 && 
            this->_mousePos.second >= 120 && this->_mousePos.second <= 160)
            this->_iswritting = true;

        switch (eventData.mouseButton) {
            case Qt::RightButton:
                return MOUSERIGHTCLICK;
            case Qt::LeftButton:
                return MOUSELEFTCLICK;
            case Qt::MiddleButton:
                return MOUSECLICK;
            default:
                break;
        }
    } else if (eventData.type == QEvent::Close) {
        return IEvent::CLOSE;
    }

    return IEvent::NOTHING;
}

std::pair<int, int> arcadeQTEvent::getMousePos()
{
    auto qtWindow = std::dynamic_pointer_cast<arcadeQT>(_window);
    const int hudOffset = 100;

    if (_mousePos.first < 0 || _mousePos.second < hudOffset)
        return {-1, -1};

    if (this->_mapSize.first > 0 && this->_mapSize.second > 0) {
        if (qtWindow && qtWindow->_window) {
            int width = qtWindow->_window->width();
            int height = qtWindow->_window->height();
            return {
                (this->_mousePos.first * this->_mapSize.first) / width,
                ((this->_mousePos.second - hudOffset) * this->_mapSize.second) / (height - hudOffset)
            };
        }
    }
    return this->_mousePos;
}

void arcadeQTEvent::setMapSize(std::pair<int, int> size) {
    _mapSize = size;
}

void arcadeQTEvent::cleanup() {
}

std::string arcadeQTEvent::getUsername()
{
    return _input;
}

void arcadeQTEvent::renderWrittiing()
{
    this->_window->drawTextMenu(
        _input,
        {685, 407},
        {0, 0, 0},
        24
    );
}

arcadeQTEvent::arcadeQTEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = std::make_pair(0, 0);
    this->_mapSize = std::make_pair(0, 0);
    this->_iswritting = false;
    this->_input = "";
}
