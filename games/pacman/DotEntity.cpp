/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** DotEntity
*/

#include "DotEntity.hpp"
#include "IGameModule.hpp"
#include "VoidEntity.hpp"
#include <iostream>

DotEntity::DotEntity(std::pair<size_t, size_t> position)
{
    this->_spriteName = "assets/pacman/other/dot.png";
    this->_color = 1;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
}

void DotEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    gameModule->setScore(gameModule->getScore() + 1);
}
