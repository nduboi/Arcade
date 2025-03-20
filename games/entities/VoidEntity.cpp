/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** VoidEntity
*/

#include "VoidEntity.hpp"

VoidEntity::VoidEntity(std::string sprite, std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_spriteName = sprite;
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = false;
    this->_hasCollisions = false;
}
