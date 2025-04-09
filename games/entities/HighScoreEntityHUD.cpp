/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** HighScoreEntityHUD
*/

#include "HighScoreEntityHUD.hpp"

HighScoreEntityHUD::HighScoreEntityHUD(std::size_t score, std::pair<std::size_t, std::size_t> position)
{
    this->_color = 1;
    this->_text = "Your Highscore: " + std::to_string(score);
    this->_position = position;
    this->_isMovable = false;
    this->_hasCollisions = false;
    this->_isControlable = false;
    this->_spriteName = "";
}
