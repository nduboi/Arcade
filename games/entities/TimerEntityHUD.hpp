/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TimerEntityHUD
*/

#ifndef TIMERENTITYHUD_HPP_
#define TIMERENTITYHUD_HPP_

#include "AEntity.hpp"

class TimerEntityHUD : public AEntity {
    public:
        TimerEntityHUD(std::size_t time, std::size_t limit, std::pair<std::size_t, std::size_t> position);
        ~TimerEntityHUD() = default;
};

#endif /* !TIMERENTITYHUD_HPP_ */
