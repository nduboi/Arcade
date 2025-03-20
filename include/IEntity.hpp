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

typedef std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> grid_t;

class IEntity {
    public:
        ~IEntity() = default;

        virtual void onClick(grid_t &grid) = 0;
        virtual void moveEntity(grid_t &grid) = 0;
        virtual void moveEntity(grid_t &grid, std::pair<size_t, size_t> direction);
        virtual void onInteract(grid_t &grid) = 0;

        virtual std::string getSpriteName() const = 0;
        virtual std::size_t getColor() const = 0;
        virtual std::string getText() const = 0;
        virtual bool isMovable() const = 0;
        virtual bool hasCollisions() const = 0;
};

#endif /* !IENTITY_HPP_ */
