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
    _entities.resize(_height);
    for (size_t y = 0; y < _height; ++y) {
        _entities[y].resize(_width);
        for (size_t x = 0; x < _width; ++x) {
            _entities[y][x].resize(1);
            _entities[y][x][0] = std::make_shared<Cell>(x, y);
        }
    }
}
