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

        std::vector<std::shared_ptr<IEntity>> getHUD() const override;

    protected:
    private:
        void setLayerBackground();
        void setLayerEntities();
        void setSnakeBody();
        void setLayerApple();
};

#endif /* !SNAKEGAME_HPP_ */
