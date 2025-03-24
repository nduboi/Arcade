/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** arcadeNcursesEncapsulation
*/

#include "arcadeNcursesWrapper.hpp"

NcursesWrapper::NcursesWrapper()
{
    _window = initscr();
    noecho();
    curs_set(0);
}

NcursesWrapper::~NcursesWrapper()
{
    endwin();
}

void NcursesWrapper::printAt(int x, int y, const char *text)
{
    mvprintw(y, x, "%s", text);
}

void NcursesWrapper::refreshScreen()
{
    refresh();
}

void NcursesWrapper::clearScreen()
{
    erase();
}
