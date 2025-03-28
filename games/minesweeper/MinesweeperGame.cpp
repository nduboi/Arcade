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

MinesweeperGame::MinesweeperGame(size_t width, size_t height)
{
    this->_width = width;
    this->_height = height;
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();

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
    hud.push_back(std::make_shared<TimerEntityHUD>(secondsElapsed, 100, std::make_pair(300, 35)));

    std::string difficulty = "Difficulty: ";
    if (this->_width == 9 && this->_height == 9)
        difficulty += "Easy";
    else if (this->_width == 16 && this->_height == 16)
        difficulty += "Medium";
    else
        difficulty += "Hard";
    hud.push_back(std::make_shared<TextEntityHUD>(difficulty, std::make_pair(600, 35)));
    return hud;
}
