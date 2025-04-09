/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(const std::shared_ptr<IWindow> &window) : _menuTitle(window, "Arcade Games", {590, 25}, 72),
    _libraryTitle(window, "Graphic", {215, 300}, 36), _gameTitle(window, "Game", {1285, 300}, 36),
    _showUsernameInput(false), _showHighscores(false), _saver("savefile.json")
{
    Boxes libBox;
    libBox.posTop = {50, 350};
    libBox.posBottom = {500, 650};
    libBox.typesBoxes = action_e::GRAPHICLIB;
    libBox.selected = false;
    libBox._nameBoxes = "Graphic Libraries";
    this->_boxes.push_back(libBox);

    Boxes gameBox;
    gameBox.posTop = {1100, 350};
    gameBox.posBottom = {1550, 650};
    gameBox.typesBoxes = action_e::GAMELIB;
    gameBox.selected = false;
    gameBox._nameBoxes = "Game Libraries";
    this->_boxes.push_back(gameBox);

    Boxes usernameBox;
    usernameBox.posTop = {600, 350};
    usernameBox.posBottom = {1050, 450};
    usernameBox.typesBoxes = action_e::USERNAME;
    usernameBox.selected = false;
    usernameBox._nameBoxes = "Username Input";
    this->_usernameBox = usernameBox;

    Button usernameBtn;
    usernameBtn.posTop = {725, 120};
    usernameBtn.posBottom = {900, 160};
    usernameBtn.text = "Set Username";
    usernameBtn.selected = false;
    usernameBtn.action = action_e::USERNAME;
    usernameBtn.value = "username";
    this->_usernameButtons.push_back(usernameBtn);
    this->_isWritting = false;
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
    drawUsernameButton(window);
    drawHighscores(window);

    if (_showUsernameInput) {
        window->drawSpriteMenu(
            {static_cast<float>(windowSize.first), static_cast<float>(windowSize.second)},
            "assets/background/BlurpScreen.png", {0, 0});
        drawUsernameInput(window);
    }
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
        btn.selected = (libs[i] == this->_currentGraphicLib);
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

        if (window->isMouseOver({static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {static_cast<size_t>(btn.posBottom.first - btn.posTop.first), static_cast<size_t>(btn.posBottom.second - btn.posTop.second)})) {
            btnColor = std::vector<int>{200, 200, 200};
        }
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

        if (window->isMouseOver({static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {static_cast<size_t>(btn.posBottom.first - btn.posTop.first), static_cast<size_t>(btn.posBottom.second - btn.posTop.second)})) {
            btnColor = std::vector<int>{200, 200, 200};
        }
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
    if (_showUsernameInput) {
        if (x >= _usernameBox.posTop.first + 90 && x <= _usernameBox.posTop.first + 190 &&
            y >= _usernameBox.posTop.second + 120 && y <= _usernameBox.posTop.second + 160) {

            if (!_inputUsername.empty()) {
                _username = _inputUsername;
                _inputUsername = "";
            }
            this->_isWritting = false;
            _showUsernameInput = false;
            selectedValue = _username;
            return action_e::USERNAME;
        }

        if (x >= _usernameBox.posTop.first + 240 && x <= _usernameBox.posTop.first + 350 &&
            y >= _usernameBox.posTop.second + 120 && y <= _usernameBox.posTop.second + 160) {
            _inputUsername = "";
            this->_isWritting = false;
            _showUsernameInput = false;
            return action_e::NOTHING;
        }

        if (x >= _usernameBox.posTop.first + 50 && x <= _usernameBox.posTop.first + 350 &&
            y >= _usernameBox.posTop.second + 60 && y <= _usernameBox.posTop.second + 100) {

            return action_e::USERNAME;
        }

        return action_e::NOTHING;
    }

    for (auto& btn : this->_usernameButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {
            if (btn.action == action_e::USERNAME) {
                _showUsernameInput = true;
                return action_e::USERNAME;
            }
        }
    }

    for (auto& btn : this->_graphicLibButtons) {
        if (x >= btn.posTop.first && x <= btn.posBottom.first &&
            y >= btn.posTop.second && y <= btn.posBottom.second) {

            this->_currentGraphicLib = btn.value;
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

void Menu::setSelectedGraphicLib(const std::string& graphicLib)
{
    this->_currentGraphicLib = graphicLib;
}

void Menu::drawUsernameInput(const std::shared_ptr<IWindow> &window)
{
    this->_isWritting = true;
    std::pair<size_t, size_t> boxSize = {
        static_cast<size_t>(_usernameBox.posBottom.first - _usernameBox.posTop.first),
        static_cast<size_t>(_usernameBox.posBottom.second - _usernameBox.posTop.second)
    };

    window->drawRectangleMenu(
        boxSize,
        {static_cast<size_t>(_usernameBox.posTop.first), static_cast<size_t>(_usernameBox.posTop.second)},
        {50, 50, 50}
    );

    window->drawTextMenu(
        "Enter Username",
        {_usernameBox.posTop.first + 75, _usernameBox.posTop.second + 10},
        {255, 255, 255},
        28
    );

    std::pair<size_t, size_t> inputBoxSize = {
        static_cast<size_t>(300),
        static_cast<size_t>(40)
    };

    int inputBoxX = _usernameBox.posTop.first + 75;
    int inputBoxY = _usernameBox.posTop.second + 50;

    window->drawRectangleMenu(
        inputBoxSize,
        {static_cast<size_t>(inputBoxX), static_cast<size_t>(inputBoxY)},
        {255, 255, 255}
    );

    window->drawTextMenu(
        _inputUsername,
        {inputBoxX + 10, inputBoxY + 10},
        {0, 0, 0},
        24
    );

    std::pair<size_t, size_t> buttonSize = {
        static_cast<size_t>(100),
        static_cast<size_t>(40)
    };

    window->drawRectangleMenu(
        buttonSize,
        {static_cast<size_t>(_usernameBox.posTop.first + 90), static_cast<size_t>(_usernameBox.posTop.second + 120)},
        {100, 200, 100}
    );

    window->drawTextMenu(
        "OK",
        {_usernameBox.posTop.first + 125, _usernameBox.posTop.second + 125},
        {255, 255, 255},
        24
    );

    window->drawRectangleMenu(
        buttonSize,
        {static_cast<size_t>(_usernameBox.posTop.first + 240), static_cast<size_t>(_usernameBox.posTop.second + 120)},
        {200, 100, 100}
    );

    window->drawTextMenu(
        "Cancel",
        {_usernameBox.posTop.first + 250, _usernameBox.posTop.second + 125},
        {255, 255, 255},
        24
    );
}

void Menu::drawUsernameButton(const std::shared_ptr<IWindow> &window)
{
    for (const auto& btn : this->_usernameButtons) {
        std::vector<int> btnColor = std::vector<int>{150, 150, 150};

        if (btn.action == action_e::USERNAME && _showUsernameInput) {
            btnColor = std::vector<int>{100, 200, 100};
        }

        std::pair<size_t, size_t> btnSize = {
            static_cast<size_t>(btn.posBottom.first - btn.posTop.first),
            static_cast<size_t>(btn.posBottom.second - btn.posTop.second)
        };

        if (window->isMouseOver({static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {static_cast<size_t>(btn.posBottom.first - btn.posTop.first), static_cast<size_t>(btn.posBottom.second - btn.posTop.second)})) {
            btnColor = std::vector<int>{200, 200, 200};
        }

        window->drawRectangleMenu(
            btnSize,
            {static_cast<size_t>(btn.posTop.first), static_cast<size_t>(btn.posTop.second)},
            {btnColor[0], btnColor[1], btnColor[2]}
        );

        int textWidth = estimateTextWidth(btn.text, 24);
        int textX = btn.posTop.first + (btn.posBottom.first - btn.posTop.first) / 2 - textWidth / 2;
        int textY = (btn.posTop.second + btn.posBottom.second) / 2 - 12;

        window->drawTextMenu(
            btn.text,
            {textX, textY},
            {255, 255, 255},
            24
        );
    }

    if (!_username.empty()) {
        window->drawTextMenu(
            _username,
            {1300, 50},
            {253,176,42},
            28
        );
    }
}

void Menu::drawHighscores(const std::shared_ptr<IWindow> &window)
{
    int scoreX = 600;
    int scoreY = 250;
    int width = 450;
    int height = 400;

    window->drawRectangleMenu(
        {static_cast<size_t>(width), static_cast<size_t>(height)},
        {static_cast<size_t>(scoreX), static_cast<size_t>(scoreY)},
        {50, 50, 60}
    );

    window->drawTextMenu(
        "High Scores",
        {scoreX + 70, scoreY + 20},
        {255, 255, 255},
        28
    );

    window->drawRectangleMenu(
        {static_cast<size_t>(width - 20), static_cast<size_t>(2)},
        {static_cast<size_t>(scoreX + 10), static_cast<size_t>(scoreY + 50)},
        {200, 200, 200}
    );

    int y = scoreY + 70;

    for (const auto& gameBtn : _gameButtons) {
        std::string gameName = gameBtn.text;

        std::pair<std::string, int> highScoreData = _saver.getHighScore(gameName);
        std::string highScoreUser = highScoreData.first;
        int score = highScoreData.second;

        window->drawTextMenu(
            extractNameFromPath(gameName),
            {scoreX + 20, y},
            {200, 200, 255},
            16
        );

        window->drawTextMenu(
            std::to_string(score),
            {scoreX + 180, y},
            {255, 200, 100},
            16
        );

        window->drawTextMenu(
            "By        " + (highScoreUser.empty() ? "noname" : highScoreUser),
            {scoreX + 250, y},
            {100, 255, 100},
            16
        );

        y += 30;
    }
}

void Menu::setInputUsername(const std::string& input) {
    _inputUsername = input;
}

bool Menu::getIsWritting()
{
    return _isWritting;
}
