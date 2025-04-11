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
#include "Saver.hpp"
#include <memory>
#include <vector>
#include <string>

class Menu : public IMenu {
	public:
		//Struct button
		struct Button {
			std::pair<int, int> posTop;
			std::pair<int, int> posBottom;
			std::string text;
			bool selected;
			action_e action;
			std::string value;
		};

		// Constructor
		Menu(const std::shared_ptr<IWindow> &window);

		// Method
		void displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes, std::vector<std::string> libs,
			std::vector<std::string> games) override;
		action_e handleClick(int x, int y, std::string& selectedValue);
		std::string extractNameFromPath(const std::string& path);
		int estimateTextWidth(const std::string& text, int fontSize);
		void drawUsernameInput(const std::shared_ptr<IWindow> &window);
		void drawUsernameButton(const std::shared_ptr<IWindow> &window);
		void drawHighscores(const std::shared_ptr<IWindow> &window);

		// Getter
		std::vector<Boxes> getBoxPoses() override;
		std::string getUsername() override;
		bool getIsWritting();

		// Setter
		void setUsername(std::string username) override;
		void setMenuTitle(const std::string& title,
			const std::pair<int, int>& position = {200, 50}, int fontSize = 36);
		void setSelectedGraphicLib(const std::string& graphicLib);
		void setInputUsername(const std::string& input);

	private:
		// Variable
		std::string _username;
		std::shared_ptr<IWindow> _window;
		MenuTitle _menuTitle;
		MenuTitle _libraryTitle;
		MenuTitle _gameTitle;
		std::vector<Boxes> _boxes;
		std::vector<Button> _graphicLibButtons;
		std::vector<Button> _gameButtons;
		std::string _currentGraphicLib;
		std::vector<Button> _usernameButtons;
		bool _showUsernameInput;
		bool _showHighscores;
		bool _isWritting;
		std::string _inputUsername;
		Boxes _usernameBox;
		Boxes _highscoreBox;

		Saver _saver;

		void initButtons(const std::vector<std::string>& libs, const std::vector<std::string>& games);
		void drawButtons(const std::shared_ptr<IWindow> &window);

};

#endif // MENU_HPP
