/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** FoodEntity
*/

#include "FoodEntity.hpp"
#include "IGameModule.hpp"
#include "VoidEntity.hpp"
#include <iostream>

FoodEntity::FoodEntity(std::pair<size_t, size_t> position)
{
    this->_spriteName = "assets/nibbler/Food1.png";
    this->_color = 2;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
    this->_timePoint = std::chrono::steady_clock::now();
}

FoodEntity::~FoodEntity()
{

}

int FoodEntity::getNbFoodEntities(const grid_t &grid) const
{
    int count = 0;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            if (std::dynamic_pointer_cast<FoodEntity>(grid[y][x][1]))
                count++;
        }
    }
    return count;
}

void FoodEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    int nbFoodEntities = getNbFoodEntities(grid);

    if (nbFoodEntities == 1) {
        gameModule->setScore(gameModule->getScore() + 110);
        gameModule->setGameState(gameState_t::WIN);
        return;
    }
    gameModule->setScore(gameModule->getScore() + 10);
}

std::string FoodEntity::getSpriteName() const
{
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - this->_timePoint;

    int state = static_cast<int>(elapsed_seconds.count() * 5) % 4;

    switch (state) {
        case 0:
            return this->_spriteName;
        case 1:
            return "assets/nibbler/Food2.png";
        case 2:
            return "assets/nibbler/Food3.png";
        case 3:
            return "assets/nibbler/Food2.png";
        default:
            return this->_spriteName;
    }
}
