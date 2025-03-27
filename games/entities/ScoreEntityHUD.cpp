/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** ScoreEntityHUD
*/

#include "ScoreEntityHUD.hpp"

ScoreEntityHUD::ScoreEntityHUD(std::size_t score)
{
    this->_color = 1;
    this->_text = "Score: " + std::to_string(score);
    this->_position = {0, 0};
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
