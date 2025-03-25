/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeGame
*/

#ifndef SNAKEGAME_HPP_
#define SNAKEGAME_HPP_

#include "GameTemplate.hpp"
#include "SnakeHeadEntity.hpp"

class SnakeGame : public GameTemplate {
    public:
        SnakeGame();
        ~SnakeGame() = default;

    protected:
    private:
        void setLayerBackground();
        void setLayerEntities();
        void setSnakeBody();
        void setLayerApple();
};

#endif /* !SNAKEGAME_HPP_ */
