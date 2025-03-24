/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeGame
*/

#include "SnakeGame.hpp"
#include "VoidEntity.hpp"

SnakeGame::SnakeGame()
{
    bool grass = false;
    this->_highScore = 0;
    this->_score = 0;

    this->_entities.resize(17);
    for (int y = 0; y < 17; y++) {
        this->_entities[y].resize(17);
        for (int x = 0; x < 17; x++) {
            this->_entities[y][x].resize(1);
            if (grass)
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_bright.png", 0, "", std::make_pair(x, y));
            else
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_dark.png", 0, "", std::make_pair(x, y));
            grass = !grass;
        }
    }
}
