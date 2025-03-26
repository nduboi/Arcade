/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <string>
#include <stdbool.h>
#include <vector>
#include <memory>
#include <utility>

#include "IGameModule.hpp"

typedef enum clickType_e {
    LEFT_CLICK,
    RIGHT_CLICK,
    MIDDLE_CLICK
} clickType_t;

class IEntity {
    public:
        ~IEntity() = default;

        virtual void onClick(std::shared_ptr<IGameModule> gameModule, clickType_t type) = 0;
        virtual void moveEntity(std::shared_ptr<IGameModule> gameModule) = 0;
        virtual void moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction) = 0;
        virtual void onInteract(std::shared_ptr<IGameModule> gameModule) = 0;

        virtual std::pair<size_t, size_t> getPosition() const = 0;
        virtual void setPosition(std::pair<size_t, size_t> position) = 0;
        virtual std::string getSpriteName() const = 0;
        virtual std::size_t getColor() const = 0;
        virtual std::string getText() const = 0;
        virtual bool isMovable() const = 0;
        virtual bool isControlable() const = 0;
        virtual bool hasCollisions() const = 0;
};

typedef std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> grid_t;

#endif /* !IENTITY_HPP_ */
