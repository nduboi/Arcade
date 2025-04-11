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
    this->_spriteName = "assets/nibbler/Food.png";
    this->_color = 2;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
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
        gameModule->setGameState(gameState_t::WIN);
        gameModule->setScore(gameModule->getScore() + 100);
        return;
    }
    gameModule->setScore(gameModule->getScore() + 10);
}
