/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"
#include "VoidEntity.hpp"
#include "WallEntity.hpp"
#include "PacmanEntity.hpp"
#include "DotEntity.hpp"
#include "BigDotEntity.hpp"

#include "ScoreEntityHUD.hpp"
#include "HighScoreEntityHUD.hpp"
#include "TimeEntityHUD.hpp"
#include "TextEntityHUD.hpp"
#include "BigTextEntityHUD.hpp"

#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "OrangeGhost.hpp"
#include "CyanGhost.hpp"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 25;
const int MAP_LAYER = 3;

const std::map<std::string, std::string> ASSETS = {
    {"a", "assets/pacman/walls/topleftdouble.png"},
    {"b", "assets/pacman/walls/tophorizontal.png"},
    {"c", "assets/pacman/walls/jointopright.png"},
    {"d", "assets/pacman/walls/jointopleft.png"},
    {"e", "assets/pacman/walls/topbar.png"},
    {"f", "assets/pacman/walls/toprightdouble.png"},
    {"g", "assets/pacman/walls/leftvertical.png"},
    {"h", "assets/pacman/walls/leftverticalsimple.png"},
    {"i", "assets/pacman/walls/rightverticalsimple.png"},
    {"j", "assets/pacman/walls/rightvertical.png"},
    {"k", "assets/pacman/walls/botleftround.png"},
    {"l", "assets/pacman/walls/tophorizontalsimple.png"},
    {"m", "assets/pacman/walls/botrightround.png"},
    {"n", "assets/pacman/walls/toprightround.png"},
    {"o", "assets/pacman/walls/topleftround.png"},
    {"p", "assets/pacman/walls/bothorizontalsimple.png"},
    {"q", "assets/pacman/walls/botleftdouble.png"},
    {"r", "assets/pacman/walls/bothorizontal.png"},
    {"s", "assets/pacman/walls/toprightdot.png"},
    {"t", "assets/pacman/walls/topleftdot.png"},
    {"u", "assets/pacman/walls/botrightdouble.png"},
    {"v", "assets/pacman/walls/botrightdot.png"},
    {"w", "assets/pacman/walls/barrier.png"},
    {"x", "assets/pacman/walls/botleftdot.png"},
    {"y", "assets/pacman/walls/joinbotright.png"},
    {"z", "assets/pacman/walls/joinbotleft.png"},
    {"A", "assets/pacman/walls/botbar.png"},
    {"B", "assets/pacman/walls/shorttopleft.png"},
    {"C", "assets/pacman/walls/shorttopright.png"},
    {"D", "assets/pacman/walls/shortbotleft.png"},
    {"E", "assets/pacman/walls/shortbotright.png"},
};

