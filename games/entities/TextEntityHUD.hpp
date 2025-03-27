/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TextEntityHUD
*/

#ifndef TEXTENTITYHUD_HPP_
#define TEXTENTITYHUD_HPP_

#include "AEntity.hpp"

class TextEntityHUD : public AEntity {
    public:
        TextEntityHUD(std::string text);
        ~TextEntityHUD() = default;
};

#endif /* !TEXTENTITYHUD_HPP_ */
