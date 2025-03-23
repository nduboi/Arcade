/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** arcadeNCURSES
*/

#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <exception>
#include "arcadeNCURSES.hpp"

void arcadeNCURSES::_initHeader() {
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
    this->header = subwin(this->mainWindow, 3, COLS, 0, 0);
    if (!this->header) {
        throw std::runtime_error("Canot create header");
    }
    this->_initHeader();
    this->game = subwin(this->mainWindow, 0, 0, 4, 0);
    if (!this->game) {
        throw std::runtime_error("Canot create game");
    }
    sleep(1);
}

void arcadeNCURSES::display()
{
    sleep(1);
    if (!this->_isOpen) {
        std::cerr << "Error: Trying to refresh a closed window" << std::endl;
        return;
    }
    if (this->mainWindow == nullptr) {
        std::cerr << "Error: Main window is null" << std::endl;
        this->_isOpen = false;
        return;
    }
    if (this->header != nullptr) {
        box(this->header, 0, 0);
        wrefresh(this->header);
    } else {
        this->_initHeader();
    }
    if (this->game != nullptr) {
        box(this->game, 0, 0);
        wrefresh(this->game);
    } else {
        this->game = subwin(this->mainWindow, 0, 0, 4, 0);
    }
}

void arcadeNCURSES::closeWindow()
{
    if (this->header != nullptr) {
        delwin(this->header);
        this->header = nullptr;
    }
    if (this->game != nullptr) {
        delwin(this->game);
        this->game = nullptr;
    }
    if (this->_isOpen) {
        endwin();
        this->_isOpen = false;
    }
}

bool arcadeNCURSES::isOpen() {
    return this->_isOpen;
}

void arcadeNCURSES::clear()
{
    if (this->game) {
        if (werase(this->game) == ERR) {
            std::cerr << "Error: Failed to clear game window" << std::endl;
        }
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
    if (size.first <= 0 || size.second <= 0)
        return;
    if (!this->game) {
        throw std::runtime_error("Cannot create game");
    }
    if (wresize(this->game, size.first, size.second) == ERR) {
        throw std::runtime_error("Cannot resize subwindow");
    }
    box(this->game, 0, 0);
}

arcadeNCURSES::arcadeNCURSES() : mainWindow(nullptr), header(nullptr), game(nullptr), _isOpen(false)
{
    system("reset");
    system("clear");
    system("stty sane");
    if (!isendwin())
        endwin();
    sleep(1);
    this->mainWindow = initscr();
    if (this->mainWindow == nullptr) {
        throw std::runtime_error("Failed to initialize ncurses");
    }
    nodelay(stdscr, TRUE);
    if (this->mainWindow != stdscr) {
        endwin();
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
    std::cout << "Destroying arcadeNCURSES instance" << std::endl;
}
