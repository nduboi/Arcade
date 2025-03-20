/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** VoidEntity
*/

#ifndef VOIDENTITY_HPP_
#define VOIDENTITY_HPP_

#include "AEntity.hpp"

class VoidEntity : public AEntity {
    protected:
    public:
        VoidEntity(std::string sprite, std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~VoidEntity() = default;
};

#endif /* !VOIDENTITY_HPP_ */
