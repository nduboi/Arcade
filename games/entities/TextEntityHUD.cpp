/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TextEntityHUD
*/

#include "TextEntityHUD.hpp"

TextEntityHUD::TextEntityHUD(std::string text)
{
    this->_color = 1;
    this->_text = text;
    this->_position = {0, 0};
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
