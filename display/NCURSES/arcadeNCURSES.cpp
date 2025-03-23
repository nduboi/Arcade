/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNCURSES
*/

#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "arcadeNCURSES.hpp"

#include <ncurses.h>
#include <exception> // Hides the cursor

void arcadeNCURSES::_displayHeader() {
    box(this->header, 0, 0);
    int x = (COLS - std::string("Arcade Ncurses").length()) / 2;
    int y = 1;
    mvwprintw(this->header, y, x, "Arcade Ncurses");
    this->poxXCloseButton = COLS - 5;
    this->poxYCloseButton = 1;
    mvwprintw(this->header, this->poxYCloseButton, this->poxXCloseButton, "[X]");
}

void arcadeNCURSES::initWindow()
{
    sleep(1);
    this->header = subwin(this->mainWindow, 3, COLS, 0, 0);
    if (!this->header) {
        throw std::runtime_error("Canot create header");
    }
    this->_displayHeader();
    this->game = subwin(this->mainWindow, 0, 0, 4, 0);
    if (!this->game) {
        throw std::runtime_error("Canot create game");
    }
}

void arcadeNCURSES::display()
{
    if (!this->_isOpen) {
        std::cerr << "Error: Trying to refresh a closed window" << std::endl;
        return;
    }
    if (this->header && is_wintouched(this->header))
        wrefresh(this->header);
    if (this->game && is_wintouched(this->game))
        wrefresh(this->game);
}

void arcadeNCURSES::closeWindow()
{
    if (this->header && is_wintouched(this->header))
        delwin(this->header);
    if (this->game && is_wintouched(this->game))
        delwin(this->game);
    endwin();
    this->_isOpen = false;
    std::cout << "Closing Window" << std::endl;
}

bool arcadeNCURSES::isOpen() {
    return this->_isOpen;
}

void arcadeNCURSES::clear()
{
    if (this->game && is_wintouched(this->game)) {
        werase(this->game);
    }
}

void arcadeNCURSES::drawSprite(std::string asset, int color, std::pair<int, int> position)
{
}

void arcadeNCURSES::drawRectangle(int color, std::pair<int, int> position)
{
    attron(COLOR_PAIR(color));
    for (int i = 0; i < 5; ++i) {
        mvwprintw(this->game, position.second + i, position.first, "#####");
    }
    attroff(COLOR_PAIR(color));
}

void arcadeNCURSES::drawText(std::string text, int color, std::pair<int, int> position)
{
    attron(COLOR_PAIR(color));
    mvwprintw(this->game, position.second, position.first, text.c_str());
    attroff(COLOR_PAIR(color));
}

void arcadeNCURSES::setMapSize(std::pair<int, int> size)
{
    if (!this->game) {
        throw std::runtime_error("Cannot create game");
    }
    if (wresize(this->game, size.first, size.second) == ERR) {
        throw std::runtime_error("Cannot resize subwindow");
    }
    box(this->game, 0, 0);
}

arcadeNCURSES::arcadeNCURSES()
{
    system("reset");
    system("clear");
    system("stty sane");
    if (!isendwin())
        endwin();
    sleep(1);
    this->mainWindow = initscr();
    sleep(1);
    nodelay(stdscr, TRUE);
    if (this->mainWindow != stdscr) {
        this->arcadeNCURSES::closeWindow();
        std::cerr << "Error: initscr() failed" << std::endl;
        throw std::runtime_error("Error: initscr() failed");
    }
    start_color();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    this->_isOpen = true;
}

arcadeNCURSES::~arcadeNCURSES()
{
    this->arcadeNCURSES::closeWindow();
    system("reset");
    std::cout << "Destroying arcadeNCURSES instance" << std::endl;
}
