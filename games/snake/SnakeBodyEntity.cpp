/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeBodyEntity
*/

#include "SnakeBodyEntity.hpp"

SnakeBodyEntity::SnakeBodyEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position, int index)
{
    this->_spriteName = "assets/snake/body_horizontal.png";
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = false;
    this->_hasCollisions = true;
    this->_index = index;
    this->_direction = {1, 0}; // Default horizontal direction

    // Initialize asset name map for different body positions
    this->_assetsName = {
        {"horizontal", "assets/snake/body_horizontal.png"},
        {"vertical", "assets/snake/body_vertical.png"},
        {"corner_tl", "assets/snake/body_topleft.png"},
        {"corner_tr", "assets/snake/body_topright.png"},
        {"corner_bl", "assets/snake/body_bottomleft.png"},
        {"corner_br", "assets/snake/body_bottomright.png"},
        {"tail_up", "assets/snake/tail_up.png"},
        {"tail_down", "assets/snake/tail_down.png"},
        {"tail_left", "assets/snake/tail_left.png"},
        {"tail_right", "assets/snake/tail_right.png"}
    };
}

int SnakeBodyEntity::getIndex() const
{
    return this->_index;
}

void SnakeBodyEntity::updateDirection(std::pair<size_t, size_t> current, std::pair<size_t, size_t> next, std::pair<size_t, size_t> prev)
{
    // Tail
    if (prev.first == 100 && prev.second == 100) {
        if (next.first > current.first)
            this->_spriteName = this->_assetsName["tail_left"];
        else if (next.first < current.first)
            this->_spriteName = this->_assetsName["tail_right"];
        else if (next.second > current.second)
            this->_spriteName = this->_assetsName["tail_up"];
        else if (next.second < current.second)
            this->_spriteName = this->_assetsName["tail_down"];
        return;
    }

    // Body
    int dx_next = next.first - current.first;
    int dy_next = next.second - current.second;
    int dx_prev = current.first - prev.first;
    int dy_prev = current.second - prev.second;

    if ((dx_next != 0 && dx_prev != 0) && (dy_next == 0 && dy_prev == 0)) {
        this->_spriteName = this->_assetsName["horizontal"];
    } else if ((dx_next == 0 && dx_prev == 0) && (dy_next != 0 && dy_prev != 0)) {
        this->_spriteName = this->_assetsName["vertical"];
    } else {
        if (dx_next < 0 && dy_prev < 0)
            this->_spriteName = this->_assetsName["corner_bl"];
        else if (dx_next < 0 && dy_prev > 0)
            this->_spriteName = this->_assetsName["corner_tl"];
        else if (dx_next > 0 && dy_prev < 0)
            this->_spriteName = this->_assetsName["corner_br"];
        else if (dx_next > 0 && dy_prev > 0)
            this->_spriteName = this->_assetsName["corner_tr"];
        else if (dy_next < 0 && dx_prev < 0)
            this->_spriteName = this->_assetsName["corner_tr"];
        else if (dy_next < 0 && dx_prev > 0)
            this->_spriteName = this->_assetsName["corner_tl"];
        else if (dy_next > 0 && dx_prev < 0)
            this->_spriteName = this->_assetsName["corner_br"];
        else if (dy_next > 0 && dx_prev > 0)
            this->_spriteName = this->_assetsName["corner_bl"];
    }
}

std::string SnakeBodyEntity::getSpriteName() const
{
    return this->_spriteName;
}
