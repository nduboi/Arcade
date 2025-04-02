/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(const std::shared_ptr<IWindow> &window) : _menuTitle(window, "Arcade Games", {170, 25}, 72),
    _libraryTitle(window, "Graphic", {100, 175}, 36), _gameTitle(window, "Game", {600, 175}, 36)
{

}

void Menu::displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes,
    std::vector<std::string> libs, std::vector<std::string> games)
{
    if (!window)
        return;

    std::pair<int, int> windowSize = window->getWindowSize();

    window->drawSpriteMenu(
        {static_cast<float>(windowSize.first), static_cast<float>(windowSize.second)},
        "assets/background/background_menu.jpg", {0, 0});

    _menuTitle.draw(window);
    _libraryTitle.draw(window);
    _gameTitle.draw(window);

    std::vector<Boxes> boxes = getBoxPoses();

    for (const auto& box : boxes) {
        std::cout << "je suis ici" << std::endl;
        std::vector<int> boxColor = box.selected ?
            std::vector<int>{100, 200, 100} :
            std::vector<int>{200, 200, 200};

        std::pair<size_t, size_t> boxSize = {
            static_cast<size_t>(box.posBottom.first - box.posTop.first),
            static_cast<size_t>(box.posBottom.second - box.posTop.second)
        };

        window->drawRectangleMenu(
            boxSize,
            {static_cast<size_t>(box.posTop.first), static_cast<size_t>(box.posTop.second)},
            {boxColor[0], boxColor[1], boxColor[2]}
        );

        window->drawTextMenu(
            box._nameBoxes, {(box.posTop.first + box.posBottom.first) / 2 - box._nameBoxes.length() * 5,
            box.posBottom.second + 10}, {255, 255, 255}, 20);
    }
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