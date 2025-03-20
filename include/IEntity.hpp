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

class IEntity {
    public:
        IEntity();
        ~IEntity() = default;

        virtual void onClick() = 0;
        virtual void moveEntity() = 0;
        virtual void onInteract() = 0;

        virtual std::string getSpriteName() const = 0;
        virtual std::size_t getColor() const = 0;
        virtual bool isMovable() const = 0;
};

#endif /* !IENTITY_HPP_ */
