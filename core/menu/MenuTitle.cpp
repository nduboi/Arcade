/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MenuTitle
*/

#include "MenuTitle.hpp"
#include <iostream>
MenuTitle::MenuTitle(const std::shared_ptr<IWindow> &window, const std::string& title,
    const std::pair<int, int>& position, int fontSize) : _window(window)
{
    this->_title = title;
    this->_position = position;
    this->_fontSize = fontSize;
}

void MenuTitle::draw(const std::shared_ptr<IWindow> &window)
{
    if (window) {
        window->drawTextMenu(this->_title, this->_position, {253,176,42}, this->_fontSize);
    }
}

void MenuTitle::setTitle(const std::string& title)
{
    this->_title = title;
}

std::string MenuTitle::getTitle() const
{
    return this->_title;
}

void MenuTitle::setPosition(const std::pair<int, int>& position)
{
    this->_position = position;
}

void MenuTitle::setFontSize(int fontSize)
{
    this->_fontSize = fontSize;
}
