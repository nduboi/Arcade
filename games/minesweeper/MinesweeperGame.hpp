/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** MinesweeperGame
*/


#ifndef MINESWEEPERGAME_HPP_
#define MINESWEEPERGAME_HPP_

#include "GameTemplate.hpp"
#include <random>
#include <map>

class MinesweeperGame : public GameTemplate {
    public:
        // Constructor
        MinesweeperGame(size_t width = 10, size_t height = 10, size_t mineCount = 10);

        // Destructor
        ~MinesweeperGame() = default;

        // Method
        void initializeGrid();
        void placeMines();
        void calculateAdjacentMines();
        gameState_t revealCell(size_t x, size_t y);
        gameState_t flagCell(size_t x, size_t y);
        gameState_t checkWinCondition();

    protected:

    private:
        // Variable
        size_t _width;
        size_t _height;
        size_t _mineCount;
        size_t _revealedCells;
        size_t _flaggedCells;
        gameState_t _gameState;
        bool _firstClick;

        // Method
        void revealAdjacentCells(size_t x, size_t y);
        bool isValidPosition(size_t x, size_t y) const;
        bool isMine(size_t x, size_t y) const;
        size_t countAdjacentMines(size_t x, size_t y) const;

};

#endif /* !MINESWEEPERGAME_HPP_ */
