/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#ifndef CELL_HPP_
#define CELL_HPP_

#include "AEntity.hpp"
#include <random>

class Cell : public AEntity {
    public:
        // Constructor
        Cell(size_t x, size_t y);
        ~Cell() = default;

        // Overridden methods
        void onClick(std::shared_ptr<IGameModule> gameModule, clickType_t type) override;
        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;

        // Getters
        bool isRevealed() const;
        bool isFlagged() const;
        bool isMine() const;
        size_t getAdjacentMines() const;

        // Setters
        void setRevealed(bool revealed);
        void setFlagged(bool flagged);
        void setMine(bool mine);
        void setAdjacentMines(size_t count);

    private:
        // Game state and grid information
        bool _isRevealed;
        bool _isFlagged;
        bool _isMine;
        size_t _adjacentMines;
        bool _firstClick;
        int _gameState;
        bool _clicked;

        // Game logic methods
        void placeMines(std::shared_ptr<IGameModule> gameModule);
        size_t createNumberMines(std::pair<size_t, size_t> map);
        void calculateAdjacentMines(std::shared_ptr<IGameModule> gameModule);
        size_t countAdjacentMines(size_t x, size_t y, const grid_t& grid) const;
        void revealAdjacentCells(size_t x, size_t y, grid_t& grid);
        void revealAllMines(std::shared_ptr<IGameModule> gameModule);
        gameState_t checkWinCondition(std::shared_ptr<IGameModule> gameModule);
};

#endif /* !CELL_HPP_ */
