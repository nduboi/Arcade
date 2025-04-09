/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigDotEntity
*/

#include "BigDotEntity.hpp"
#include "IGameModule.hpp"
#include "VoidEntity.hpp"
#include "GhostEntity.hpp"

#include <iostream>
#include <memory>

BigDotEntity::BigDotEntity(std::pair<size_t, size_t> position)
{
    this->_spriteName = "assets/pacman/other/strawberry.png";
    this->_color = 5;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
}

void BigDotEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    gameModule->setScore(gameModule->getScore() + 50);
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> pos = gameModule->getGridSize();

    for (int y = 0; y < pos.second; y++) {
        for (int x = 0; x < pos.first; x++) {
            if (grid[y][x][2] == nullptr)
                continue;

            auto entity = grid[y][x][2];
            GhostEntity *ghost = dynamic_cast<GhostEntity *>(entity.get());

            if (ghost != nullptr) {
                ghost->setWasGettingChased(true);
                if (ghost->getPosition() == ghost->getSpawnPosition())
                    continue;
                ghost->setState(GhostEntity::CHASED);
                ghost->setWaitingTime(10);
                ghost->setSpeedTime(0.5f);
            }
        }
    }
}
