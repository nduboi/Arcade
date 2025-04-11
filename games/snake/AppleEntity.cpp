/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AppleEntity
*/

#include "AppleEntity.hpp"
#include "IGameModule.hpp"
#include "VoidEntity.hpp"
#include <iostream>

AppleEntity::AppleEntity(std::pair<size_t, size_t> position)
{
    this->_spriteName = "assets/snake/apple1.png";
    this->_color = 2;
    this->_text = "a";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
    this->_timePoint = std::chrono::steady_clock::now();
}

int AppleEntity::getNbVoidEntities(const grid_t &grid) const
{
    int count = 0;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            if (std::dynamic_pointer_cast<VoidEntity>(grid[y][x][1]))
                count++;
        }
    }
    return count;
}

bool AppleEntity::isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const
{
    if (pos.first >= grid[0].size() || pos.second >= grid.size())
        return false;
    if (pos.first < 0 || pos.second < 0)
        return false;

    if (std::dynamic_pointer_cast<VoidEntity>(grid[pos.second][pos.first][1]))
        return true;
    return false;
}

void AppleEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    int nbVoidEntities = getNbVoidEntities(grid);

    if (nbVoidEntities == 0) {
        gameModule->setGameState(gameState_t::WIN);
        gameModule->setScore(gameModule->getScore() + 100);
        return;
    }

    srand(time(NULL));
    std::pair<size_t, size_t> newPos = {rand() % grid[0].size(), rand() % grid.size()};
    while (!isValidPosition(newPos, grid)) {
        newPos = {rand() % grid[0].size(), rand() % grid.size()};
    }

    grid[newPos.second][newPos.first][1] = std::make_shared<AppleEntity>(newPos);
    gameModule->setEntities(grid);
    gameModule->setScore(gameModule->getScore() + 10);
}

std::string AppleEntity::getSpriteName() const
{
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - this->_timePoint;

    int state = static_cast<int>(elapsed_seconds.count() * 5) % 4;

    switch (state) {
        case 0:
            return this->_spriteName;
        case 1:
            return "assets/snake/apple2.png";
        case 2:
            return "assets/snake/apple3.png";
        case 3:
            return "assets/snake/apple2.png";
        default:
            return this->_spriteName;
    }
}
