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

    this->_assetsName = {
        {"horizontal", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"vertical", "assets/nibbler/Nibbler_tail_vertical.png"},
        {"corner_tl", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"corner_tr", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"corner_bl", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"corner_br", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"tail_up", "assets/nibbler/Nibbler_tail_vertical"},
        {"tail_down", "assets/nibbler/Nibbler_tail_vertical.png"},
        {"tail_left", "assets/nibbler/Nibbler_tail_horizontal.png"},
        {"tail_right", "assets/nibbler/Nibbler_tail_horizontal.png"}
    };
}

int NibblerTailEntity::getIndex() const
{
    return this->_index;
}

void NibblerTailEntity::updateDirection(std::pair<size_t, size_t> current, std::pair<size_t, size_t> next, std::pair<size_t, size_t> prev)
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

std::string NibblerTailEntity::getSpriteName() const
{
    return this->_spriteName;
}
