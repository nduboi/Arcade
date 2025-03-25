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
