//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include "arcadeQT.hpp"
#include <QKeyEvent>
#include <QMouseEvent>

// Define the event handler implementation
arcadeQT::EventHandler::EventHandler(arcadeQT* parent) : QObject(nullptr), _arcade(parent) {}

bool arcadeQT::EventHandler::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == _arcade->_window || watched == _arcade->_centralWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            _arcade->_lastEvent.type = QEvent::KeyPress;
            _arcade->_lastEvent.key = keyEvent->key();
            _arcade->_lastEvent.processed = false;
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            _arcade->_lastEvent.type = QEvent::MouseButtonPress;
            _arcade->_lastEvent.mouseButton = mouseEvent->button();
            _arcade->_lastEvent.mouseX = mouseEvent->x();
            _arcade->_lastEvent.mouseY = mouseEvent->y();
            _arcade->_lastEvent.processed = false;
            return true;
        }
        else if (event->type() == QEvent::Close) {
            _arcade->_lastEvent.type = QEvent::Close;
            _arcade->_lastEvent.processed = false;
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void arcadeQT::display() {
    _app->processEvents();
    _window->update();
}

void arcadeQT::closeWindow() {
    if (_window) {
        _window->close();
        _isOpen = false;
    }
}

bool arcadeQT::isOpen() {
    return _isOpen;
}

void arcadeQT::clear() {
    if (_centralWidget) {
        _centralWidget->update();
    }
}

std::pair<int, int> arcadeQT::_getWindowPosition(std::pair<int, int> position) {
    return {0, 0};
}

// void arcadeQT::_resizeData(sf::Sprite &sprite, std::pair<int, int> position) {
// }

// void arcadeQT::_resizeData(sf::RectangleShape &rectangle, std::pair<int, int> position) {
// }

void arcadeQT::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
}

void arcadeQT::drawRectangle(int color, std::pair<size_t, size_t> position) {
}

void arcadeQT::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color)
{
}

void arcadeQT::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize)
{
}

void arcadeQT::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position)
{
}

void arcadeQT::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness)
{
}

std::pair<int, int> arcadeQT::getWindowSize() {
    return {0, 0};
}

bool arcadeQT::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
    return false;
}

void arcadeQT::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
}

void arcadeQT::setMapSize(std::pair<size_t, size_t> size) {
    this->_mapSize = size;
}

void arcadeQT::resizeWindow(size_t x, size_t y) {
}

arcadeQT::arcadeQT() : _isOpen(true)
{
    int argc = 0;
    _app = new QApplication(argc, nullptr);
    _window = new QMainWindow();
    _centralWidget = new QWidget(_window);
    _eventHandler = new EventHandler(this);

    _window->installEventFilter(_eventHandler);
    _centralWidget->installEventFilter(_eventHandler);

    _window->setCentralWidget(_centralWidget);
    _window->setWindowTitle("Arcade - Qt5");
    _window->resize(1620, 900);
    _window->show();

    _mapSize = {0, 0};
}

arcadeQT::~arcadeQT() {
    delete _eventHandler;
    delete _centralWidget;
    delete _window;
    delete _app;
	_eventHandler = nullptr;
	_window = nullptr;
	_centralWidget = nullptr;
	_app = nullptr;
}
