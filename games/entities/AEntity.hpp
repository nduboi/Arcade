/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <string>
#include <utility>
#include "IEntity.hpp"

class AEntity : public IEntity {
    protected:
        std::pair<size_t, size_t> _position;
        std::string _spriteName;
        std::size_t _color;
        std::string _text;
        bool _isMovable;
        bool _hasCollisions;

    public:
        AEntity() = default;
        ~AEntity() = default;

        gameState_t onClick(grid_t &grid, clickType_t type) override;
        gameState_t moveEntity(grid_t &grid) override;
        gameState_t moveEntity(grid_t &grid, std::pair<size_t, size_t> direction) override;
        gameState_t onInteract(grid_t &grid) override;

        std::pair<size_t, size_t> getPosition() const override;
        void setPosition(std::pair<size_t, size_t> position) override;
        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;
        bool isMovable() const override;
        bool hasCollisions() const override;
};

#endif /* !AENTITY_HPP_ */
