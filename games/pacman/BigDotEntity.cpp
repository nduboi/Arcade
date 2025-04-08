/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigDotEntity
*/

#include "BigDotEntity.hpp"
#include "IGameModule.hpp"
#include "VoidEntity.hpp"
#include <iostream>

BigDotEntity::BigDotEntity(std::pair<size_t, size_t> position)
{
    this->_spriteName = "assets/pacman/other/strawberry.png";
    this->_color = 2;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
}

void BigDotEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    gameModule->setScore(gameModule->getScore() + 50);
}
