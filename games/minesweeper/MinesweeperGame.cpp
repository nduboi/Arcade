/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MinesweeperGame
*/

#include "MinesweeperGame.hpp"
#include "Cell.hpp"

MinesweeperGame::MinesweeperGame(size_t width, size_t height)
{
    this->_width = width;
    this->_height = height;

    initializeGrid();
}

void MinesweeperGame::initializeGrid()
{
    _entities.resize(this->_height);
    for (size_t y = 0; y < this->_height; ++y) {
        _entities[y].resize(this->_width);
        for (size_t x = 0; x < this->_width; ++x) {
            _entities[y][x].resize(1);
            _entities[y][x][0] = std::make_shared<Cell>(x, y);
        }
    }
}
