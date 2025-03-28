/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TextEntityHUD
*/

#include "TextEntityHUD.hpp"

TextEntityHUD::TextEntityHUD(std::string text, std::pair<std::size_t, std::size_t> position)
{
    this->_color = 1;
    this->_text = text;
    this->_position = position;
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
