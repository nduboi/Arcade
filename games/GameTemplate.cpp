/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** GameTemplate
*/

#include "GameTemplate.hpp"

std::size_t GameTemplate::getHighScore() const
{
    return this->_highScore;
}

void GameTemplate::setHighScore(std::size_t highScore)
{
    this->_highScore = highScore;
}

std::size_t GameTemplate::getScore() const
{
    return this->_score;
}

void GameTemplate::setScore(std::size_t score)
{
    this->_score = score;
}

grid_t GameTemplate::getEntities() const
{
    return this->_entities;
}

void GameTemplate::setEntities(grid_t entities)
{
    this->_entities = entities;
}

std::pair<size_t, size_t> GameTemplate::getGridSize() const
{
    grid_t grid = this->_entities;

    return std::make_pair(grid.size(), grid[0].size());
}

bool GameTemplate::getIsStarted() const
{
    return this->_isStarted;
}

void GameTemplate::setIsStarted(bool isStarted)
{
    this->_isStarted = isStarted;
}

gameState_t GameTemplate::getGameState() const
{
    return this->_gameState;
}

void GameTemplate::setGameState(gameState_t gameState)
{
    this->_gameState = gameState;
}

std::vector<std::shared_ptr<IEntity>> GameTemplate::getHUD() const
{
    return {};
}

size_t GameTemplate::getTime() const
{
    return this->_time;
}

void GameTemplate::setTime(size_t time)
{
    this->_time = time;
}
