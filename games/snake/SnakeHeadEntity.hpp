/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeHead
*/

#ifndef SNAKEHEAD_HPP_
#define SNAKEHEAD_HPP_

#include <map>

#include "AEntity.hpp"

class SnakeHeadEntity : public AEntity {
    private:
        std::pair<int, int> _direction;
        std::map<std::pair<size_t, size_t>, std::string> _assetsName;

    public:
        SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~SnakeHeadEntity() = default;

        gameState_t moveEntity(IGameModule &gameModule, std::pair<int, int> direction) override;

        std::string getSpriteName() const override;
};

#endif /* !SNAKEHEAD_HPP_ */
