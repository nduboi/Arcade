/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TimeEntityHUD
*/

#include "TimeEntityHUD.hpp"

TimeEntityHUD::TimeEntityHUD(std::size_t time)
{
    this->_color = 1;
    this->_text = "Time: " + std::to_string(time) + "s";
    this->_position = {0, 1};
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
