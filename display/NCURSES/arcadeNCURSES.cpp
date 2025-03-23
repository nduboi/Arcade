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
#include <exception>

void arcadeNCURSES::initWindow()
{
    sleep(1);
    this->header = subwin(this->mainWindow, 3, COLS, 0, 0);
    if (!this->header) {
        throw std::runtime_error("Canot create header");
    }
    box(this->header, 0, 0);
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
    // if (this->mainWindow && is_wintouched(this->mainWindow)) {
    //     refresh();
    // }
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
    if (this->header && is_wintouched(this->header))
        wrefresh(this->header);
    if (this->game && is_wintouched(this->game))
        wrefresh(this->game);
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
    if (this->game && is_wintouched(this->game))
        delwin(this->game);
    this->game = subwin(this->mainWindow, size.first, size.second, 4, 4);
    if (!this->game) {
        throw std::runtime_error("Cannot create game");
    }
    box(this->game, 0, 0);
}

arcadeNCURSES::arcadeNCURSES()
{
    std::cout << "Creating initScr" << std::endl;
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
