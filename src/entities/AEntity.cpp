/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#include "AEntity.hpp"

void AEntity::onClick()
{
}

void AEntity::moveEntity()
{
}

void AEntity::onInteract()
{
}

std::string AEntity::getSpriteName() const
{
    return _spriteName;
}

std::size_t AEntity::getColor() const
{
    return _color;
}

bool AEntity::isMovable() const
{
    return _isMovable;
}
