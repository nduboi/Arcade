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
        std::size_t _zIndex;
        bool _isMovable;

    public:
        AEntity();
        ~AEntity() = default;

        void onClick() override;
        void moveEntity() override;
        void onInteract() override;

        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        bool isMovable() const override;
};

#endif /* !AENTITY_HPP_ */
