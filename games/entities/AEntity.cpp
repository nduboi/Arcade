/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#include "AEntity.hpp"

gameState_t onClick(grid_t &grid, clickType_t type)
{
    (void)grid;
    return gameState_t::PLAYING;
}

gameState_t AEntity::moveEntity(grid_t &grid)
{
    (void)grid;
    return gameState_t::PLAYING;
}

gameState_t moveEntity(grid_t &grid, std::pair<size_t, size_t> direction)
{
    (void)grid;
    (void)direction;
    return gameState_t::PLAYING;
}

gameState_t AEntity::onInteract(grid_t &grid)
{
    (void)grid;
    return gameState_t::PLAYING;
}

std::pair<size_t, size_t> AEntity::getPosition() const
{
    return this->_position;
}

void AEntity::setPosition(std::pair<size_t, size_t> position)
{
    this->_position = position;
}

std::string AEntity::getSpriteName() const
{
    return this->_spriteName;
}

std::size_t AEntity::getColor() const
{
    return this->_color;
}

std::string AEntity::getText() const
{
    return this->_text;
}

bool AEntity::isMovable() const
{
    return this->_isMovable;
}

bool AEntity::hasCollisions() const
{
    return this->_hasCollisions;
}
