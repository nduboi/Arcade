/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TimerEntityHUD
*/

#include "TimerEntityHUD.hpp"

TimerEntityHUD::TimerEntityHUD(std::size_t time, std::size_t limit, std::pair<std::size_t, std::size_t> position)
{
    this->_color = 1;
    if (time >= limit)
        this->_text = "Time left: 0s";
    else
        this->_text = "Time left: " + std::to_string(limit - time) + "s";
    this->_position = position;
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
