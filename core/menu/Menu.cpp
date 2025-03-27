/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(std::shared_ptr<IWindow> window) : _menuTitle(window, "Arcade Games", {200, 50}, 36)
{

}

void Menu::displayMenu(std::vector<Boxes> _boxes, std::vector<std::string> libs,
    std::vector<std::string> games)
{
    if (!this->_window)
        return;

    this->_window->clear();
    _menuTitle.draw();
    this->_window->display();
}

std::vector<Boxes> Menu::getBoxPoses()
{
    std::vector<Boxes> boxes;

    if (this->_window) {
        std::pair<int, int> windSize =  this->_window->getWindowSize();
        int windowWidth = windSize.first;
        int windowHeight = windSize.second;

        Boxes libBox;
        libBox.posTop = {50, 150};
        libBox.posBottom = {200, 250};
        libBox.typesBoxes = action_e::GRAPHICLIB;
        libBox.selected = false;
        libBox._nameBoxes = "Graphic Libraries";
        boxes.push_back(libBox);

        Boxes gameBox;
        gameBox.posTop = {250, 150};
        gameBox.posBottom = {400, 250};
        gameBox.typesBoxes = action_e::GAMELIB;
        gameBox.selected = false;
        gameBox._nameBoxes = "Game Libraries";
        boxes.push_back(gameBox);
    }

    return boxes;
}

std::string Menu::getUsername()
{
    return this->_username;
}

void Menu::setUsername(std::string username)
{
    this->_username = username;
}

void Menu::setMenuTitle(const std::string& title,
    const std::pair<int, int>& position, int fontSize)
{
    this->_menuTitle = MenuTitle(this->_window, title, position, fontSize);
}