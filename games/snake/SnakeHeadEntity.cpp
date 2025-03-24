/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeHeadEntity
*/

#include "SnakeHeadEntity.hpp"
#include "VoidEntity.hpp"
#include "IGameModule.hpp"
#include "SnakeGame.hpp"
#include <iostream>

SnakeHeadEntity::SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_direction = {1, 0};
    this->_spriteName = "assets/snake/head_right.png";
    this->_assetsName = {
        {{1, 0}, "assets/snake/head_right.png"},
        {{-1, 0}, "assets/snake/head_left.png"},
        {{0, 1}, "assets/snake/head_down.png"},
        {{0, -1}, "assets/snake/head_up.png"},
    };
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = true;
    this->_hasCollisions = true;
}

std::string SnakeHeadEntity::getSpriteName() const
{
    if (this->_assetsName.find(this->_direction) == this->_assetsName.end())
        return this->_spriteName;
    return this->_assetsName.at(this->_direction);
}

gameState_t SnakeHeadEntity::moveEntity(IGameModule &gameModule, std::pair<int, int> direction)
{
    if (direction.first != 0 || direction.second != 0)
        this->_direction = {direction.first, direction.second};

    grid_t grid = gameModule.getEntities();
    std::pair<size_t, size_t> gridSize = gameModule.getGridSize();
    std::pair<size_t, size_t> nextPosition = {this->_position.first + this->_direction.first, this->_position.second + this->_direction.second};

    if (nextPosition.first >= gridSize.first || nextPosition.second >= gridSize.second
        || nextPosition.first < 0 || nextPosition.second < 0)
        return gameState_t::LOSE;

    grid[nextPosition.second][nextPosition.first][1] = grid[this->_position.second][this->_position.first][1];
    grid[this->_position.second][this->_position.first][1] = std::make_shared<VoidEntity>(grid[this->_position.second][this->_position.first][0].get()->getSpriteName(), 0, "", this->_position);
    this->_position = nextPosition;
    gameModule.setEntities(grid);

    return gameState_t::PLAYING;
}
