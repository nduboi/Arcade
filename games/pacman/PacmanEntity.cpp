/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PacmanEntity
*/

#include "PacmanEntity.hpp"
#include "VoidEntity.hpp"
#include "IGameModule.hpp"
#include "PacmanGame.hpp"
#include "DotEntity.hpp"
#include "WallEntity.hpp"

#include <iostream>

PacmanEntity::PacmanEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_inputDirection = {1, 0};
    this->_direction = {1, 0};
    this->_spriteName = "assets/pacman/pacman-right/1.png";
    this->_assetsName = {
        {{1, 0}, "assets/pacman/pacman-right/1.png"},
        {{-1, 0}, "assets/pacman/pacman-left/1.png"},
        {{0, 1}, "assets/pacman/pacman-down/1.png"},
        {{0, -1}, "assets/pacman/pacman-up/1.png"},
    };
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = true;
    this->_hasCollisions = true;
    this->_lastTime = std::chrono::steady_clock::now();
    this->_lastAnimation = std::chrono::steady_clock::now();
    this->_speedTime = 0.15f;
}

bool PacmanEntity::isWall(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    grid_t grid = gameModule->getEntities();

    if (newPos.first < 0 || newPos.second < 0
        || newPos.first >= gameModule->getGridSize().first
        || newPos.second >= gameModule->getGridSize().second)
        return true;
    if (std::dynamic_pointer_cast<WallEntity>(grid[newPos.second][newPos.first][1]))
        return true;
    return false;
}

void PacmanEntity::setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule)
{
    if (direction.first == 0 && direction.second == 0)
        return;

    if (direction.first == 0 && direction.second == -1) {
        if (isWall(gameModule, {this->_position.first, this->_position.second - 1}))
            return;
    }
    if (direction.first == 0 && direction.second == 1) {
        if (isWall(gameModule, {this->_position.first, this->_position.second + 1}))
            return;
    }
    if (direction.first == -1 && direction.second == 0) {
        if (isWall(gameModule, {this->_position.first - 1, this->_position.second}))
            return;
    }
    if (direction.first == 1 && direction.second == 0) {
        if (isWall(gameModule, {this->_position.first + 1, this->_position.second}))
            return;
    }
    gameModule->setIsStarted(true);
    this->_inputDirection = direction;
}

bool PacmanEntity::lastTimePassed()
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_lastTime;
    if (elapsedTime.count() < this->_speedTime)
        return false;

    this->_lastTime = currentTime;
    return true;
}

void PacmanEntity::actualiseAnimation()
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_lastAnimation;
    if (elapsedTime.count() < 0.1f)
        return;

    this->_lastAnimation = currentTime;
    this->_animationIndex++;
    if (this->_animationIndex > 3)
        this->_animationIndex = 1;
}

std::string PacmanEntity::getSpriteName() const
{
    if (this->_assetsName.find(this->_direction) == this->_assetsName.end())
        return this->_spriteName;
    std::string spriteName = this->_assetsName.at(this->_direction);
    return spriteName.substr(0, spriteName.find_last_of('/')) + "/" + std::to_string(this->_animationIndex) + ".png";
}

void PacmanEntity::moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2)
{
    grid_t grid = gameModule->getEntities();

    if (pos2.first == -1 && pos2.second == 11)
        pos2.first = gameModule->getGridSize().first - 1;
    else if (pos2.first == gameModule->getGridSize().first && pos2.second == 11)
        pos2.first = 0;
    grid[pos2.second][pos2.first][1] = grid[pos1.second][pos1.first][1];
    grid[pos1.second][pos1.first][1] = std::make_shared<VoidEntity>(grid[pos1.second][pos1.first][0]->getSpriteName(), 0, "", pos1);
    grid[pos2.second][pos2.first][1]->setPosition(pos2);
    gameModule->setEntities(grid);
}

bool PacmanEntity::checkWallCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    std::pair<size_t, size_t> gridSize = gameModule->getGridSize();

    if (newPos.first == -1 && newPos.second == 11) {
        newPos.first = gridSize.first - 1;
        return false;
    }
    if (newPos.first == gridSize.first && newPos.second == 11) {
        newPos.first = 0;
        return false;
    }
    if (newPos.first >= gridSize.first || newPos.second >= gridSize.second
        || newPos.first < 0 || newPos.second < 0)
        return true;

    grid_t grid = gameModule->getEntities();
    if (std::dynamic_pointer_cast<WallEntity>(grid[newPos.second][newPos.first][1]))
        return true;
    return false;
}

void PacmanEntity::checkInteractions(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    grid_t grid = gameModule->getEntities();

    if (newPos.first == -1 && newPos.second == 11) {
        newPos.first = gameModule->getGridSize().first - 1;
    } else if (newPos.first == gameModule->getGridSize().first && newPos.second == 11) {
        newPos.first = 0;
    }
    if (newPos.first >= gameModule->getGridSize().first || newPos.second >= gameModule->getGridSize().second
        || newPos.first < 0 || newPos.second < 0)
        return;

    if (std::dynamic_pointer_cast<DotEntity>(grid[newPos.second][newPos.first][1])) {
        grid[newPos.second][newPos.first][1]->onInteract(gameModule);
        return;
    }
}

void PacmanEntity::moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction)
{
    this->actualiseAnimation();
    this->setDirection(direction, gameModule);

    if (gameModule->getGameState() != gameState_t::PLAYING)
        return;
    if (!this->lastTimePassed() || !gameModule->getIsStarted())
        return;
    this->_direction = this->_inputDirection;

    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> nextPosition = {this->_position.first + this->_direction.first, this->_position.second + this->_direction.second};

    if (checkWallCollision(gameModule, nextPosition))
        return;
    checkInteractions(gameModule, nextPosition);

    this->moveEntities(gameModule, this->_position, nextPosition);
}
