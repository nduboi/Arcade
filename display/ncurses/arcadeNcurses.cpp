/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNcurses
*/

#include <iostream>
#include "arcadeNcurses.hpp"

void arcadeNcurses::initWindow()
{
}

void arcadeNcurses::display() {
}

void arcadeNcurses::closeWindow()
{
     this->_isOpen = false;
}

bool arcadeNcurses::isOpen() {
    return this->_isOpen;
}

void arcadeNcurses::clear() {
}

void arcadeNcurses::drawSprite(std::string asset, int color, std::pair<int, int> position)
{
}

void arcadeNcurses::drawRectangle(int color, std::pair<int, int> position) {
    (void)color;
    (void)position;
}

void arcadeNcurses::drawText(std::string text, int color, std::pair<int, int> position) {
    (void)text;
    (void)color;
    (void)position;
}

void arcadeNcurses::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

arcadeNcurses::arcadeNcurses() : _window(nullptr), _renderer(nullptr)
{

}

arcadeNcurses::~arcadeNcurses()
{

}
