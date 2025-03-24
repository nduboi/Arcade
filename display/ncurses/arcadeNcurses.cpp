/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNcurses
*/

#include "arcadeNcurses.hpp"

arcadeNcurses::arcadeNcurses()
{
    _window = nullptr;
    _isOpen = false;
}

arcadeNcurses::~arcadeNcurses()
{
    closeWindow();
}

void arcadeNcurses::initWindow()
{
    _window = initscr();
    noecho();
    curs_set(0);
    keypad(_window, TRUE);
    _isOpen = true;
}

void arcadeNcurses::display()
{
    refresh();
}

void arcadeNcurses::closeWindow()
{
    if (_isOpen) {
        endwin();
        _isOpen = false;
    }
}

bool arcadeNcurses::isOpen()
{
    return _isOpen;
}

void arcadeNcurses::clear()
{
    if (_isOpen)
        erase();
}

void arcadeNcurses::drawSprite(std::string asset, int color, std::pair<size_t, size_t> position)
{
    mvprintw(position.second, position.first, "%s", asset.c_str());
}

void arcadeNcurses::drawRectangle(int color, std::pair<size_t, size_t> position)
{
    mvprintw(position.second, position.first, "█");
}

void arcadeNcurses::drawText(std::string text, int color, std::pair<size_t, size_t> position)
{
    mvprintw(position.second, position.first, "%s", text.c_str());
}

void arcadeNcurses::setMapSize(std::pair<int, int> size) {
    _mapSize = size;
}
