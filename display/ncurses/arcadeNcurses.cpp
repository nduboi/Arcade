/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNcurses
*/

#include "arcadeNcurses.hpp"
#include <iostream>

arcadeNcurses::arcadeNcurses()
{
    this->_window = nullptr;
    this->_isOpen = false;
}

arcadeNcurses::~arcadeNcurses()
{
    if (!isendwin()) {
        endwin();
    }
}

void arcadeNcurses::initWindow()
{
    this->_window = initscr();
    if (this->_window != stdscr)
        throw std::runtime_error("Failed to open window initscr()");
    this->_window = initscr();
    if (this->_window != stdscr)
        throw std::runtime_error("Failed to open window initscr()");
    noecho();
    curs_set(0);
    timeout(0);
    keypad(this->_window, TRUE);
    noecho();
    curs_set(0);
    keypad(this->_window, TRUE);
    this->_isOpen = true;
}

void arcadeNcurses::display()
{
    if (this->_window == nullptr || this->_window != stdscr) {
        std::cerr << "The window is broken, reinitializing..." << std::endl;
        this->initWindow();
    }
    if (this->_window == stdscr) {
        refresh();
    }
}

void arcadeNcurses::closeWindow() {
    if (this->_isOpen) {
        endwin();
        if (this->_window != stdscr && this->_window != nullptr) {
            delwin(this->_window);
        }
        this->_window = nullptr;
    }
    this->_isOpen = false;
}

bool arcadeNcurses::isOpen()
{
    return this->_isOpen;
}

void arcadeNcurses::clear()
{
    if (this->_isOpen)
        erase();
}

void arcadeNcurses::drawSprite(std::string asset, int color, std::pair<size_t, size_t> position)
{
}

void arcadeNcurses::drawRectangle(int color, std::pair<size_t, size_t> position)
{
    if (this->_window != stdscr)
        return;
    mvprintw(position.second, position.first, "█");
}

void arcadeNcurses::drawText(std::string text, int color, std::pair<size_t, size_t> position)
{
    if (this->_window != stdscr)
        return;
    mvprintw(position.second, position.first, "%s", text.c_str());
}

void arcadeNcurses::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}
