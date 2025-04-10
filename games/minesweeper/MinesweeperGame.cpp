/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MinesweeperGame
*/

#include "MinesweeperGame.hpp"
#include "Cell.hpp"
#include "ScoreEntityHUD.hpp"
#include "HighScoreEntityHUD.hpp"
#include "TimerEntityHUD.hpp"
#include "TextEntityHUD.hpp"
#include "BigTextEntityHUD.hpp"

MinesweeperGame::MinesweeperGame(size_t width, size_t height)
{
    this->_width = width;
    this->_height = height;
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->_nbMines = this->getNbMines();

    initializeGrid();
}

void MinesweeperGame::initializeGrid()
{
    _entities.resize(this->_height);
    for (size_t y = 0; y < this->_height; ++y) {
        _entities[y].resize(this->_width);
        for (size_t x = 0; x < this->_width; ++x) {
            _entities[y][x].resize(1);
            _entities[y][x][0] = std::make_shared<Cell>(x, y);
        }
    }
}

std::vector<std::shared_ptr<IEntity>> MinesweeperGame::getHUD() const
{
    std::vector<std::shared_ptr<IEntity>> hud;

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore(), std::make_pair(10, 15)));
    hud.push_back(std::make_shared<HighScoreEntityHUD>(this->getHighScore(), std::make_pair(10, 55)));

    std::size_t secondsElapsed = this->getTime();

    std::string difficulty = "Difficulty: ";
    if (this->_width == 9 && this->_height == 9) {
        difficulty += "Easy";
        hud.push_back(std::make_shared<TimerEntityHUD>(secondsElapsed, 120, std::make_pair(300, 35)));
    }
    else if (this->_width == 16 && this->_height == 16) {
        difficulty += "Medium";
        hud.push_back(std::make_shared<TimerEntityHUD>(secondsElapsed, 360, std::make_pair(300, 35)));
    }
    else {
        difficulty += "Hard";
        hud.push_back(std::make_shared<TimerEntityHUD>(secondsElapsed, 720, std::make_pair(300, 35)));
    }
    hud.push_back(std::make_shared<TextEntityHUD>(difficulty, std::make_pair(600, 55)));

    hud.push_back(std::make_shared<TextEntityHUD>("Mines: " + std::to_string(this->_nbMines - this->getNbFlags()), std::make_pair(600, 15)));

    if (this->getIsStarted() == false)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Click on any cell to start", std::make_pair(250, 850)));
    if (this->getGameState() == LOSE)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Game Over", std::make_pair(350, 850)));
    if (this->getGameState() == WIN)
        hud.push_back(std::make_shared<BigTextEntityHUD>("You Win", std::make_pair(350, 850)));
    return hud;
}

void MinesweeperGame::changeDifficulty()
{
    if (this->_width == 9 && this->_height == 9) {
        this->_width = 16;
        this->_height = 16;
    } else if (this->_width == 16 && this->_height == 16) {
        this->_width = 30;
        this->_height = 30;
    } else {
        this->_width = 9;
        this->_height = 9;
    }
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->initializeGrid();
    this->_nbMines = this->getNbMines();
}

void MinesweeperGame::update(std::shared_ptr<IGameModule> gameModule)
{
    if (this->_isStarted == false)
        return;
    if (this->_gameState != PLAYING)
        return;

    std::size_t secondsElapsed = this->getTime();
    if (this->_width == 9 && this->_height == 9 && secondsElapsed >= 120) {
        this->_gameState = LOSE;
    } else if (this->_width == 16 && this->_height == 16 && secondsElapsed >= 360) {
        this->_gameState = LOSE;
    } else if (secondsElapsed >= 720) {
        this->_gameState = LOSE;
    }
}

int MinesweeperGame::getNbMines() const
{
    if (this->_width == 9 && this->_height == 9)
        return 10;
    if (this->_width == 16 && this->_height == 16)
        return 40;
    if (this->_width == 30 && this->_height == 30)
        return 150;
    return static_cast<int>(this->_width * this->_height * 0.15);
}

int MinesweeperGame::getNbFlags() const
{
    int flags = 0;

    for (size_t y = 0; y < this->_height; ++y) {
        for (size_t x = 0; x < this->_width; ++x) {
            auto cell = std::dynamic_pointer_cast<Cell>(this->_entities[y][x][0]);
            if (cell->isFlagged())
                flags++;
        }
    }
    return flags;
}
