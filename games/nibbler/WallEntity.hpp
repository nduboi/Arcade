/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** WallEntity
*/

#ifndef WALLENTITY_HPP_
#define WALLENTITY_HPP_

#include "AEntity.hpp"

class WallEntity : public AEntity {
    public:
        // Constructor
        WallEntity(const std::string& spriteName, std::pair<size_t, size_t> position);
        ~WallEntity() = default;
};

#endif /* !WALLENTITY_HPP_ */