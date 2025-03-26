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
        bool _isControlable;
        bool _hasCollisions;

    public:
        AEntity() = default;
        ~AEntity() = default;

        void onClick(std::shared_ptr<IGameModule> gameModule, clickType_t type) override;
        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
        void moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction) override;
        void onInteract(std::shared_ptr<IGameModule> gameModule) override;

        std::pair<size_t, size_t> getPosition() const override;
        void setPosition(std::pair<size_t, size_t> position) override;
        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;
        bool isMovable() const override;
        bool isControlable() const override;
        bool hasCollisions() const override;
};

#endif /* !AENTITY_HPP_ */
