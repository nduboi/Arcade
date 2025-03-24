/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** arcadeNcursesEncapsulation
*/

#ifndef ARCADE_NCURSES_WRAPPER_HPP
#define ARCADE_NCURSES_WRAPPER_HPP

#include <ncurses.h>

class NcursesWrapper {
    public:
        // Constructor
        NcursesWrapper();
        ~NcursesWrapper();

        // Method
        void printAt(int x, int y, const char *text);
        void refreshScreen();
        void clearScreen();

    private:
        // Variable
        WINDOW* _window;
};

#endif // ARCADE_NCURSES_WRAPPER_HPP