const std::vector<std::vector<std::string>> MAP = {
    {"a", "b", "b", "b", "b", "b", "b", "c", "d", "b", "c", "e", "e", "e", "d", "b", "c", "d", "b", "b", "b", "b", "b", "b", "f"},
    {"g", " ", " ", " ", " ", " ", " ", "i", "h", " ", "i", " ", " ", " ", "h", " ", "i", "h", " ", " ", " ", " ", " ", " ", "j"},
    {"g", " ", "k", "l", "l", "m", " ", "i", "h", " ", "C", "p", "p", "p", "B", " ", "i", "h", " ", "k", "l", "l", "m", " ", "j"},
    {"g", " ", "h", " ", " ", "i", " ", "C", "B", " ", " ", " ", " ", " ", " ", " ", "C", "B", " ", "h", " ", " ", "i", " ", "j"},
    {"g", " ", "h", " ", " ", "i", " ", " ", " ", " ", "k", "l", "l", "l", "m", " ", " ", " ", " ", "h", " ", " ", "i", " ", "j"},
    {"g", " ", "n", "p", "p", "o", " ", "k", "m", " ", "n", "D", " ", "E", "o", " ", "k", "m", " ", "n", "p", "p", "o", " ", "j"},
    {"g", " ", " ", " ", " ", " ", " ", "h", "i", " ", " ", "h", " ", "i", " ", " ", "h", "i", " ", " ", " ", " ", " ", " ", "j"},
    {"q", "r", "r", "r", "r", "s", " ", "h", "C", "m", " ", "h", " ", "i", " ", "k", "B", "i", " ", "t", "r", "r", "r", "r", "u"},
    {" ", " ", " ", " ", " ", "g", " ", "h", "E", "o", " ", "n", "p", "o", " ", "n", "D", "i", " ", "j", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", "g", " ", "h", "i", " ", " ", " ", " ", " ", " ", " ", "h", "i", " ", "j", " ", " ", " ", " ", " "},
    {"b", "b", "b", "b", "b", "v", " ", "n", "o", " ", "t", "r", "w", "r", "s", " ", "n", "o", " ", "x", "b", "b", "b", "b", "b"},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "j", " ", " ", " ", "g", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {"r", "r", "r", "r", "r", "s", " ", "k", "m", " ", "j", " ", " ", " ", "g", " ", "k", "m", " ", "t", "r", "r", "r", "r", "r"},
    {" ", " ", " ", " ", " ", "g", " ", "h", "i", " ", "x", "b", "b", "b", "v", " ", "h", "i", " ", "j", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", "g", " ", "h", "i", " ", " ", " ", " ", " ", " ", " ", "h", "i", " ", "j", " ", " ", " ", " ", " "},
    {"a", "b", "b", "b", "b", "v", " ", "h", "C", "m", " ", "k", "l", "m", " ", "k", "B", "i", " ", "x", "b", "b", "b", "b", "f"},
    {"g", " ", " ", " ", " ", " ", " ", "h", "E", "o", " ", "h", " ", "i", " ", "n", "D", "i", " ", " ", " ", " ", " ", " ", "j"},
    {"g", " ", "k", "l", "l", "m", " ", "h", "i", " ", " ", "h", " ", "i", " ", " ", "h", "i", " ", "k", "l", "l", "m", " ", "j"},
    {"g", " ", "h", " ", " ", "i", " ", "n", "o", " ", "k", "B", " ", "C", "m", " ", "n", "o", " ", "h", " ", " ", "i", " ", "j"},
    {"g", " ", "h", " ", " ", "i", " ", " ", " ", " ", "n", "p", "p", "p", "o", " ", " ", " ", " ", "h", " ", " ", "i", " ", "j"},
    {"g", " ", "n", "p", "p", "o", " ", "E", "D", " ", " ", " ", " ", " ", " ", " ", "E", "D", " ", "n", "p", "p", "o", " ", "j"},
    {"g", " ", " ", " ", " ", " ", " ", "i", "h", " ", "E", "l", "l", "l", "D", " ", "i", "h", " ", " ", " ", " ", " ", " ", "j"},
    {"q", "r", "r", "r", "r", "r", "r", "y", "z", "r", "y", "A", "A", "A", "z", "r", "y", "z", "r", "r", "r", "r", "r", "r", "u"},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
};

const std::vector<std::vector<std::string>> DOTS = {
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {" ", "b", "d", "d", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", "d", "d", "b", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", "d", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", "d", "d", "d", " ", " ", " ", " ", " ", "d", "d", "d", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", "d", "d", "d", "d", "d", " ", " ", "d", "d", " ", " ", " ", "d", "d", " ", " ", "d", "d", "d", "d", "d", "d", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", "d", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {"d", "d", "d", "d", "d", "d", "d", "d", "d", "d", " ", "R", " ", "O", " ", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d"},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", "P", " ", "C", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", " ", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", " ", " ", " "},
    {" ", "d", "d", "d", "d", "d", "d", " ", " ", " ", "d", " ", " ", " ", "d", " ", " ", " ", "d", "d", "d", "d", "d", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", "d", " ", " ", " ", "d", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", "d", "d", "d", " ", " ", " ", " ", " ", "d", "d", "d", "d", " ", " ", " ", " ", "d", " "},
    {" ", "d", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", "d", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", "d", " "},
    {" ", "b", "d", "d", "d", "d", "d", " ", " ", "d", " ", " ", " ", " ", " ", "d", " ", " ", "d", "d", "d", "d", "d", "b", " "},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
};

PacmanGame::PacmanGame()
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->_multiplier = 1.0f;
    this->_round = 1;

    this->_entities.resize(MAP_HEIGHT);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        this->_entities[y].resize(MAP_WIDTH);
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x].resize(MAP_LAYER);
        }
    }
    this->setLayerBackground();
    this->setLayerEntities();
}

void PacmanGame::setLayerBackground()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/pacman/walls/void.png", 0, "", std::make_pair(x, y));
        }
    }
}

