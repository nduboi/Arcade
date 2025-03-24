/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** arcadeNcurses
*/

/**
 * @file arcadeNcurses.hpp
 * @brief Header file for the arcadeNcurses class.
 *
 * This file contains the declaration of the arcadeNcurses class, which implements the IDisplayModule interface.
 *
 * @author eliotttesnier
 * @date 3/17/25
 */
#ifndef ARCADE_NCURSES_HPP
#define ARCADE_NCURSES_HPP

#include <ncurses.h>
#include <string>
#include <utility>
#include "IWindow.hpp"

/**
 * @class arcadeNcurses
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeNcurses class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeNcurses : public IWindow {
	public:
		// Constructor
		arcadeNcurses();
		~arcadeNcurses() override;

		// Method
		void initWindow() override;
		void display() override;
		void closeWindow() override;
		bool isOpen() override;
		void clear() override;
		void drawSprite(std::string asset, int color, std::pair<size_t, size_t> position) override;
		void drawRectangle(int color, std::pair<size_t, size_t> position) override;
		void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

		// Setter
		void setMapSize(std::pair<int, int> size) override;

	private:
		// Variable
		WINDOW* _window;
		bool _isOpen;
		std::string _libName = "Arcade Ncurses";
		std::pair<int, int> _mapSize;
};

#endif // ARCADE_NCURSES_HPP
