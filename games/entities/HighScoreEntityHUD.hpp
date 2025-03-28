/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** HighScoreEntityHUD
*/

#ifndef HIGHSCOREENTITYHUD_HPP_
#define HIGHSCOREENTITYHUD_HPP_

#include "AEntity.hpp"

class HighScoreEntityHUD : public AEntity {
    public:
        HighScoreEntityHUD(std::size_t score, std::pair<std::size_t, std::size_t> position);
        ~HighScoreEntityHUD() = default;
};

#endif /* !HIGHSCOREENTITYHUD_HPP_ */
