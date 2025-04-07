/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** WallEntity
*/

#ifndef WALLENTITY_HPP_
#define WALLENTITY_HPP_

#include "AEntity.hpp"

class WallEntity : public AEntity {
    public:
        WallEntity(std::string sprite, std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~WallEntity() = default;
};

#endif /* !WALLENTITY_HPP_ */
