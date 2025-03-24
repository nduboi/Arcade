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

class IEntity;
class IGameModule;

typedef std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> grid_t;

typedef enum clickType_e {
    LEFT_CLICK,
    RIGHT_CLICK,
    MIDDLE_CLICK
} clickType_t;

typedef enum gameState_e {
    PLAYING,
    WIN,
    LOSE
} gameState_t;

class IEntity {
    public:
        virtual ~IEntity() = default;

        virtual gameState_t onClick(IGameModule &gameModule, clickType_t type) = 0;
        virtual gameState_t moveEntity(IGameModule &gameModule) = 0;
        virtual gameState_t moveEntity(IGameModule &gameModule, std::pair<int, int> direction) = 0;
        virtual gameState_t onInteract(IGameModule &gameModule) = 0;

        virtual std::pair<size_t, size_t> getPosition() const = 0;
        virtual void setPosition(std::pair<size_t, size_t> position) = 0;
        virtual std::string getSpriteName() const = 0;
        virtual std::size_t getColor() const = 0;
        virtual std::string getText() const = 0;
        virtual bool isMovable() const = 0;
        virtual bool isControlable() const = 0;
        virtual bool hasCollisions() const = 0;
};

#endif /* !IENTITY_HPP_ */
