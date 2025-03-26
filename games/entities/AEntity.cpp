/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#include "AEntity.hpp"

void AEntity::onClick(std::shared_ptr<IGameModule> gameModule, clickType_t type)
{
    (void)gameModule;
    (void)type;
}

void AEntity::moveEntity(std::shared_ptr<IGameModule> gameModule)
{
    (void)gameModule;
}

void AEntity::moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction)
{
    (void)gameModule;
    (void)direction;
}

void AEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    (void)gameModule;
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

bool AEntity::isControlable() const
{
    return this->_isControlable;
}

bool AEntity::hasCollisions() const
{
    return this->_hasCollisions;
}
