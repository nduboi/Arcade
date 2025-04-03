/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(const std::shared_ptr<IWindow> &window) : _menuTitle(window, "Arcade Games", {575, 25}, 72),
    _libraryTitle(window, "Graphic", {400, 200}, 36), _gameTitle(window, "Game", {1125, 200}, 36)
{
    Boxes libBox;
    libBox.posTop = {250, 250};
    libBox.posBottom = {700, 550};
    libBox.typesBoxes = action_e::GRAPHICLIB;
    libBox.selected = false;
    libBox._nameBoxes = "Graphic Libraries";
    this->_boxes.push_back(libBox);

    Boxes gameBox;
    gameBox.posTop = {950, 250};
    gameBox.posBottom = {1400, 550};
    gameBox.typesBoxes = action_e::GAMELIB;
    gameBox.selected = false;
    gameBox._nameBoxes = "Game Libraries";
    this->_boxes.push_back(gameBox);
}

void Menu::displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes,
    std::vector<std::string> libs, std::vector<std::string> games)
{
    if (!window)
        return;

    if (this->_graphicLibButtons.empty() || this->_gameButtons.empty()) {
        initButtons(libs, games);
    }

    std::pair<int, int> windowSize = window->getWindowSize();

    window->drawSpriteMenu(
        {static_cast<float>(windowSize.first), static_cast<float>(windowSize.second)},
        "assets/background/background_menu.jpg", {0, 0});

    this->_menuTitle.draw(window);
    this->_libraryTitle.draw(window);
    this->_gameTitle.draw(window);

    std::vector<Boxes> boxes = getBoxPoses();

    for (const auto& box : boxes) {
        std::vector<int> boxColor;

        if (box.typesBoxes == action_e::GRAPHICLIB) {
            boxColor = box.selected ? std::vector<int>{50, 150, 250} : std::vector<int>{100, 100, 250};
        } else if (box.typesBoxes == action_e::GAMELIB) {
            boxColor = box.selected ? std::vector<int>{250, 150, 50} : std::vector<int>{250, 100, 100};
        } else {
            boxColor = std::vector<int>{200, 200, 200};
        }

        std::pair<size_t, size_t> boxSize = {
            static_cast<size_t>(box.posBottom.first - box.posTop.first),
            static_cast<size_t>(box.posBottom.second - box.posTop.second)
        };

        window->drawRectangleMenu(
            boxSize,
            {static_cast<size_t>(box.posTop.first), static_cast<size_t>(box.posTop.second)},
            {boxColor[0], boxColor[1], boxColor[2]}
        );
    }
    drawButtons(window);
}

std::vector<Boxes> Menu::getBoxPoses()
{
    return this->_boxes;
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
    this->_graphicLibButtons.clear();
    this->_gameButtons.clear();

    std::vector<Boxes> boxes = getBoxPoses();

    const int buttonWidth = 430;
    const int buttonHeight = 50;
    const int spacing = 15;

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

        this->_graphicLibButtons.push_back(btn);
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

        this->_gameButtons.push_back(btn);
    }

    int totalHeightLibs = (buttonHeight + spacing) * libs.size();
    int totalHeightGames = (buttonHeight + spacing) * games.size();

    for (auto &box : _boxes) {
        if (box.typesBoxes == action_e::GRAPHICLIB)
            box.posBottom.second = box.posTop.second + totalHeightLibs + 20;
        else if (box.typesBoxes == action_e::GAMELIB)
            box.posBottom.second = box.posTop.second + totalHeightGames + 20;
    }
}

std::string Menu::extractNameFromPath(const std::string& path)
{
    size_t arcadePos = path.find("lib/");
    size_t soPos = path.find(".so");

    if (arcadePos != std::string::npos && soPos != std::string::npos) {
        size_t start = arcadePos + 11;
        return path.substr(start, soPos - start);
    } else {
        size_t lastSlash = path.find_last_of("/");
        if (lastSlash != std::string::npos && soPos != std::string::npos) {
            return path.substr(lastSlash + 1, soPos - (lastSlash + 1));
        }
    }

    return path;
}

int Menu::estimateTextWidth(const std::string& text, int fontSize)
{
    return text.length() * (fontSize / 2);
}

void Menu::drawButtons(const std::shared_ptr<IWindow> &window)
{
    for (const auto& btn : this->_graphicLibButtons) {
        std::vector<int> btnColor = (btn.value == this->_currentGraphicLib) ?
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

        std::string displayName = extractNameFromPath(btn.text);
        int textWidth = estimateTextWidth(displayName, 24);
        int textX = btn.posTop.first + (btn.posBottom.first - btn.posTop.first) / 2 - textWidth / 2;
        int textY = (btn.posTop.second + btn.posBottom.second) / 2 - 12;

        window->drawTextMenu(
            displayName,
            {textX, textY},
            {255, 255, 255},
            24
        );

    }

    for (const auto& btn : _gameButtons) {
        std::vector<int> btnColor = std::vector<int>{150, 150, 150};

        std::pair<size_t, size_t> btnSize = {
            static_cast<size_t>(btn.posBottom.first - btn.posTop.first),
            static_cast<size_t>(btn.posBottom.second - btn.posTop.second)
        };

        window->drawRectangleMenu(
            btnSize,
            {static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {btnColor[0], btnColor[1], btnColor[2]}
        );

        std::string displayName = extractNameFromPath(btn.text);
        int textWidth = estimateTextWidth(displayName, 24);
        int textX = btn.posTop.first + (btn.posBottom.first - btn.posTop.first) / 2 - textWidth / 2;
        int textY = (btn.posTop.second + btn.posBottom.second) / 2 - 12;

        window->drawTextMenu(
            displayName,
            {textX, textY},
            {255, 255, 255},
            24
        );

    }
}

action_e Menu::handleClick(int x, int y, std::string& selectedValue)
{
    for (auto& btn : this->_graphicLibButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {

            _currentGraphicLib = btn.value;
            selectedValue = btn.value;
            return btn.action;
        }
    }

    for (auto& btn : this->_gameButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {

            selectedValue = btn.value;
            return btn.action;
        }
    }

    selectedValue = "";
    return action_e::NOTHING;
}
