/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(const std::shared_ptr<IWindow> &window) : _menuTitle(window, "Arcade Games", {575, 25}, 72),
    _libraryTitle(window, "Graphic", {400, 200}, 36), _gameTitle(window, "Game", {1100, 200}, 36)
{
    Boxes libBox;
    libBox.posTop = {50, 150};
    libBox.posBottom = {200, 250};
    libBox.typesBoxes = action_e::GRAPHICLIB;
    libBox.selected = false;
    libBox._nameBoxes = "Graphic Libraries";
    _boxes.push_back(libBox);

    Boxes gameBox;
    gameBox.posTop = {250, 150};
    gameBox.posBottom = {400, 250};
    gameBox.typesBoxes = action_e::GAMELIB;
    gameBox.selected = false;
    gameBox._nameBoxes = "Game Libraries";
    _boxes.push_back(gameBox);
}

void Menu::displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes,
    std::vector<std::string> libs, std::vector<std::string> games)
{
    if (!window)
        return;

    if (_graphicLibButtons.empty() || _gameButtons.empty()) {
        initButtons(libs, games);
    }

    std::pair<int, int> windowSize = window->getWindowSize();

    window->drawSpriteMenu(
        {static_cast<float>(windowSize.first), static_cast<float>(windowSize.second)},
        "assets/background/background_menu.jpg", {0, 0});

    _menuTitle.draw(window);
    _libraryTitle.draw(window);
    _gameTitle.draw(window);

    std::vector<Boxes> boxes = getBoxPoses();

    for (const auto& box : boxes) {
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
    drawButtons(window);
}

std::vector<Boxes> Menu::getBoxPoses()
{
    return _boxes;
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

void Menu::initButtons(const std::vector<std::string>& libs, const std::vector<std::string>& games)
{
    _graphicLibButtons.clear();
    _gameButtons.clear();

    std::vector<Boxes> boxes = getBoxPoses();

    const int buttonWidth = 130;
    const int buttonHeight = 30;
    const int spacing = 10;

    Boxes libBox;
    Boxes gameBox;

    for (const auto& box : boxes) {
        if (box.typesBoxes == action_e::GRAPHICLIB)
            libBox = box;
        else if (box.typesBoxes == action_e::GAMELIB)
            gameBox = box;
    }

    int startX = libBox.posTop.first + 10;
    int startY = libBox.posTop.second + 10;

    for (size_t i = 0; i < libs.size(); ++i) {
        Button btn;
        btn.posTop = {startX, startY + i * (buttonHeight + spacing)};
        btn.posBottom = {startX + buttonWidth, startY + i * (buttonHeight + spacing) + buttonHeight};
        btn.text = libs[i];
        btn.selected = (i == 0);
        btn.action = action_e::GRAPHICLIB;
        btn.value = libs[i];

        _graphicLibButtons.push_back(btn);
    }

    startX = gameBox.posTop.first + 10;
    startY = gameBox.posTop.second + 10;

    for (size_t i = 0; i < games.size(); ++i) {
        Button btn;
        btn.posTop = {startX, startY + i * (buttonHeight + spacing)};
        btn.posBottom = {startX + buttonWidth, startY + i * (buttonHeight + spacing) + buttonHeight};
        btn.text = games[i];
        btn.selected = (i == 0);
        btn.action = action_e::GAMELIB;
        btn.value = games[i];

        _gameButtons.push_back(btn);
    }
}

void Menu::drawButtons(const std::shared_ptr<IWindow> &window)
{
    for (const auto& btn : _graphicLibButtons) {
        std::vector<int> btnColor = btn.selected ?
            std::vector<int>{100, 200, 100} :
            std::vector<int>{150, 150, 150};

        std::pair<size_t, size_t> btnSize = {
            static_cast<size_t>(btn.posBottom.first - btn.posTop.first),
            static_cast<size_t>(btn.posBottom.second - btn.posTop.second)
        };

        window->drawRectangleMenu(
            btnSize,
            {static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {btnColor[0], btnColor[1], btnColor[2]}
        );

        window->drawTextMenu(
            btn.text,
            {btn.posTop.first + 10,
             (btn.posTop.second + btn.posBottom.second) / 2 - 5},
            {255, 255, 255},
            14
        );
    }

    for (const auto& btn : _gameButtons) {
        std::vector<int> btnColor = btn.selected ?
            std::vector<int>{100, 200, 100} :
            std::vector<int>{150, 150, 150};

        std::pair<size_t, size_t> btnSize = {
            static_cast<size_t>(btn.posBottom.first - btn.posTop.first),
            static_cast<size_t>(btn.posBottom.second - btn.posTop.second)
        };

        window->drawRectangleMenu(
            btnSize,
            {static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {btnColor[0], btnColor[1], btnColor[2]}
        );

        window->drawTextMenu(
            btn.text,
            {btn.posTop.first + 10,
             (btn.posTop.second + btn.posBottom.second) / 2 - 5},
            {255, 255, 255},
            14
        );
    }
}

action_e Menu::handleClick(int x, int y, std::string& selectedValue)
{
    for (auto& btn : _graphicLibButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {

            for (auto& b : _graphicLibButtons) {
                b.selected = false;
            }

            btn.selected = true;
            selectedValue = btn.value;
            return btn.action;
        }
    }

    for (auto& btn : _gameButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {

            for (auto& b : _gameButtons) {
                b.selected = false;
            }

            btn.selected = true;
            selectedValue = btn.value;
            return btn.action;
        }
    }

    selectedValue = "";
    return action_e::NOTHING;
}
