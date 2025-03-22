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


void arcadeNCURSES::initWindow()
{
}

void arcadeNCURSES::display()
{
    wrefresh(this->window);
    usleep(50000);
}

void arcadeNCURSES::closeWindow()
{
    if (this->window) {
        delwin(this->window);
        this->window = nullptr;
    }
    endwin();
    this->_isOpen = false;
}

bool arcadeNCURSES::isOpen() {
    return this->_isOpen;
}

void arcadeNCURSES::clear()
{
    werase(this->window);
}

void arcadeNCURSES::drawSprite(std::string asset, int color, std::pair<int, int> position)
{
    attron(COLOR_PAIR(color));
    mvwprintw(this->window, position.second, position.first, asset.c_str());
    attroff(COLOR_PAIR(color));
}

void arcadeNCURSES::drawRectangle(int color, std::pair<int, int> position)
{
    attron(COLOR_PAIR(color));
    for (int i = 0; i < 5; ++i) {
        mvwprintw(this->window, position.second + i, position.first, "#####");
    }
    attroff(COLOR_PAIR(color));
}

void arcadeNCURSES::drawText(std::string text, int color, std::pair<int, int> position)
{
    attron(COLOR_PAIR(color));
    mvprintw(position.second, position.first, text.c_str());
    attroff(COLOR_PAIR(color));
}

void arcadeNCURSES::setMapSize(std::pair<int, int> size)
{
    resize_term(size.second, size.first);
}

arcadeNCURSES::arcadeNCURSES()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    timeout(50);
    int height = 10, width = 40;
    int startY = 5, startX = 10;
    this->window = newwin(LINES, COLS, 0, 0);
    if (this->window == nullptr) {
        endwin();
        std::cerr << "Cannot create the window" << std::endl;
        return;
    }
    this->_isOpen = true;
}

arcadeNCURSES::~arcadeNCURSES()
{
    if (this->_isOpen) {
        arcadeNCURSES::closeWindow();
    }
}
