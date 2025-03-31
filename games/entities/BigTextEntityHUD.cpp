/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigTextEntityHUD
*/

#include "BigTextEntityHUD.hpp"

BigTextEntityHUD::BigTextEntityHUD(std::string text, std::pair<std::size_t, std::size_t> position)
{
    this->_color = 0;
    this->_text = text;
    this->_position = position;
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
