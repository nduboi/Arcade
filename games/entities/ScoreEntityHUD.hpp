/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** ScoreEntityHUD
*/

#ifndef SCOREENTITYHUD_HPP_
#define SCOREENTITYHUD_HPP_

#include "AEntity.hpp"

class ScoreEntityHUD : public AEntity {
    public:
        ScoreEntityHUD(std::size_t score, std::pair<std::size_t, std::size_t> position);
        ~ScoreEntityHUD() = default;
};

#endif /* !SCOREENTITYHUD_HPP_ */
