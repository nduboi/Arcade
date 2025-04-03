/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#ifndef MENU_HPP
#define MENU_HPP

#include "IGameModule.hpp"
#include "IMenu.hpp"
#include "MenuTitle.hpp"
#include <memory>
#include <vector>
#include <string>

class Menu : public IMenu {
	private:
		std::string _username;
		std::shared_ptr<IWindow> _window;
		MenuTitle _menuTitle;
		MenuTitle _libraryTitle;
		MenuTitle _gameTitle;
	public:
		// Getter
		std::vector<Boxes> getBoxPoses() override;
		std::string getUsername() override;

		// Method
		void displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes, std::vector<std::string> libs,
			std::vector<std::string> games) override;

		// Setter
		void setUsername(std::string username) override;
		void setMenuTitle(const std::string& title,
			const std::pair<int, int>& position = {200, 50}, int fontSize = 36);

		// Constructor
		Menu(const std::shared_ptr<IWindow> &window);
};

#endif // MENU_HPP
