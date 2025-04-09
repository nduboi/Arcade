/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** WallEntity
*/

#include "WallEntity.hpp"

WallEntity::WallEntity(std::string sprite, std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_spriteName = sprite;
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
}
