/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"

class AEntity : public IEntity {
    protected:
        std::pair<size_t, size_t> _position;
        std::pair<size_t, size_t> _size;
        std::string _spriteName;
        std::size_t _color;
        std::string _text;
        std::size_t _zIndex;
        bool _isMovable;
        bool _hasCollisions;

    public:
        AEntity();
        ~AEntity() = default;

        void onClick(grid_t &grid) override;
        void moveEntity(grid_t &grid) override;
        void moveEntity(grid_t &grid, std::pair<size_t, size_t> direction);
        void onInteract(grid_t &grid) override;

        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;
        bool isMovable() const override;
        bool hasCollisions() const override;
};

#endif /* !AENTITY_HPP_ */
