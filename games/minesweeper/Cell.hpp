/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#ifndef CELL_HPP_
#define CELL_HPP_

#include "AEntity.hpp"

class Cell : public AEntity {
    public:
        // Constructor
        Cell(size_t x, size_t y);
        ~Cell() = default;

        // Method
        gameState_t onClick(grid_t &grid, clickType_t type) override;
        bool isRevealed() const;
        bool isFlagged() const;
        bool isMine() const;

        // Getter
        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;
        size_t getAdjacentMines() const;

        // Setter
        void setRevealed(bool revealed);
        void setFlagged(bool flagged);
        void setMine(bool mine);
        void setAdjacentMines(size_t count);

    protected:

    private:
        // Variable
        bool _isRevealed;
        bool _isFlagged;
        bool _isMine;
        size_t _adjacentMines;

};

#endif /* !CELL_HPP_ */
