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

std::string AEntity::getSpriteName() const
{
    return _spriteName;
}

std::size_t AEntity::getColor() const
{
    return _color;
}

std::string AEntity::getText() const
{
    return _text;
}

bool AEntity::isMovable() const
{
    return _isMovable;
}

bool AEntity::hasCollisions() const
{
    return _hasCollisions;
}
