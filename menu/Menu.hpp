//
// Created by roussierenoa on 3/20/25.
//

#ifndef MENU_HPP
#define MENU_HPP
#include "IGameModule.hpp"
#include "IMenu.hpp"

class Menu : public IMenu {
private:
	std::string _username;

public:

	void displayMenu(std::shared_ptr<IWindow> window, std::vector<Boxes> _boxes, std::vector<std::string> libs, std::vector<std::string> games) override;

	std::vector<Boxes> getBoxPoses(std::shared_ptr<IWindow> window) override;

	std::string getUsername() override {return this->_username;};

	void setUsername(std::string username) override {this->_username = username;};

	Menu();

	~Menu() = default;
};



#endif //MENU_HPP
