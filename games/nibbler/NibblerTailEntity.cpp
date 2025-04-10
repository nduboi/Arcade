/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerTailEntity
*/

#include "NibblerTailEntity.hpp"

NibblerTailEntity::NibblerTailEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position, int index)
{
    this->_spriteName = "assets/nibbler/Nibbler_tail_horizontal.png";
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = false;
    this->_hasCollisions = true;
    this->_index = index;
    this->_direction = {1, 0};
}

int NibblerTailEntity::getIndex() const
{
    return this->_index;
}

std::string NibblerTailEntity::getSpriteName() const
{
    return this->_spriteName;
}
