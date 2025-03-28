/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** TimeEntity
*/

#ifndef TIMEENTITYHUD_HPP_
#define TIMEENTITYHUD_HPP_

#include "AEntity.hpp"

class TimeEntityHUD : public AEntity {
    public:
        TimeEntityHUD(std::size_t time, std::pair<size_t, size_t> position);
        ~TimeEntityHUD() = default;

    protected:
    private:
};

#endif /* !TIMEENTITYHUD_HPP_ */
