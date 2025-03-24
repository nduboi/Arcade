 /*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <iostream>
#include <vector>
#include <memory>

#include "IEntity.hpp"

class IGameModule {
    public:
        virtual ~IGameModule() = default;

        virtual std::size_t getHighScore() const = 0;
        virtual void setHighScore(std::size_t highScore) = 0;
        virtual std::size_t getScore() const = 0;
        virtual void setScore(std::size_t score) = 0;
        virtual grid_t getEntities() const = 0;
        virtual std::pair<size_t, size_t> getGridSize() const = 0;
        //maybe more ?
};

#endif /* !IGAMEMODULE_HPP_ */
