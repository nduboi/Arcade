/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeGame
*/

#include "SnakeGame.hpp"

SnakeGame::SnakeGame()
{
    this->_highScore = 0;
    this->_score = 0;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            this->_entities[y][x][0] = new VoidEntity("void", 0, "", std::make_pair(x, y));
        }
    }
}