void PacmanGame::setLayerEntities()
{
    // Background
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x][1] = std::make_shared<VoidEntity>("assets/pacman/walls/void.png", 0, "", std::make_pair(x, y));
            this->_entities[y][x][2] = nullptr;
        }
    }

    // Walls
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (MAP[y][x] == "" || MAP[y][x] == " ")
                continue;

            if (ASSETS.find(MAP[y][x]) != ASSETS.end())
                this->_entities[y][x][1] = std::make_shared<WallEntity>(ASSETS.at(MAP[y][x]), 1, "", std::make_pair(x, y));
        }
    }

    // Player
    this->_entities[14][12][1] = std::make_shared<PacmanEntity>(4, "", std::make_pair(12, 14));

    // Pacgums and Ghosts
    this->setLayerInteract();
}

void PacmanGame::setLayerInteract()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (DOTS[y][x] == "" || DOTS[y][x] == " ")
                continue;

            if (DOTS[y][x] == "d")
                this->_entities[y][x][1] = std::make_shared<DotEntity>(std::make_pair(x, y));
            if (DOTS[y][x] == "b")
                this->_entities[y][x][1] = std::make_shared<BigDotEntity>(std::make_pair(x, y));
            if (DOTS[y][x] == "R")
                this->_entities[y][x][2] = std::make_shared<RedGhost>(std::make_pair(x, y), this->_entities[14][12][1], _multiplier);
            if (DOTS[y][x] == "P")
                this->_entities[y][x][2] = std::make_shared<PinkGhost>(std::make_pair(x, y), this->_entities[14][12][1], _multiplier);
            if (DOTS[y][x] == "O")
                this->_entities[y][x][2] = std::make_shared<OrangeGhost>(std::make_pair(x, y), this->_entities[14][12][1], _multiplier);
            if (DOTS[y][x] == "C")
                this->_entities[y][x][2] = std::make_shared<CyanGhost>(std::make_pair(x, y), this->_entities[14][12][1], _multiplier);
        }
    }
}

void PacmanGame::update(std::shared_ptr<IGameModule> gameModule)
{
    if (this->getIsStarted() == false) {
        grid_t grid = gameModule->getEntities();
        std::pair<size_t, size_t> pos = gameModule->getGridSize();

        for (int y = 0; y < pos.second; y++) {
            for (int x = 0; x < pos.first; x++) {
                if (grid[y][x][2] == nullptr)
                    continue;

                auto entity = grid[y][x][2];
                GhostEntity *ghost = dynamic_cast<GhostEntity *>(entity.get());

                if (ghost != nullptr)
                    ghost->setWaitingTime(ghost->getWaitingTime());
            }
        }
    }

    bool hasWon = true;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (hasWon == false)
            break;

        for (int x = 0; x < MAP_WIDTH; x++) {
            if (hasWon == false)
                break;

            if (this->_entities[y][x][1] == nullptr)
                continue;
            if (std::dynamic_pointer_cast<DotEntity>(this->_entities[y][x][1]) != nullptr)
                hasWon = false;
        }
    }
    if (hasWon)
        this->resetGame(gameModule);
}

std::vector<std::shared_ptr<IEntity>> PacmanGame::getHUD() const
{
    std::vector<std::shared_ptr<IEntity>> hud;

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore(), std::make_pair(10, 15)));
    hud.push_back(std::make_shared<HighScoreEntityHUD>(this->getHighScore(), std::make_pair(10, 55)));

    std::size_t secondsElapsed = this->getTime();
    hud.push_back(std::make_shared<TimeEntityHUD>(secondsElapsed, std::make_pair(350, 35)));

    std::string roundString = std::to_string(this->_round);
    while (roundString.length() < 2)
        roundString = "0" + roundString;
    hud.push_back(std::make_shared<TextEntityHUD>("Round " + roundString, std::make_pair(675, 35)));

    if (this->getIsStarted() == false)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Press any direction to start", std::make_pair(250, 850)));
    if (this->getGameState() == LOSE)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Game Over", std::make_pair(350, 850)));
    if (this->getGameState() == WIN)
        hud.push_back(std::make_shared<BigTextEntityHUD>("You Win", std::make_pair(350, 850)));
    return hud;
}

void PacmanGame::resetGame(std::shared_ptr<IGameModule> gameModule)
{
    this->_gameState = PLAYING;
    this->_multiplier -= 0.1f;
    if (this->_multiplier < 0.1f)
        this->_multiplier = 0.1f;
    this->_round++;

    this->setLayerEntities();
}
