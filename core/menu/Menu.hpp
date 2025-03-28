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
		std::shared_ptr<IWindow> _window;
		MenuTitle _menuTitle;
	public:
		// Constructor
		Menu(const std::shared_ptr<IWindow> &window);

		// Method
		void displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes, std::vector<std::string> libs,
			std::vector<std::string> games) override;

		// Getter
		std::vector<Boxes> getBoxPoses() override;
		std::string getUsername() override;

		// Setter
		void setUsername(std::string username) override;
		void setMenuTitle(const std::string& title,
			const std::pair<int, int>& position = {200, 50}, int fontSize = 36);

	private:
		// Variable
		std::string _username;

};

#endif // MENU_HPP
