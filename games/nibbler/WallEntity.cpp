/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** WallEntity
*/

#include "WallEntity.hpp"

WallEntity::WallEntity(const std::string& spriteName, std::pair<size_t, size_t> position)
{
    this->_spriteName = spriteName;
    this->_color = 5;
    this->_text = "";
    this->_position = position;
    this->_isMovable = false;
    this->_isControlable = false;
    this->_hasCollisions = true;
}
