/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#include "AEntity.hpp"

void AEntity::onClick(grid_t &grid)
{
    (void)grid;
}

void AEntity::moveEntity(grid_t &grid)
{
    (void)grid;
}

void moveEntity(grid_t &grid, std::pair<size_t, size_t> direction)
{
    (void)grid;
    (void)direction;
}

void AEntity::onInteract(grid_t &grid)
{
    (void)grid;
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
